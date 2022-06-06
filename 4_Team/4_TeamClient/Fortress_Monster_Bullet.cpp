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

	/*m_tInfo_Bullet_Local[0].vPos = { -10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[1].vPos = { +10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[2].vPos = { +10.f , +10.f , 0.f };
	m_tInfo_Bullet_Local[3].vPos = { -10.f , +10.f , 0.f };*/

	m_fSpeed = 1.f;
}

const int CFortress_Monster_Bullet::Update(void)
{	
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	/*D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_tInfo_Bullet_World[i].vPos, &m_tInfo_Bullet_Local[i].vPos, &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);*/

	m_fAir_Shoot += 0.02f;

	/*if (0 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -300 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 5;
		m_tInfo.vPos -= m_fSpeed * m_tInfo.vLook;
	}
	else if (0 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 300 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 5;
		m_tInfo.vPos += m_fSpeed * m_tInfo.vLook;
	}
	else if (-300 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -600 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos -= m_fSpeed * m_tInfo.vLook;
	}
	else if (300 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 600 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 10;
		m_tInfo.vPos += m_fSpeed * m_tInfo.vLook;
	}
	else if (-600 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && -900 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 15;
		m_tInfo.vPos -= m_fSpeed * m_tInfo.vLook;
	}
	else if (600 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX && 900 < pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 15;
		m_tInfo.vPos += m_fSpeed * m_tInfo.vLook;
	}*/
	if (-900 >= pJunPlayer->Get_Info().vPos.x - m_fMonster_PosX)
	{
		m_fSpeed = 20;
		m_tInfo.vPos.x -= m_tInfo.vLook.x;
	}
	else if (900 <= pJunPlayer->Get_Info().vPos.x - m_tInfo.vPos.x)
	{
		m_fSpeed = 20;
		m_tInfo.vPos +=  m_tInfo.vLook;
	}

	m_tInfo.vPos.y -= m_fShoot_Power * m_fAir_Shoot - 0.5f *9.8f * m_fAir_Shoot * m_fAir_Shoot;
	
	return OBJ_NOEVENT;
}

void CFortress_Monster_Bullet::Late_Update(void)
{
}

void CFortress_Monster_Bullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	/*MoveToEx(hDC, (int)m_tInfo_Bullet_World[0].vPos.x, (int)m_tInfo_Bullet_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].vPos.x, (int)m_tInfo_Bullet_World[i].vPos.y);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[0].vPos.x, (int)m_tInfo_Bullet_World[0].vPos.y);*/

	Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);
}

void CFortress_Monster_Bullet::Release(void)
{
}


