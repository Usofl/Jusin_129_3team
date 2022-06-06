#include "stdafx.h"
#include "Fortress_Monster_Bullet.h"
#include "ScrollMgr.h"

CFortress_Monster_Bullet::CFortress_Monster_Bullet()
	: m_fShoot_Power(10.f)
	, m_fAir_Shoot(0.f)
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

	m_tInfo_Bullet_Local[0] = { 0.f , -40.f , 0.f };
	m_tInfo_Bullet_Local[1] = { +4.f , -33.f , 0.f };
	m_tInfo_Bullet_Local[2] = { +8.f , -26.f , 0.f };
	m_tInfo_Bullet_Local[3] = { +12.f , -19.f , 0.f };
	m_tInfo_Bullet_Local[4] = { +17.f , -12.f , 0.f };
	m_tInfo_Bullet_Local[5] = { +17.f , +40.f , 0.f };
	m_tInfo_Bullet_Local[6] = { -17.f , +40.f , 0.f };
	m_tInfo_Bullet_Local[7] = { -17.f , -12.f , 0.f };
	m_tInfo_Bullet_Local[8] = { -12.f , -19.f , 0.f };
	m_tInfo_Bullet_Local[9] = { -8.f , -26.f , 0.f };
	m_tInfo_Bullet_Local[10] = { -4.f , -33.f , 0.f };



	m_fSpeed = 1.f;
}

const int CFortress_Monster_Bullet::Update(void)
{	
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 11; ++i)
	{
		D3DXVec3TransformCoord(&m_tInfo_Bullet_World[i], &m_tInfo_Bullet_Local[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	m_fAir_Shoot += 0.016f;

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
	else if (-1400 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}
	else if (1400 <= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
		m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	}





	/*m_fSpeed = 5;
	m_tInfo.vPos +=  m_tInfo.vLook * m_fSpeed;
	m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;*/
	m_tInfo.vPos.y += (0.5f * 9.8f * m_fAir_Shoot * m_fAir_Shoot);
	
	return OBJ_NOEVENT;
}

void CFortress_Monster_Bullet::Late_Update(void)
{
}

void CFortress_Monster_Bullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo_Bullet_World[0].x + iScrollX, (int)m_tInfo_Bullet_World[0].y + iScrollY, nullptr);
	for (int i = 0; i < 10; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].x + iScrollX, (int)m_tInfo_Bullet_World[i].y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[0].x + iScrollX, (int)m_tInfo_Bullet_World[0].y + iScrollY);
	
	MoveToEx(hDC, (int)m_tInfo_Bullet_World[4].x + iScrollX, (int)m_tInfo_Bullet_World[4].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo_Bullet_World[7].x + iScrollX, (int)m_tInfo_Bullet_World[7].y + iScrollY);

	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);
}

void CFortress_Monster_Bullet::Release(void)
{
}


