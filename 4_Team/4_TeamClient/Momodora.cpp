#include "stdafx.h"
#include "Momodora.h"
#include "MomoDoraMgr.h"
#include "RenderMgr.h"
#include "KeyMgr.h"
#include "MomoAbstractFactory.h"


CMomodora::CMomodora()
	: m_pPlayer(nullptr)
	, m_pTarget(nullptr)
	, m_iRandom_Spawn(0)
	, m_bSword_On(true)
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
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());
	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());

	m_listMonsterList.push_back(CMomoAbstractFactory::Create_Shoter());

	if (nullptr == m_pHPBar)
	{
		m_pHPBar = new CMomo_HpBar;
	}
}

void CMomodora::Update(void)
{
	Key_Input();
	if (nullptr != m_pPlayer)
	{
		m_pHPBar->Set_Lest_HP(m_pPlayer->Get_MaxHp(), m_pPlayer->Get_Hp());
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

	if (m_listMonsterList.size() < 5)
	{
		m_iRandom_Spawn = unsigned(rand() % 4) + 1;
		if (m_iRandom_Spawn == 4)
		{
			m_listMonsterList.push_back(CMomoAbstractFactory::Create_Shoter());
		}
		else
		{
			m_listMonsterList.push_back(CMomoAbstractFactory::Create_Follower());
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

	m_pHPBar->Update();
}

void CMomodora::Late_Update(void)
{
	m_pHPBar->Late_Update();

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

		D3DXVECTOR3 v_LeftFirst = iter->Get_Point(0);
		D3DXVECTOR3 v_LeftEnd = iter->Get_Point(1);
		
		D3DXVECTOR3 v_RightFirst = iter->Get_Point(2);
		D3DXVECTOR3 v_RightEnd = iter->Get_Point(3);



		float	LX = v_LeftFirst.x;
		float	RX = v_LeftEnd.x;
		float	LX2 = v_RightFirst.x;
		float	RX2 = v_RightEnd.x;

		float	LY = v_LeftFirst.y;
		float	RY = v_LeftEnd.y;
		float	LY2 = v_RightFirst.y;
		float	RY2 = v_RightEnd.y;

	//	float	pY(0.f);
	

		
		/*	if ((_fX <= LX + 10 && _fX >= RX - 10) || (_fX <= RX + 10  && _fX >= LX - 10))
			{
				bX = true;
			}

			if ((_fY <= LX + 10 && _fX >= RX - 10) || (_fX <= RX + 10 && _fX >= LX - 10))
			{
				bY = true;
			}
		*/
	/*	if ((_fX >= LX - 20.f && _fX <= RX + 20.f) || (_fX >= RX + 20.f && _fX <= LX - 20.f))
		{
			bX = true;
		}

		if ((_fY <= LY + 20.f && _fY >= RY - 20.f) || (_fY <= RY - 20.f && _fY >= LY + 20.f))
		{
			bY = true;
		}*/

		for (auto iter2 = m_listMonsterList.begin(); iter2 != m_listMonsterList.end(); iter2++)
		{
			if ((*iter2)->Get_MonsterID() == MOMO_FOLLOW)
			{

				float fX = (*iter2)->Get_Info().vPos.x;
				float fY = (*iter2)->Get_Info().vPos.y;

				//	float	pY(0.f);
				
				bool bX = false, bY = false;
				bool bX2 = false, bY2 = false;

				if ((fX <= LX + 20 && fX >= RX - 20) || (fX <= RX + 20 && fX >= LX - 20))
				{
					bX = true;
				}

				if ((fY <= LY + 20 && fY >= RY - 20) || (fY <= RY + 20 && fY >= LY - 20))
				{
					bY = true;
				}

				if (bX&&bY)
				{
					(*iter2)->Set_Dead(true);
				}

				if ((fX <= LX2 + 20 && fX >= RX2 - 20) || (fX <= RX2 + 20 && fX >= LX2 - 20))
				{
					bX2 = true;
				}

				if ((fY <= LY2 + 20 && fY >= RY2 - 20) || (fY <= RY2 + 20 && fY >= LY2 - 20))
				{
					bY2 = true;
				}

				if (bX2&&bY2)
				{
					(*iter2)->Set_Dead(true);
				}

			}

		}
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
			if ((*iter2)->Get_MonsterID() == MOMO_FOLLOW)
			{
				if (((*iter2)->Get_Info().vPos.x - 20 < fX && (*iter2)->Get_Info().vPos.x + 20 > fX)
					&& ((*iter2)->Get_Info().vPos.y - 20 < fY && (*iter2)->Get_Info().vPos.y + 20 > fY))
				{
					(*iter2)->Set_HP(5);// 삭제 처리한 부분인데 여기서 이제 HP까는걸로 바꾸면 됨
					(iter)->Set_Dead(true);
				}
			}


			else if ((*iter2)->Get_MonsterID() == MOMO_ROTATION)
			{
				if (((*iter2)->Get_Info().matWorld._41 - 20 < fX && (*iter2)->Get_Info().matWorld._41 + 20 > fX)
					&& ((*iter2)->Get_Info().matWorld._42 - 20 < fY && (*iter2)->Get_Info().matWorld._42 + 20 > fY))
				{
					(*iter2)->Set_HP(5); // 삭제 처리한 부분인데 여기서 이제 HP까는걸로 바꾸면 됨
					(iter)->Set_Dead(true);
				}
			}
		}

		//iter->Set_Dead(true);
		RENDERMGR->Add_Render_Obj(iter);
	}
}

void CMomodora::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);

	m_pHPBar->Render(_hDC);

	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);
}

void CMomodora::Release(void)
{
	Safe_Delete<CMomodoraPlayer*>(m_pPlayer);

	Safe_Delete<CMomo_HpBar*>(m_pHPBar);

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
	if (KEYMGR->Key_Up('Q') &&  MomoSwordList.size() == 0)	// 
	{
		//CMomoDoraMgr::Get_Instance()->Weapon_Change(MOMOWEAPON_SWORD);0
		MomoSwordList.push_back(CMomoAbstractFactory::Create_Momo_Sword());
	}
	if (KEYMGR->Key_Up('E') && MomoSwordList.size() == 1)
	{
		MomoSwordList.pop_front();
	}

	if (KEYMGR->Key_Up(VK_LBUTTON))
	{
		MomoBulletList.push_front(CMomoAbstractFactory::Create_Momo_Bullet());
	}
}