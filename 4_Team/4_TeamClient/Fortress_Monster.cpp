#include "stdafx.h"
#include "Fortress_Monster.h"
#include "FortressFactory.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"


CFortress_Monster::CFortress_Monster()
	: m_iHp(100)
	, m_iRandom_Move(0)
	, m_fRandom(0.f)
	, m_bRandom(true)
	, m_bRandom_Move(true)
	, m_bShoot(true)
	, m_bMonster_Turn(false)
	, m_bMove_On(true)
	, m_dwShootCount(GetTickCount())
	, m_dwShootDelay(GetTickCount())
	, Fortress_Monster_Bullet(nullptr)
	, pJunPlayer(nullptr)
{
}


CFortress_Monster::~CFortress_Monster()
{
	Release();
}

void CFortress_Monster::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	srand(unsigned(time(NULL)));

	m_tInfo.vPos = { 1200 , 200.f , 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_tInfo_Body_Local[0].vPos = { -50.f , -30.f , 0.f };
	m_tInfo_Body_Local[1].vPos = { +50.f , -30.f , 0.f };
	m_tInfo_Body_Local[2].vPos = { +50.f , +30.f , 0.f };
	m_tInfo_Body_Local[3].vPos = { -50.f , +30.f , 0.f };


	m_tInfo_Posin_Local[0].vPos = { 0.f , 0.f, 0.f };
	m_tInfo_Posin_Local[1].vPos = { -50.f , 0.f, 0.f };

	m_fSpeed = 5.f;
	m_fAngle = 0.f;
	m_fAngle_Body = 0.f;
	m_fAngle_Posin = 0.f;
}

const int CFortress_Monster::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matRotZ;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);


	// 이동행렬 생성 인포의 포스x , y == 400 , 300 , 그리고 matTrans에 대입 == 위치값
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	// Z 중심축으로 대입된 앵글바디값을 RotZ 에 대입 == 방향, 앵글 값
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body));

	// 월드 변환을 위한 행렬에 matRotZ 와 matTrans 곱한후에 더한다.
	m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		// 최종적인 위치벡터를 반환 해준다 (월드 변환을 위한 행렬에 인포타입 바디 로컬의 포스를 곱하기를 한후에 바디 월드의 포스에 대입 )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i].vPos, &m_tInfo_Body_Local[i].vPos, &m_tInfo.matWorld);
	}

	// 포신의 앵글값 , 몸체의 앵글값을 더한 값을 matRotZ 에 대입
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body + m_fAngle_Posin));

	// 월드 변환을 위한 행렬에 matRoz(앵글 값) * matTrans(이동행렬== 위치)
	m_PosinWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 2; ++i)
	{
		// 최종적인 위치 벡터를 반환 해준다 ( 월드 변환을 위한 행렬에 인포포신 로컬을 곱한후에 포신월드에 대입
		D3DXVec3TransformCoord(&m_tInfo_Posin_World[i].vPos, &m_tInfo_Posin_Local[i].vPos, &m_PosinWorld);
	}

	CFortress* pFortress = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
	if (pFortress->Get_Monster_Turn() == true && pFortress->Get_JunBulletList()->empty() && SCROLLMGR->Fix_Cheak(this))
	{
		if (m_bMove_On == true)
		{
			Move();
			m_bMove_On = false;
		}
		Shoot_Bullet();
	}

	// 앵글값을 0으로 초기화를 안 시키면 계속 회전함
	m_fAngle = 0.f;

	return 0;
}

void CFortress_Monster::Late_Update(void)
{
}

void CFortress_Monster::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo_Body_World[0].vPos.x + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + iScrollY, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].vPos.x + iScrollX, (int)m_tInfo_Body_World[i].vPos.y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[0].vPos.x + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + iScrollY);

	// 인포값의 원
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 55, (int)m_tInfo.vPos.y - 15, (int)m_tInfo.vPos.x + 5, (int)m_tInfo.vPos.y + 45);
	//Ellipse(hDC, (int)m_tInfo.vPos.x + 25, (int)m_tInfo.vPos.y + 25, (int)m_tInfo.vPos.x + 45, (int)m_tInfo.vPos.y + 45);

	// 전면부를 나타내는 조그마한 점 2개
	Ellipse(hDC, (int)m_tInfo_Body_World[0].vPos.x - 5 + iScrollX, (int)m_tInfo_Body_World[0].vPos.y - 5 + iScrollY, (int)m_tInfo_Body_World[0].vPos.x + 5 + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + 5 + iScrollY);
	

	// 포신
	MoveToEx(hDC, (int)m_tInfo_Posin_World[0].vPos.x + iScrollX, (int)m_tInfo_Posin_World[0].vPos.y + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo_Posin_World[1].vPos.x + iScrollX, (int)m_tInfo_Posin_World[1].vPos.y + iScrollY);
}

