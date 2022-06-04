#include "stdafx.h"
#include "JunPlayer.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CJunPlayer::CJunPlayer():m_iAngleCount(0)
{
	Initialize();
}


CJunPlayer::~CJunPlayer()
{
	Release();
}

void CJunPlayer::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	//m_tInfo.
	//int iArray[4] = { 0,0,50,50 };
	//SCENEMGR->Get_Instance()->
	Tank[0] = { -50.f,-50.f,0.f };
	Tank[1] = { 50.f, -50.f,0.f };
	Tank[2] = { 50.f,50.f,0.f };
	Tank[3] = { -50.f,50.f,0.f };

	m_HeadInfo.vPos = { 50.f,-50.f,0.f };
	TankHead[0] = { -1.f,-1.f,0.f };
	TankHead[1] = { 1.f, -1.f,0.f };
	TankHead[2] = { 1.f,1.f,0.f };
	TankHead[3] = { -1.f,1.f,0.f };
	m_tInfo.vPos = { 300.f,300.f,0.f };

	m_HeadInfo.vPos = { 300.f,250.f,0.f };
	//vHeadPos = { m_tInfo.vPo,300.f,0.f };
	//m_tInfo.vDir = { 0.f,1.f,0.f };

	m_tInfo.vLook = { 1.f,0.f,0.f };
	m_fAngle = 0.f;
	m_fPoAngle = 0.f;
	BeforeAngle = m_fAngle;
	m_fSpeed = 5.f;
	OriPo_Dir = { 1.f,0.f,0.f };
	m_fShootPower = 0.f;
	m_fTempPower = 0.f;
	m_bMaxPower = true;
	m_bGageRender = false;
}

