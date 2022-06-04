#include "stdafx.h"
#include "Fortress.h"
#include "RenderMgr.h"
#include "FortressFactory.h"
#include "CameraMgr.h"
#include "ScrollMgr.h"

CFortress::CFortress()
	: JunPlayer(nullptr)
	, m_pTarget(nullptr)
	, JunBullet(nullptr)
	, m_bPlayer_Turn(true)
	, m_bMonster_Turn(false)
	, iEnemyDamage(50)
	, iPlayerDamage(20)
{

}

CFortress::~CFortress()
{
	Release();
}

void CFortress::Initialize(void)
{

	if (nullptr == JunPlayer)
	{
		JunPlayer = new CJunPlayer;
		m_pTarget = JunPlayer;
	}

	if (nullptr == FortressMonster)
	{
		FortressMonster = new CFortress_Monster;
		FortressMonster->Initialize();

	}

	m_Line.tLPoint = { 0.f,0.f };
	m_Line.tRPoint = { 300.f,0.f };

	LineMaker();
}

void CFortress::Update(void)
{
	SCROLLMGR->Scroll_Lock_Fortress();

	if (nullptr != JunPlayer)
	{
		JunPlayer->Update();
	}
	if (nullptr != FortressMonster)
	{
		FortressMonster->Update();
	}
	
	for (auto& iter : JunBulletList)
	{
		iter->Update();
	}
	for (auto& iter : Monster_Bullet_List)
	{
		iter->Update();
	}

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		if (OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete(*iter);
			(iter) = m_list_Bullet_Effect.erase((iter));
		}
		else
		{
			iter++;
		}
	}

	OffSet();
}

