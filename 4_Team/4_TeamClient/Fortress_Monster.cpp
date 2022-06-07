#include "stdafx.h"
#include "Fortress_Monster.h"
#include "FortressFactory.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "Fortress.h"


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
	, m_bMyTurn(false)
	, m_iMoveCount(0)
	, m_iRandomDir(0)
	, m_bMove(true)
	

	/*, m_pFortress(nullptr)*/
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
	//m_pFortress = dynamic_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
	m_tInfo.vPos = { 1200 , 200.f , 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_tInfo_Body_Local[0] = { -144.f , -70.f , 0.f };
	m_tInfo_Body_Local[1] = { -70.f , -70.f , 0.f };
	m_tInfo_Body_Local[2] = { -35.f , 0.f , 0.f };
	m_tInfo_Body_Local[3] = { +35.f , 0.f , 0.f };
	m_tInfo_Body_Local[4] = { +70.f , -70.f , 0.f };
	m_tInfo_Body_Local[5] = { +140.f , -70.f , 0.f };
	m_tInfo_Body_Local[6] = { +125.f , 0.f , 0.f };
	m_tInfo_Body_Local[7] = { +105.f , 0.f , 0.f };
	m_tInfo_Body_Local[8] = { +70.f , +70.f , 0.f };
	m_tInfo_Body_Local[9] = { -70.f , +70.f , 0.f };
	m_tInfo_Body_Local[10] = { -105.f , +0.f , 0.f };
	m_tInfo_Body_Local[11] = { -125.f , +0.f , 0.f };
	m_tInfo_Body_Local[12] = { -25.f , -35.f , 0.f };
	m_tInfo_Body_Local[13] = { +25.f , -35.f , 0.f };
	m_tInfo_Body_Local[14] = { +25.f , 0.f , 0.f };
	m_tInfo_Body_Local[15] = { -25.f , 0.f , 0.f };

	m_tInfo_Posin_Local[0] = { -17.f, -140.f, 0.f };
	m_tInfo_Posin_Local[1] = {	+0.f, -140.f, 0.f };
	m_tInfo_Posin_Local[2] = { +17.f, -140.f, 0.f };
	m_tInfo_Posin_Local[3] = { +20.f , -35.f, 0.f };
	m_tInfo_Posin_Local[4] = { -20.f , -35.f, 0.f };

	m_tInfo_Test_Dir = { 0.f , 0.f , 0.f };

	m_fSpeed = 5.f;
	m_fAngle = 0.f;
	m_fAngle_Body = 0.f;
	m_fAngle_Posin = 0.f;
	//m_iRandomDir
	m_iBeforeHp = m_iHp;

}

const int CFortress_Monster::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}
	if (nullptr != pJunPlayer)
	{
		m_tInfo_Test_Dir = pJunPlayer->Get_Info().vPos - m_tInfo_Posin_World[1];
		D3DXVec3Normalize(&m_tInfo_Test_Dir, &m_tInfo_Test_Dir);
	}

	Move();
	

	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matRotZ;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);


	// 이동행렬 생성 인포의 포스x , y == 400 , 300 , 그리고 matTrans에 대입 == 위치값
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	// Z 중심축으로 대입된 앵글바디값을 RotZ 에 대입 == 방향, 앵글 값
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body));

	// 월드 변환을 위한 행렬에 matRotZ 와 matTrans 곱한후에 더한다.
	m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 16; ++i)
	{
		// 최종적인 위치벡터를 반환 해준다 (월드 변환을 위한 행렬에 인포타입 바디 로컬의 포스를 곱하기를 한후에 바디 월드의 포스에 대입 )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i], &m_tInfo_Body_Local[i], &m_tInfo.matWorld);
	}

	D3DXMatrixTranslation(&matTrans_Posin, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	// 포신의 앵글값 , 몸체의 앵글값을 더한 값을 matRotZ 에 대입
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body + m_fAngle_Posin));

	// 월드 변환을 위한 행렬에 matRoz(앵글 값) * matTrans(이동행렬== 위치)
	m_PosinWorld = m_tMatInfo.matRotZ * matTrans_Posin;


	for (int i = 0; i < 5; ++i)
	{
		// 최종적인 위치 벡터를 반환 해준다 ( 월드 변환을 위한 행렬에 인포포신 로컬을 곱한후에 포신월드에 대입
		D3DXVec3TransformCoord(&m_tInfo_Posin_World[i], &m_tInfo_Posin_Local[i], &m_PosinWorld);
	}

	/*CFortress* pFortress = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));*/
	/*if (m_pFortress->Get_Monster_Turn() == true && m_pFortress->Get_JunBulletList()->empty() && SCROLLMGR->Fix_Cheak(this))*/
	{
		/*if (m_bMove_On == true && m_dwShootCount + 1000 < GetTickCount())
		{
			Move();
			m_bMove_On = false;
		}
		if (m_dwShootDelay + 5000 < GetTickCount())
		{
			Shoot_Bullet();
			m_dwShootDelay = GetTickCount();
		}*/

	}

	//if (nullptr != pJunPlayer)
	//{
	//	m_tInfo_Test_Dir = pJunPlayer->Get_Info().vPos - m_tInfo_Posin_World[1];
	//	D3DXVec3Normalize(&m_tInfo_Test_Dir, &m_tInfo_Test_Dir);
	//}
	//
	// 앵글값을 0으로 초기화를 안 시키면 계속 회전함
	m_fAngle = 0.f;
	Shoot_Bullet();
	return 0;
}

