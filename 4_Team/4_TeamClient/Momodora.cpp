#include "stdafx.h"
#include "Momodora.h"
#include "MomoDoraMgr.h"
#include "RenderMgr.h"


CMomodora::CMomodora()
	: m_pPlayer(nullptr), m_pMomoSword(nullptr)
{
}


CMomodora::~CMomodora()
{
	Release();
}

void CMomodora::Initialize(void)
{
	m_ObjList[MOMO_PLAYER].push_back(Set_Player());
	((CMomodoraPlayer*)(m_ObjList[MOMO_PLAYER].front()))->Set_SwordList(&m_ObjList[MOMO_WEAPON]);
}

void CMomodora::Update(void)
{
	//m_pPlayer->Update();
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

}

void CMomodora::Late_Update(void)
{
	//m_pPlayer->Late_Update();
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	RENDERMGR->Add_Render_Obj(m_pPlayer);
}

void CMomodora::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);

	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);
}

void CMomodora::Release(void)
{
	//Safe_Delete<CMomodoraPlayer*>(m_pPlayer);
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CMomodora::Key_Input(void)
{
}

CObj* CMomodora::Set_Player(void)
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CMomodoraPlayer;
		m_pPlayer->Initialize();

		return m_pPlayer;
	}

	return nullptr;
}