void CFortress::Late_Update(void)
{
	if (JunPlayer !=nullptr)
	{
		JunPlayer->Late_Update();
		//RENDERMGR->Add_Render_Obj(JunPlayer);
	}
	

	if (nullptr != FortressMonster)
	{
		FortressMonster->Late_Update();
	}

	float fMonsterX2(0.f), fMonsterY2(0.f);
	if (nullptr != FortressMonster)
	{
		D3DXVECTOR3 vMonster = FortressMonster->Get_Info().vPos;
		fMonsterX2 = vMonster.x;
		fMonsterY2 = vMonster.y;
	}

	//임시 총알 - 몬스터 충돌처리(몬스터 1마리 기준이라 추후 수정 필요)
	if (fMonsterX2 != 0.f && fMonsterY2 != 0.f)
	{
		for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
		{
			(*iter)->Late_Update();

			if (MonsterCollision_Check(fMonsterX2, fMonsterY2, (*iter)->Get_Info().vPos.x, (*iter)->Get_Info().vPos.y))
			{
				Safe_Delete(*iter);
				(iter) = JunBulletList.erase((iter));
				FortressMonster->Set_Hp(1);
				if (FortressMonster->Get_Hp() <= 0)
				{
					Safe_Delete<CFortress_Monster*>(FortressMonster);
				}

				JunPlayer->ReSet_Bullet(); // 삭제 했으니 플레이어의 총알 포인터 초기화 -> 현재는 총알 포인터가 Nullptr이면 새로 생성 못하게 끔 해놨음(한 발만 쏘게)
				
				if (nullptr != FortressMonster)
				{
					m_pTarget = FortressMonster;
				}
				else
				{
					m_pTarget = JunPlayer;
				}
			}

			else
			{
				iter++;
			}
		}
	}

	//총알 충돌 했으면 몬스터가 없을테니 렌더를 안하게 해서 오류 없애기
	if (nullptr != FortressMonster)
	{
		RENDERMGR->Add_Render_Obj(FortressMonster);
	}

	if (JunBulletList.size() > 0)
	{
		for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
		{
			float fX = (*iter)->Get_Info().vPos.x;
			float fY = (*iter)->Get_Info().vPos.y;
			/*if((*iter)->Get_Info)*/
			if (LINEMGR->Collision_DeLine(fX, fY))
			{
				int num = Random_Num(7, 10);
				for (int i = 0; i < num; ++i)
				{
					m_list_Bullet_Effect.push_back(CFortressFactory::Create_Fortress_Bullet_Effect((*iter)->Get_Info().vPos.x, (*iter)->Get_Info().vPos.y));
				}

				Safe_Delete(*iter);
				(iter) = JunBulletList.erase((iter));
				JunPlayer->ReSet_Bullet(); // 삭제 했으니 플레이어의 총알 포인터 초기화 -> 현재는 총알 포인터가 Nullptr이면 새로 생성 못하게 끔 해놨음(한 발만 쏘게)

				if (nullptr != FortressMonster)
				{
					m_pTarget = FortressMonster;
				}
				else
				{
					m_pTarget = JunPlayer;
				}

			}
			else if (fY >= WINCY)
			{
				Safe_Delete(*iter);
				(iter) = JunBulletList.erase((iter));
				JunPlayer->ReSet_Bullet(); // 삭제 했으니 플레이어의 총알 포인터 초기화 -> 현재는 총알 포인터가 Nullptr이면 새로 생성 못하게 끔 해놨음(한 발만 쏘게)

				if (nullptr != FortressMonster)
				{
					m_pTarget = FortressMonster;
				}
				else
				{
					m_pTarget = JunPlayer;
				}
			}
			else
			{
				RENDERMGR->Add_Render_Obj(*iter);
				iter++;
			}
		}
	}



	

	for (auto iter = Monster_Bullet_List.begin(); iter != Monster_Bullet_List.end();)
	{
		if (JunPlayer == nullptr)
		{
			return;
		}
		
		float fPlayerX = JunPlayer->Get_Info().vPos.x;
		float fPlayerY = JunPlayer->Get_Info().vPos.y;
		(*iter)->Late_Update();
		//if (FortressMonster->Get_Info().vPos.x < iter->Get_Info().vPos.x)
		float fX = (*iter)->Get_Info().vPos.x;
		float fY = (*iter)->Get_Info().vPos.y;

		bool bX = false, bY = false;

		if (fPlayerX - 50.f <= fX && fPlayerX + 50.f >= fX )
		{
			bX = true;
		}

		if (fPlayerY - 60.f <= fY && fPlayerY + 30.f >= fY )
		{
			bY = true;
		}
		if (bX&&bY)
		{
			if (0 < JunPlayer->Get_Hp())
			{
				JunPlayer->Minus_Hp(iEnemyDamage);
				JunPlayer->Get_Hp();
				int i = 5;
			}
			else
			{
				Safe_Delete(JunPlayer);
			}
		}
		if (LINEMGR->Collision_DeLine(fX, fY))
		{
			int num = Random_Num(7, 10);
			for (int i = 0; i < num; ++i)
			{
				m_list_Bullet_Effect.push_back(CFortressFactory::Create_Fortress_Bullet_Effect((*iter)->Get_Info().vPos.x, (*iter)->Get_Info().vPos.y));
			}

			Safe_Delete(*iter);
			(iter) = Monster_Bullet_List.erase((iter));

			if (nullptr != JunPlayer)
			{
				m_pTarget = JunPlayer;
			}
			else
			{
				m_pTarget = FortressMonster;
			}
		}
		else if (fY >= WINCY)
		{
			Safe_Delete(*iter);
			(iter) = Monster_Bullet_List.erase((iter));

			if (nullptr != JunPlayer)
			{
				m_pTarget = JunPlayer;
			}
			else
			{
				m_pTarget = FortressMonster;
			}
		}
		else
		{
			RENDERMGR->Add_Render_Obj(*iter);
			iter++;
		}
		//iter->Set_Pos(1000.f, 1000.f);
	}

	for (auto& iter : m_list_Bullet_Effect)
	{
		iter->Late_Update();

		RENDERMGR->Add_Render_Obj(iter);
	}

	if (JunPlayer == nullptr)
	{
		return;
	}

		float fX = JunPlayer->Get_Info().vPos.x;
		float fY = JunPlayer->Get_Info().vPos.y;
	
	

	float fAngle(0.f);

	if (LINEMGR->Collision_JunLine(fX, fY, fAngle))
	{
		JunPlayer->Set_Angle(fAngle);
		JunPlayer->Set_Pos(fX, fY);
		JunPlayer->Set_State(CJunPlayer::IDLE);
	}
	else
	{
		JunPlayer->Set_State(CJunPlayer::FALLEN);
	}

	if (nullptr == FortressMonster)
	{
		return;
	}

	float fMonsterX = FortressMonster->Get_Info().vPos.x;
	float fMonsterY = FortressMonster->Get_Info().vPos.y;

	if (LINEMGR->Collision_Line(fMonsterX, &fMonsterY))
	{
		float fSour = LINEMGR->Collision_Monster_Line(fMonsterX, &fMonsterY);
		FortressMonster->Set_Angle(fSour);
		FortressMonster->Set_Pos(fMonsterX, fMonsterY - 20);
	}

	RENDERMGR->Add_Render_Obj(JunPlayer);
}

