#include "stdafx.h"
#include "Fortress_Monster_Bullet.h"
#include "ScrollMgr.h"

CFortress_Monster_Bullet::CFortress_Monster_Bullet()
	: m_fShoot_Power(10.f)
	, m_fAir_Shoot(0.f)
	, m_vDir_X(NORMALVECTOR_X)
{
}


CFortress_Monster_Bullet::~CFortress_Monster_Bullet()
{
	Release();
}

void CFortress_Monster_Bullet::Initialize(void)
{
	m_tInfo.vPos = { 100.f ,100, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f , 1.f , 0.f };

	m_tInfo_Bullet_Local[0] = { -60.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[1] = { -20.f , -20.f , 0.f };
	m_tInfo_Bullet_Local[2] = { +60.f , -20.f , 0.f };
	m_tInfo_Bullet_Local[3] = { +60.f , +20.f , 0.f };
	m_tInfo_Bullet_Local[4] = { -20.f ,+20.f , 0.f };
	m_tInfo_Bullet_Local[5] = { -60.f , +10.f , 0.f };
	m_tInfo_Bullet_Local[6] = { +20.f , -20.f , 0.f };
	m_tInfo_Bullet_Local[7] = { +30.f , -30.f , 0.f };
	m_tInfo_Bullet_Local[8] = { +70.f , -30.f , 0.f };
	m_tInfo_Bullet_Local[9] = { +20.f , +20.f , 0.f };
	m_tInfo_Bullet_Local[10] = { +30.f , +30.f , 0.f };
	m_tInfo_Bullet_Local[11] = { +70.f , +30.f , 0.f };



	m_fSpeed = 1.f;

	m_fAngle = 0.f;
}

const int CFortress_Monster_Bullet::Update(void)
{	
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	for (int i = 0; i < 12; ++i)
	{
		m_tInfo_Bullet_World[i] = m_tInfo_Bullet_Local[i];
	}

	D3DXVECTOR3 m_vPos_Move_A = m_tInfo.vPos;	// 처음 총알

	m_fAir_Shoot += 0.016f;

	Bullet_Move();		// 총알 이동

	D3DXVECTOR3	m_vPos_Move_B = m_tInfo.vPos;	// 두번째 총알

	D3DXVECTOR3 m_vPos_Move_C = m_vPos_Move_B - m_vPos_Move_A; // 방향백터 구하기

	D3DXVec3Normalize(&m_vPos_Move_C, &m_vPos_Move_C);	// 정규화 단위벡터로

	float	fTemp = 0.f;

	if (m_vPos_Move_B.y > m_vPos_Move_A.y)
	{
		fTemp = D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);		// 정규화된 방향벡터와, 지형 지면의 x방향벡터
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);		// 크기 변환 행렬 생성함수
		m_fAngle = acosf(fTemp);
	}
	else
	{
		fTemp = -D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);
		D3DXMatrixScaling(&m_matScale, -1.f, 1.f, 0.f);
		m_fAngle = acosf(fTemp);
	}

	if (m_vPos_Move_B.y > m_vPos_Move_A.y)
	{
		fTemp = -D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);		// 정규화된 방향벡터와, 지형 지면의 x방향벡터
		D3DXMatrixScaling(&m_matScale, -1.f, 1.f, 0.f);		// 크기 변환 행렬 생성함수
		m_fAngle = -acosf(fTemp);
	}
	//////////////////////////////////////////////////////
	/*if (m_vPos_Move_B.y < m_vPos_Move_A.y)
	{
		fTemp = D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);		// 정규화된 방향벡터와, 지형 지면의 x방향벡터
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);		// 크기 변환 행렬 생성함수
		m_fAngle = acosf(fTemp);
	}
	else
	{
		fTemp = D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
		m_fAngle = acosf(fTemp);
	}

	if (m_vPos_Move_B.y > m_vPos_Move_A.y)
	{
		fTemp = D3DXVec3Dot(&m_vPos_Move_C, &m_vDir_X);		// 정규화된 방향벡터와, 지형 지면의 x방향벡터
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);		// 크기 변환 행렬 생성함수
		m_fAngle = -acosf(fTemp);
	}*/
	

	
	


	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, (m_fAngle));
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 12; ++i)
	{
		D3DXVec3TransformCoord(&m_tInfo_Bullet_World[i], &m_tInfo_Bullet_Local[i], &m_tInfo.matWorld);
	}

	return OBJ_NOEVENT;
}

void CFortress_Monster_Bullet::Late_Update(void)
{
}

void CFortress_Monster_Bullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo_Bullet_World[0].x + iScrollX, (int)m_tInfo_Bullet_World[0].y + iScrollY, nullptr);	// 몸통
	for (int i = 0; i < 6; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].x + iScrollX, (int)m_tInfo_Bullet_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[0].x + iScrollX, (int)m_tInfo_Bullet_World[0].y + iScrollY);
	
	MoveToEx(hDC, (int)m_tInfo_Bullet_World[6].x + iScrollX, (int)m_tInfo_Bullet_World[6].y + iScrollY, nullptr);	// 윗날개
	for (int i = 6; i < 9; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].x + iScrollX, (int)m_tInfo_Bullet_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[2].x + iScrollX, (int)m_tInfo_Bullet_World[2].y + iScrollY);

	MoveToEx(hDC, (int)m_tInfo_Bullet_World[9].x + iScrollX, (int)m_tInfo_Bullet_World[9].y + iScrollY, nullptr);	// 아랫날개
	for (int i = 9; i < 12; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].x + iScrollX, (int)m_tInfo_Bullet_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[3].x + iScrollX, (int)m_tInfo_Bullet_World[3].y + iScrollY);
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);

	MoveToEx(hDC, (int)m_tInfo_Bullet_World[1].x + iScrollX, (int)m_tInfo_Bullet_World[1].y + iScrollY, nullptr);	// 아랫날개
	LineTo(hDC, (int)m_tInfo_Bullet_World[4].x + iScrollX, (int)m_tInfo_Bullet_World[4].y + iScrollY);
}

void CFortress_Monster_Bullet::Release(void)
{
}

void CFortress_Monster_Bullet::Bullet_Move()
{


	if (0 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -100 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 2;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (0 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 100 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 2;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;

	}
	else if (-100 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -200 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 3;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (100 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 200 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 3;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-200 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -400 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 4;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (200 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 400 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 4;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-400 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -600 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 4.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (400 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 600 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 4.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-600 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -800 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 5.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (600 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 800 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 5.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-800 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -1000 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 6.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (800 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 1000 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 6.5;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-1000 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -1200 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 7;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;

	}
	else if (1000 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 1200 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 7;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-1200 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -1400 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 8;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (1200 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x && 1400 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 8;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-1400 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -1600 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 9;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (1400 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 1600 > pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 9;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (-1600 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (1600 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}





	/*m_fSpeed = 5;
	m_tInfo.vPos +=  m_tInfo.vLook * m_fSpeed;
	m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;*/
	m_tInfo.vPos.y += (0.5f * 9.8f * m_fAir_Shoot * m_fAir_Shoot);
}


