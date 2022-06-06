#include "stdafx.h"
#include "Momodora.h"
#include "MomoDoraMgr.h"
#include "RenderMgr.h"
#include "KeyMgr.h"
#include "MomoAbstractFactory.h"


CMomodora::CMomodora()
	: m_pPlayer(nullptr)
	, m_pTarget(nullptr)
{
}


CMomodora::~CMomodora()
{
	Release();
}

void CMomodora::Initialize(void)
{
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CMomodoraPlayer;
	}
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());
}

void CMomodora::Update(void)
{
	Key_Input();
	if (nullptr != m_pPlayer)
	{
		m_pPlayer->Update();
	}

	for (auto& iter = MomoSwordList.begin();
		iter != MomoSwordList.end(); )
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete<CMomoSword*>(*iter);
			iter = MomoSwordList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	for (auto& iter = m_listMonsterList.begin();
		iter != m_listMonsterList.end(); )
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete<CMonster*>(*iter);
			iter = m_listMonsterList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CMomodora::Late_Update(void)
{
	if (nullptr != m_pPlayer)
	{
		m_pPlayer->Late_Update();
		RENDERMGR->Add_Render_Obj(m_pPlayer);
	}

	for (auto& iter : MomoSwordList)
	{
		iter->Late_Update();
		RENDERMGR->Add_Render_Obj(iter);
	}

	for (auto& iter : m_listMonsterList)
	{
		iter->Late_Update();
		RENDERMGR->Add_Render_Obj(iter);
	}
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
	Safe_Delete<CMomodoraPlayer*>(m_pPlayer);

	for (auto& iter : MomoSwordList)
	{
		Safe_Delete<CMomoSword*>(iter);
	}
	MomoSwordList.clear();

	for (auto& iter : m_listMonsterList)
	{
		Safe_Delete<CMonster*>(iter);
	}
	m_listMonsterList.clear();
}

void CMomodora::Key_Input(void)
{
	if (KEYMGR->Key_Up('F'))
	{
		//CMomoDoraMgr::Get_Instance()->Weapon_Change(MOMOWEAPON_SWORD);0
		MomoSwordList.push_back(CMomoAbstractFactory::Create_Momo_Sword());
	}

}