void CFortress::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);

	LINEMGR->Render(_hDC);

	CAMERAMGR->CloseUP_DC(_hDC);

	//UI 예정
	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);
	/*const TCHAR *str2 = TEXT("45%d");
	int i = 45;*/
	//TextOut(_hDC, 100, 100, i"%d", _tcslen(str2));
	//CString::Format()

	//Rectangle(_hDC, 0, 0, 1024, 110);
	//Rectangle(_hDC, 0, 658, 1024, 768);

	/*for (int i = 0; 6 > i; ++i)
	{
		MoveToEx(_hDC, LineArray[i].tLPoint.fX, LineArray[i].tLPoint.fY, nullptr);
		LineTo(_hDC, LineArray[i+1].tLPoint.fX, LineArray[i + 1].tLPoint.fY);
	}
	*/
	//LineArray[0].Render(_hDC);
	/*MoveToEx(_hDC,., 320, nullptr);
	LineTo(_hDC, 500, 320);*/


}


void CFortress::Release(void)
{

	Safe_Delete<CJunPlayer*>(JunPlayer);

	Safe_Delete<CFortress_Monster*>(FortressMonster);

	for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CJunBullet*>(*iter);

		iter = JunBulletList.erase(iter);
	}

	for (auto iter = Monster_Bullet_List.begin(); iter != Monster_Bullet_List.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Monster_Bullet*>(*iter);

		iter = Monster_Bullet_List.erase(iter);
	}

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Bullet_Effect*>(*iter);

		iter = m_list_Bullet_Effect.erase(iter);
	}

	LINEMGR->Destroy_Instance();
}

void CFortress::Key_Input(void)
{

}

const bool CFortress::MonsterCollision_Check(float _fMonsterX, float _fMonsterY, float _fBulletX, float _fBulletY)
{
	if ((_fMonsterX - 50 <= _fBulletX &&
		_fMonsterX + 50 >= _fBulletX) &&
		(_fMonsterY - 30 <= _fBulletY &&
			_fMonsterY + 30 >= _fBulletY))
	{
		return true;
	}

	return false;
}