void CFortress_Monster::Late_Update(void)
{
}

void CFortress_Monster::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//  배 몸통
	MoveToEx(hDC, (int)m_tInfo_Body_World[0].x + iScrollX, (int)m_tInfo_Body_World[0].y + iScrollY, nullptr);
	for (int i = 0; i < 12; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].x + iScrollX, (int)m_tInfo_Body_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[0].x + iScrollX, (int)m_tInfo_Body_World[0].y + iScrollY);

	MoveToEx(hDC, (int)m_tInfo_Body_World[12].x + iScrollX, (int)m_tInfo_Body_World[12].y + iScrollY, nullptr);
	for (int i = 12; i < 16; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].x + iScrollX, (int)m_tInfo_Body_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[12].x + iScrollX, (int)m_tInfo_Body_World[12].y + iScrollY);



	// 인포값의 원
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 55, (int)m_tInfo.vPos.y - 15, (int)m_tInfo.vPos.x + 5, (int)m_tInfo.vPos.y + 45);
	//Ellipse(hDC, (int)m_tInfo.vPos.x + 25, (int)m_tInfo.vPos.y + 25, (int)m_tInfo.vPos.x + 45, (int)m_tInfo.vPos.y + 45);

	// 전면부를 나타내는 조그마한 점 2개
	Ellipse(hDC, (int)m_tInfo_Body_World[0].x - 5 + iScrollX, (int)m_tInfo_Body_World[0].y - 5 + iScrollY, (int)m_tInfo_Body_World[0].x + 5 + iScrollX, (int)m_tInfo_Body_World[0].y + 5 + iScrollY);
	

	// 포신
	MoveToEx(hDC, (int)m_tInfo_Posin_World[0].x + iScrollX, (int)m_tInfo_Posin_World[0].y + iScrollY, nullptr);
	for (int i = 0; i < 5; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Posin_World[i].x + iScrollX, (int)m_tInfo_Posin_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Posin_World[0].x + iScrollX, (int)m_tInfo_Posin_World[0].y + iScrollY);
}

void CFortress_Monster::Release(void)
{
}

void CFortress_Monster::Shoot_Bullet()
{
	if (!m_bMyTurn || m_iMoveCount < 200)
		return;

	
	
	if (nullptr == Fortress_Monster_Bullet/*pFortress->Get_Monster_Bullet_List()->empty()*/)
	{
		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		Fortress_Monster_Bullet->Initialize();
		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		
		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		CFortress* pFortress = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
		pFortress->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());
		m_iRandomDir = rand() % 2;
		m_bMove = false;
		m_iBeforeHp = m_iHp;
	}
	m_iMoveCount = 0;
	
