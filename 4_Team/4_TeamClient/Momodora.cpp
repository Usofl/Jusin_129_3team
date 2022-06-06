#include "stdafx.h"
#include "Momodora.h"
#include "MomoDoraMgr.h"
#include "RenderMgr.h"
#include "KeyMgr.h"
#include "MomoAbstractFactory.h"


CMomodora::CMomodora()
	: m_pPlayer(nullptr)
	, m_pTarget(nullptr)
	, iEnemyDamage(5)
	, iPlayerDamage(5)
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
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Shoter());
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

	for (auto& iter = MomoBulletList.begin();
		iter != MomoBulletList.end(); )
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete<CMomoBullet*>(*iter);
			iter = MomoBulletList.erase(iter);
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
		float fX = m_pPlayer->Get_Info().vPos.x;
		float fY = m_pPlayer->Get_Info().vPos.y;
		for (auto iter = m_listMonsterList.begin(); iter != m_listMonsterList.end(); iter++)
		{
			if (((*iter)->Get_Info().vPos.x - 50 < fX && (*iter)->Get_Info().vPos.x + 50 > fX)
				&& ((*iter)->Get_Info().vPos.y - 50 < fY && (*iter)->Get_Info().vPos.y + 50 > fY))
			{
				m_pPlayer->Set_HP(10);
				(*iter)->Set_Dead(true); //계속 충돌해서 피 쭈루룩 깎일까봐 방지용.. 피를 주고 몹 지우기
				int i = 5;
			}	
		}
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

	for (auto& iter : MomoBulletList)
	{
		iter->Late_Update();
		float fX = iter->Get_Info().vPos.x;
		float fY = iter->Get_Info().vPos.y;
		for (auto iter2 = m_listMonsterList.begin(); iter2 != m_listMonsterList.end(); iter2++)
		{
			if (((*iter2)->Get_Info().vPos.x - 30 < fX && (*iter2)->Get_Info().vPos.x + 30 > fX)
				&& ((*iter2)->Get_Info().vPos.y - 30 < fY && (*iter2)->Get_Info().vPos.y + 30 > fY) )
			{
				//(*iter2)->Set_Dead(true); // 삭제 처리한 부분인데 여기서 이제 HP까는걸로 바꾸면 됨
				(*iter2)->Set_HP(5);
				iter->Set_Dead(true);
			}
			else
			{
				//(*iter2)->Set_Dead(true);
			}
		}

		//iter->Set_Dead(true);
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

	for (auto& iter : MomoBulletList)
	{
		Safe_Delete<CMomoBullet*>(iter);
	}

	MomoBulletList.clear();

}

void CMomodora::Key_Input(void)
{
	if (KEYMGR->Key_Up('F'))
	{
		//CMomoDoraMgr::Get_Instance()->Weapon_Change(MOMOWEAPON_SWORD);0
		MomoSwordList.push_back(CMomoAbstractFactory::Create_Momo_Sword());
	}

	if (KEYMGR->Key_Up(VK_LBUTTON))
	{
		MomoBulletList.push_front(CMomoAbstractFactory::Create_Momo_Bullet());
	}
}