void CFortress::LineMaker(void)
{
	LINEMGR->Create_Line(0, 300, 100, 310);
	LINEMGR->Create_Line(100, 310, 120, 320);
	LINEMGR->Create_Line(120, 320, 140, 350);
	LINEMGR->Create_Line(140, 350, 200, 500);
	LINEMGR->Create_Line(200, 500, 210, 510);
	LINEMGR->Create_Line(210, 510, 230, 530);
	LINEMGR->Create_Line(230, 530, 250, 540);
	LINEMGR->Create_Line(250, 540, 320, 550);
	LINEMGR->Create_Line(320, 550, 410, 545);
	LINEMGR->Create_Line(410, 545, 460, 540);
	LINEMGR->Create_Line(460, 540, 520, 540);
	LINEMGR->Create_Line(520, 540, 560, 545);
	LINEMGR->Create_Line(560, 545, 650, 540);
	LINEMGR->Create_Line(650, 540, 770, 515);
	LINEMGR->Create_Line(770, 515, 810, 500);
	LINEMGR->Create_Line(810, 500, 900, 480);
	LINEMGR->Create_Line(900, 480, 920, 460);
	LINEMGR->Create_Line(920, 460, 1000, 420);
	LINEMGR->Create_Line(1000, 420, 1100, 405);
	LINEMGR->Create_Line(1100, 405, 1130, 400);
	LINEMGR->Create_Line(1130, 400, 1150, 395);
	LINEMGR->Create_Line(1150, 395, 1200, 395);
	LINEMGR->Create_Line(1200, 395, 1230, 400);
	LINEMGR->Create_Line(1230, 400, 1290, 405);
	LINEMGR->Create_Line(1290, 405, 1320, 415);
	LINEMGR->Create_Line(1320, 415, 1400, 470);
	LINEMGR->Create_Line(1400, 470, 1450, 510);
	LINEMGR->Create_Line(1450, 510, 1500, 530);
	LINEMGR->Create_Line(1500, 530, 1540, 550);
	LINEMGR->Create_Line(1540, 550, 1570, 560);
	LINEMGR->Create_Line(1570, 560, 1600, 570);
	LINEMGR->Create_Line(1600, 570, 1650, 565);
	LINEMGR->Create_Line(1650, 565, 1690, 560);
	LINEMGR->Create_Line(1690, 560, 1730, 550);
	LINEMGR->Create_Line(1730, 550, 1800, 550);
	LINEMGR->Create_Line(1800, 550, 1870, 565);
	LINEMGR->Create_Line(1870, 565, 1910, 570);
	LINEMGR->Create_Line(1910, 570, 1930, 560);
	LINEMGR->Create_Line(1930, 560, 1950, 550);
	LINEMGR->Create_Line(1950, 550, 2000, 530);
	LINEMGR->Create_Line(2000, 530, 2030, 525);
	LINEMGR->Create_Line(2030, 525, 2070, 520);
	LINEMGR->Create_Line(2070, 520, 2090, 510);
	LINEMGR->Create_Line(2090, 510, 2130, 500);
	LINEMGR->Create_Line(2130, 500, 2190, 500);
	LINEMGR->Create_Line(2190, 500, 2230, 515);
	LINEMGR->Create_Line(2230, 515, 2350, 540);
	LINEMGR->Create_Line(2350, 540, 2440, 545);
	LINEMGR->Create_Line(2440, 545, 2480, 540);
	LINEMGR->Create_Line(2480, 540, 2520, 540);
	LINEMGR->Create_Line(2520, 540, 2570, 545);
	LINEMGR->Create_Line(2570, 545, 2680, 550);
	LINEMGR->Create_Line(2680, 550, 2750, 540);
	LINEMGR->Create_Line(2750, 540, 2770, 530);
	LINEMGR->Create_Line(2770, 530, 2790, 510);
	LINEMGR->Create_Line(2790, 510, 2800, 500);
	LINEMGR->Create_Line(2800, 500, 2860, 350);
	LINEMGR->Create_Line(2860, 350, 2880, 320);
	LINEMGR->Create_Line(2880, 320, 2900, 310);
	LINEMGR->Create_Line(2900, 310, 3000, 300);
}

void CFortress::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	INFO	tTarget_Info = m_pTarget->Get_Info();
	float	fSpeed = m_pTarget->Get_Speed();

	int		iItvX = 50;
	int		iItvY = 50;

	if (iOffSetX + iItvX < tTarget_Info.vPos.x + iScrollX)
	{
		SCROLLMGR->Plus_ScrollX(-fSpeed);
	}

	if (iOffSetX - iItvX > tTarget_Info.vPos.x + iScrollX)
	{
		SCROLLMGR->Plus_ScrollX(fSpeed);
	}

	if (iOffSetY - iItvY > tTarget_Info.vPos.y + iScrollY)
	{
		SCROLLMGR->Plus_ScrollY(fSpeed);
	}

	if (iOffSetY + iItvY < tTarget_Info.vPos.y + iScrollY)
	{
		SCROLLMGR->Plus_ScrollY(-fSpeed);
	}
}