const int CJunPlayer::Update(void)
{
	//float BeforeAngle = m_fAngle ;
	/*Tank[0] = { -50.f,-30.f,0.f };
	Tank[1] = { 50.f, -30.f,0.f };
	Tank[2] = { 50.f,30.f,0.f };
	Tank[3] = { -50.f,30.f,0.f };*/
	Tank[0] = { -50.f,-30.f - 29.f,0.f };
	Tank[1] = { 50.f, -30.f - 29.f,0.f };
	Tank[2] = { 50.f,30.f - 29.f,0.f };
	Tank[3] = { -50.f,30.f - 29.f,0.f };
	/*TankHead[0] = { -20.f,-20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[1] = { 20.f, -20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[2] = { 20.f,20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[3] = { -20.f,20.f + m_HeadInfo.vPos.y,0.f };*/

	TankHead[0] = { -20.f,-50.f-20.f - 29.f ,0.f };
	TankHead[1] = { 20.f, -50.f-20.f - 29.f  ,0.f };
	TankHead[2] = { 20.f,-50.f + 20.f - 29.f  ,0.f };
	TankHead[3] = { -20.f,-50.f +20.f - 29.f,0.f };
	Po = { 80.f, 0.f ,0.f };
	

	if (BeforeAngle != m_fAngle)
	{
		if (m_fAngle < BeforeAngle)
		{
			m_fPoAngle -= (BeforeAngle - m_fAngle);
		}
		else
		{
			m_fPoAngle += (m_fAngle - BeforeAngle);
		}
		/*else
			m_fPoAngle += (BeforeAngle - m_fAngle);*/
		BeforeAngle = m_fAngle;
	}

	Po_One = { 0, -79.f,0.f };

	Key_Input();
	OffSet();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0);

	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	//m_tInfo.matWorld = m_matScale * m_matRotZ;
	//D3DXVec3TransformCoord(&Po_One, &Po_One, &m_tInfo.matWorld);

	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&Tank[i], &Tank[i], &m_tInfo.matWorld);
		D3DXVec3TransformCoord(&TankHead[i], &TankHead[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformCoord(&Po_One, &Po_One, &m_tInfo.matWorld);
	
	D3DXMatrixRotationZ(&m_HmatRotZ, m_fPoAngle);
	D3DXMatrixTranslation(&m_HmatTrans, Po_One.x, Po_One.y, 0.f);

	m_HeadInfo.matWorld = m_matScale * m_HmatRotZ * m_HmatTrans;

	D3DXVec3TransformCoord(&Po, &Po, &m_HeadInfo.matWorld);

	//D3DXVec3TransformNormal(&Po_Dir, &OriPo_Dir, &m_HeadInfo.matWorld);

	D3DXVECTOR3 TempVec1 = { Po.x - Po_One.x, Po.y - Po_One.y,0.f };
	D3DXVECTOR3 TempVec2 = { 1.f,0.f,0.f };

	D3DXVec3Normalize(&TempVec1, &TempVec1);
	//float fTe = D3DXVec3Dot(&TempVec1, &TempVec2);
	//D3DXVec3Normalize
	if (KEYMGR->Key_Pressing(VK_SPACE))
	{
		m_bGageRender = true;
		if (m_bMaxPower)
		{
			m_fShootPower += 0.4f;
		}
		else
		{
			m_fShootPower -= 0.4f;
		}
		if (m_fShootPower >= 20.f)
		{
			m_bMaxPower = false;
		}
		else if(m_fShootPower <= 0.f)
		{
			m_bMaxPower = true;
		}
		m_fTempPower = m_fShootPower;
	}
	if (KEYMGR->Key_Up(VK_SPACE))
	{
		//fShootPower;
		m_bGageRender = false;
		Bullet = new CJunBullet;
		Bullet->Initialize();
		if (Po_One.x > Po.x)
		{
			Bullet->Set_Pos_Dir(Po.x, Po.y, TempVec1, -1, m_fShootPower);
		}
		//	Bullet->Set_Pos_Dir(Po.x, Po.y, Po_Dir ,-1);
		else
		{
			Bullet->Set_Pos_Dir(Po.x, Po.y, TempVec1, 1, m_fShootPower);
		}

		Bullet->Set_BulletID(BULLET_BASIC);
		static_cast<CFortress*>(SCENEMGR->Get_Instance()->Get_Scene(SC_FORTRESS))->Get_JunBulletList()->push_back(Bullet);
		m_fShootPower = 0.f;
		m_fTempPower = 0.f;
		//int i = 5;
	}
	
 	return 0;
}

void CJunPlayer::Late_Update(void)
{

}

void CJunPlayer::Render(HDC hDC)
{
	//Ellipse(hDC, iArray[0], iArray[1], iArray[2], iArray[3]);
	/*MoveToEx(hDC, 0, 0, nullptr);
	LineTo(hDC,300, 500);*/
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	MoveToEx(hDC, (int)Tank[0].x + iScrollX, (int)Tank[0].y + iScrollY,nullptr);
	LineTo(hDC, (int)Tank[1].x + iScrollX, (int)Tank[1].y + iScrollY);
	LineTo(hDC, (int)Tank[2].x + iScrollX, (int)Tank[2].y + iScrollY);
	LineTo(hDC, (int)Tank[3].x + iScrollX, (int)Tank[3].y + iScrollY);
	LineTo(hDC, (int)Tank[0].x + iScrollX, (int)Tank[0].y + iScrollY);


	MoveToEx(hDC, (int)TankHead[0].x + iScrollX, (int)TankHead[0].y + iScrollY, nullptr);
	LineTo(hDC, (int)TankHead[1].x + iScrollX, (int)TankHead[1].y + iScrollY);
	LineTo(hDC, (int)TankHead[2].x + iScrollX, (int)TankHead[2].y + iScrollY);
	LineTo(hDC, (int)TankHead[3].x + iScrollX, (int)TankHead[3].y + iScrollY);
	LineTo(hDC, (int)TankHead[0].x + iScrollX, (int)TankHead[0].y + iScrollY);
	Ellipse(hDC, (int)TankHead[1].x - 5 + iScrollX, (int)TankHead[1].y - 5 + iScrollY, (int)TankHead[1].x + 5 + iScrollX, (int)TankHead[1].y + 5 + iScrollY);

	Ellipse(hDC, (int)Po_One.x - 5 + iScrollX, (int)Po_One.y - 5 + iScrollY, (int)Po_One.x + 5 + iScrollX, (int)Po_One.y + 5 + iScrollY);
	MoveToEx(hDC, (int)Po_One.x + iScrollX, (int)Po_One.y + iScrollY, nullptr);
	LineTo(hDC, (int)Po.x + iScrollX, (int)Po.y + iScrollY);

	if(m_bGageRender)
	Rectangle(hDC, (int)800/* + iScrollX*/, (int)400 - (m_fTempPower * 10) /*+ iScrollY*/, (int)850/* + iScrollX*/, (int)450 - (m_fTempPower * 10)/*+ iScrollY*/);

	/*MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)Po.x, (int)Po.y);*/
}

void CJunPlayer::Release(void)
{

}

void CJunPlayer::Key_Input(void)
{
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		//m_fAngle -= D3DXToRadian(3.f);
		//m_fPoAngle += D3DXToRadian(3.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		//m_fAngle += D3DXToRadian(3.f);
		//m_fPoAngle -= D3DXToRadian(3.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_UP))
	{
		m_fPoAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fPoAngle += D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing('A'))
	{
		//m_fPoAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing('D'))
	{
		//m_fPoAngle += D3DXToRadian(3.f);
	}

	/*if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fAngle += D3DXToRadian(3.f);
	}*/
}

void CJunPlayer::Shoot(void)
{

}

void CJunPlayer::OffSet(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	int		iItvX = 300;
	int		iItvY = 300;

	if (iOffSetX + iItvX < m_tInfo.vPos.x + iScrollX)
	{
		CScrollMgr::Get_Instance()->Plus_ScrollX(-m_tInfo.vDir.x * m_fSpeed);
	}

	if (iOffSetX - iItvX > m_tInfo.vPos.x + iScrollX)
	{
		CScrollMgr::Get_Instance()->Plus_ScrollX(m_tInfo.vDir.x * m_fSpeed);
	}

	if (iOffSetY - iItvY > m_tInfo.vPos.y + iScrollY)
	{
		CScrollMgr::Get_Instance()->Plus_ScrollY(m_fSpeed);
	}

	if (iOffSetY + iItvY < m_tInfo.vPos.y + iScrollY)
	{
		CScrollMgr::Get_Instance()->Plus_ScrollY(-m_fSpeed);
	}
}