#pragma region 민성이 코드
	// 플레이어 - 몬스터 == 0 ~ -300
	//if (0 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -300 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 80.f;
	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());


	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);

	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 0.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//// 플레이어 - 몬스터 == 0 ~ 300
	//else if (0 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 100.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);

	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 170.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//// 플레이어 - 몬스터 == -300 ~ -600
	//else if (-300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -600 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 70.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 20.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//// 플레이어 - 몬슽터 == 300 ~ 600
	//else if (300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 600 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 110.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 160.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//else if (-600 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -900 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 60.f;

		/*	Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
			Fortress_Monster_Bullet->Initialize();
			Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
			Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
			Fortress_Monster_Bullet->Set_Player(pJunPlayer);
			Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
			Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
			static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
			pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());*/

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 60.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//else if (600 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 900 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 120.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 120.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//else if (-900 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 50.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 50.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
	//else if (900 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	//{
	//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 130.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
	//	{
	//		//m_fAngle_Posin = 130.f;

	//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
	//		Fortress_Monster_Bullet->Initialize();
	//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
	//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
	//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
	//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
	//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
	//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
	//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

	//		pFortress->Set_Monster_Turn(false);
	//		pFortress->Set_Player_Turn(true);
	//	}
	//}
#pragma endregion 민성이 코드
	

#pragma endregion 민성이 코드

#pragma region 코드
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


	//CFortress* pFortress = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
#pragma endregion 코드
	
	if (nullptr != pJunPlayer)
	{
		if (m_bMyTurn)
		{

		}
#pragma region 민성이 코드
		// 플레이어 - 몬스터 == 0 ~ -300
		//if (0 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -300 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 80.f;
		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());


		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);

		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 0.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//// 플레이어 - 몬스터 == 0 ~ 300
		//else if (0 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 100.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);

		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 170.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//// 플레이어 - 몬스터 == -300 ~ -600
		//else if (-300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -600 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 70.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 20.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//// 플레이어 - 몬슽터 == 300 ~ 600
		//else if (300 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 600 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 110.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 160.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//else if (-600 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && -900 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 60.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 60.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//else if (600 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 900 < pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 120.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 120.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//else if (-900 >= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 50.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 50.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}
		//else if (900 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
		//{
		//	if (pJunPlayer->Get_Info().vPos.y <= m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 130.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//	else if (pJunPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
		//	{
		//		//m_fAngle_Posin = 130.f;

		//		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		//		Fortress_Monster_Bullet->Initialize();
		//		Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
		//		Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].x, m_tInfo_Posin_World[1].y);
		//		Fortress_Monster_Bullet->Set_Player(pJunPlayer);
		//		Fortress_Monster_Bullet->Get_Monster_Dir(m_tInfo_Test_Dir);
		//		Fortress_Monster_Bullet->Get_Monster_PosX(m_tInfo.vPos.x);
		//		static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
		//		pFortress->Set_Target(pFortress->Get_Monster_Bullet_List()->back());

		//		pFortress->Set_Monster_Turn(false);
		//		pFortress->Set_Player_Turn(true);
		//	}
		//}

#pragma endregion 민성이 코드

		
	}
}

void CFortress_Monster::Move()
{
	if (!m_bMyTurn || !m_bMove)
		return;
	if (m_iMoveCount < 200)
	{
		if (m_iBeforeHp > m_iHp)
		{
			if (pJunPlayer->Get_Info().vPos.x > m_tInfo.vPos.x)
			{
				m_tInfo.vPos -= {6.0f, 0.f, 0.f};
			}
			else
			{
				m_tInfo.vPos += {6.0f, 0.f, 0.f};
			}
			m_iMoveCount+=4;
			return;
			
		}

		if (m_tInfo.vPos.x > 2700.f)
		{
			m_tInfo.vPos -= {1.5f, 0.f, 0.f};
			m_iMoveCount++;
			return;
		}

		if (m_iRandomDir == 0)
		{
			m_tInfo.vPos += {1.5f, 0.f, 0.f};
		}

		else
		{
			m_tInfo.vPos -= {1.5f, 0.f, 0.f};
		}
		m_iMoveCount++;
	}
	
#pragma region 민성이 코드
	/*if (m_bRandom == true)
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
	case 80:
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
	case 60:
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
	case 40:
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

	case 20:
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
	}*/
#pragma endregion 민성이 코드
	
}
// 난수값을 받고 rnad 값이 포신값보다 작으면 ++포신각도 같아지면 멈추고, 총알 쏘고-> 다른 난수값을 받으면 포신값보다 작으면 내려가고 같아지면 총알 쏘고
