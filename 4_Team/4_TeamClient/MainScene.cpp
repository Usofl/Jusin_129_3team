#include "stdafx.h"
#include "MainScene.h"
#include "RenderMgr.h"
#include "SceneMgr.h"
#include "LineMgr.h"
#include "JunPlayer.h"
#include "JunBullet.h"
#include "Fortress_Bullet_Effect.h"
#include "Fortress_Boom_Effect.h"
#include "FortressFactory.h"

CMainScene::CMainScene()
	: m_pPlayer(nullptr)
	, m_pBullet(nullptr)
	, m_bReady(false)
	, m_eScene_Id(SC_MAIN)
{
	m_vecButton.reserve(3);
}


CMainScene::~CMainScene()
{
	Release();
}

void CMainScene::Initialize(void)
{
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CJunPlayer;
		m_pPlayer->Set_Pos(100, WINCY - 112);
	}

	if (m_vecButton.empty())
	{
		CMain_Button* Fortress_button = new CMain_Button(WINCX * 0.5f, WINCY * 0.6f);
		Fortress_button->Set_SceneId(SC_FORTRESS);

		CMain_Button* Momodora_button = new CMain_Button(WINCX * 0.5f, WINCY * 0.7f);
		Momodora_button->Set_SceneId(SC_MOMO);

		CMain_Button* End_button = new CMain_Button(WINCX * 0.5f, WINCY * 0.8f);
		End_button->Set_SceneId(SC_END);

		m_vecButton.push_back(Fortress_button);
		m_vecButton.push_back(Momodora_button);
		m_vecButton.push_back(End_button);
	}
}

void CMainScene::Update(void)
{
	if (nullptr != m_pPlayer)
	{
		m_pPlayer->Update();
	}

	if (nullptr != m_pBullet)
	{
		if (OBJ_DEAD == m_pBullet->Update())
		{
			Safe_Delete<CJunBullet*>(m_pBullet);
		}
	}

	for (auto& iter : m_vecButton)
	{
		iter->Update();
	}

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete<CFortress_Bullet_Effect*>(*iter);
			(iter) = m_list_Bullet_Effect.erase((iter));
		}
		else
		{
			iter++;
		}
	}

	for (auto iter = m_list_Boom_Effect.begin(); iter != m_list_Boom_Effect.end();)
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete<CFortress_Boom_Effect*>(*iter);
			(iter) = m_list_Boom_Effect.erase((iter));
		}
		else
		{
			iter++;
		}
	}
}

void CMainScene::Late_Update(void)
{
	if (m_bReady && m_list_Bullet_Effect.empty())
	{
		SCENEMGR->Scene_Change(m_eScene_Id);
		return;
	}

	if (nullptr != m_pPlayer)
	{
		m_pPlayer->Late_Update();
		RENDERMGR->Add_Render_Obj(m_pPlayer);
	}

	if (nullptr != m_pBullet)
	{
		m_pBullet->Late_Update();

		RENDERMGR->Add_Render_Obj(m_pBullet);
	}

	for (auto& iter : m_vecButton)
	{
		iter->Late_Update();
		Selete_Button(iter);

		RENDERMGR->Add_Render_Obj(iter);
	}

	for (auto& iter : m_list_Bullet_Effect)
	{
		iter->Late_Update();

		RENDERMGR->Add_Render_Obj(iter);
	}

	for (auto& iter : m_list_Boom_Effect)
	{
		iter->Late_Update();

		RENDERMGR->Add_Render_Obj(iter);
	}
}

void CMainScene::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);

	//UI ¿¹Á¤
	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);
}

void CMainScene::Release(void)
{
	Safe_Delete<CJunPlayer*>(m_pPlayer);
	Safe_Delete<CJunBullet*>(m_pBullet);

	for (auto& iter : m_vecButton)
	{
		Safe_Delete<CMain_Button*>(iter);
	}
	m_vecButton.clear();

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Bullet_Effect*>(*iter);

		iter = m_list_Bullet_Effect.erase(iter);
	}

	for (auto iter = m_list_Boom_Effect.begin(); iter != m_list_Boom_Effect.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Boom_Effect*>(*iter);

		iter = m_list_Boom_Effect.erase(iter);
	}
}

void CMainScene::Key_Input(void)
{
}

void CMainScene::Selete_Button(CMain_Button*& _pButton)
{
	if (nullptr == m_pBullet)
	{
		return;
	}

	D3DXVECTOR3 vBullet = m_pBullet->Get_Info().vPos;

	float fX = _pButton->Get_Info().vPos.x;
	float fY = _pButton->Get_Info().vPos.y;

	if (vBullet.x < 0 || vBullet.x > WINCX || vBullet.y > WINCY)
	{
		m_pBullet->Set_Dead(true);

		m_pPlayer->ReSet_Bullet();
		return;
	}

	if ((fX - 100.f <= vBullet.x && fX + 100.f >= vBullet.x) && (fY - 30.f <= vBullet.y && fY + 30.f >= vBullet.y))
	{
		m_pBullet->Set_Dead(true);
		if (SC_END != _pButton->Get_SceneId())
		{
			m_bReady = true;
			m_eScene_Id = _pButton->Get_SceneId();
			_pButton->Selected_Button();
		}
		else
		{
			m_pPlayer->ReSet_Bullet();
		}

		int num = Random_Num(7, 10);
		for (int i = 0; i < num; ++i)
		{
			m_list_Bullet_Effect.push_back(CFortressFactory::Create_Fortress_Bullet_Effect(vBullet.x, vBullet.y));
		}
		m_list_Boom_Effect.push_back(CFortressFactory::Create_Fortress_Boom_Effect(vBullet.x, vBullet.y));

	}
}