void CFortress_Monster::Release(void)
{
}

void CFortress_Monster::Shoot_Bullet()
{
	/*if (m_dwCount + 500 < GetTickCount())
	{
		m_iRandom = rand() % 360;
		m_fAngle_Posin = m_iRandom;
		m_pMonster_Bullet->push_back(CFortressFactory::Create_Fortress_Bullet(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y, m_fAngle_Posin));

		m_dwCount = GetTickCount();
	}*/

	/*if (m_dwShootCount + 1000 < GetTickCount())
	{
		m_fRandom = (float)(rand() % 90);
		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		Fortress_Monster_Bullet->Initialize();
		if (m_fAngle_Posin < m_fRandom)
		{
			++m_fAngle_Posin;
		}
		else if (m_fAngle > m_fRandom)
		{
			--m_fAngle_Posin;
		}
	
		if (m_dwShootDelay + 5000 < GetTickCount())
		{
			Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin + m_fAngle_Body);
			Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
			static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);

			m_dwShootDelay = GetTickCount();
		}
		else
		{
			Safe_Delete<CFortress_Monster_Bullet*>(Fortress_Monster_Bullet);
		}


		m_dwShootCount = GetTickCount();
	}*/
	CFortress* pFortress = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
	if (pJunPlayer != nullptr)
	{
		if (0 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -300 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		{
			if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
			{
				m_fAngle_Posin += 0.f;

				Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
				Fortress_Monster_Bullet->Initialize();
				Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
				Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
				static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
				pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

				pFortress->Set_Monster_Turn(false);
				pFortress->Set_Player_Turn(true);

			}
			else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
			{
				m_fAngle_Posin += 70.f;

				Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
				Fortress_Monster_Bullet->Initialize();
				Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
				Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
				static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
				pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

				pFortress->Set_Monster_Turn(false);
				pFortress->Set_Player_Turn(true);
			}
		}
		else
		{
			Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
			Fortress_Monster_Bullet->Initialize();
			Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
			Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
			static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
			pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

			pFortress->Set_Monster_Turn(false);
			pFortress->Set_Player_Turn(true);
		}
	}
}

void CFortress_Monster::Move()
{
	if (m_bRandom == true)
	{
		m_fRandom = (float)(rand() % 10) + 100;
		m_bRandom = false;
	}
	if (m_bRandom_Move == true)
	{
		m_iRandom_Move = (rand() % 2) + 1;
		m_bRandom_Move = false;
	}
	switch (m_iHp)
	{
	case 4:
		if (1 == m_iRandom_Move)
		{
			m_tInfo.vPos.x -= m_tInfo.vDir.x * 200.f ;
			m_bRandom = true;
			m_bRandom_Move = true;

		}
		else if (2 == m_iRandom_Move)
		{
			m_tInfo.vPos.x += m_tInfo.vDir.x * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;

		}
		break;
	case 3:
		if (1 == m_iRandom_Move)
		{
			m_tInfo.vPos.x -= m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}
		else if (2 == m_iRandom_Move)
		{
			m_tInfo.vPos.x += m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}
		break;
	case 2:
		if (1 == m_iRandom_Move)
		{
			m_tInfo.vPos.x -= m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}
		else if (2 == m_iRandom_Move)
		{
			m_tInfo.vPos.x += m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}

		break;

	case 1:
		if (1 == m_iRandom_Move)
		{
			m_tInfo.vPos.x -= m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}
		else if (2 == m_iRandom_Move)
		{
			m_tInfo.vPos.x += m_tInfo.vDir.x  * 200.f;
			m_bRandom = true;
			m_bRandom_Move = true;
		}

		break;
	}
}
// 난수값을 받고 rnad 값이 포신값보다 작으면 ++포신각도 같아지면 멈추고, 총알 쏘고-> 다른 난수값을 받으면 포신값보다 작으면 내려가고 같아지면 총알 쏘고
