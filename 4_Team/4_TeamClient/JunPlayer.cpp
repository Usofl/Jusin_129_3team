#include "stdafx.h"
#include "JunPlayer.h"
#include "KeyMgr.h"

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
	//m_tInfo.
	//int iArray[4] = { 0,0,50,50 };
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
	m_fSpeed = 5.f;
	OriPo_Dir = { 1.f,0.f,0.f };
	
}

const int CJunPlayer::Update(void)
{
	//float BeforePoAngle = m_fPoAngle ;
	Tank[0] = { -50.f,-30.f,0.f };
	Tank[1] = { 50.f, -30.f,0.f };
	Tank[2] = { 50.f,30.f,0.f };
	Tank[3] = { -50.f,30.f,0.f };
	/*TankHead[0] = { -20.f,-20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[1] = { 20.f, -20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[2] = { 20.f,20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[3] = { -20.f,20.f + m_HeadInfo.vPos.y,0.f };*/

	TankHead[0] = { -20.f,-50.f-20.f ,0.f };
	TankHead[1] = { 20.f, -50.f-20.f  ,0.f };
	TankHead[2] = { 20.f,-50.f + 20.f  ,0.f };
	TankHead[3] = { -20.f,-50.f +20.f,0.f };
	Po = { 80.f, 0.f ,0.f };
	




	Po_One = { 0, -50.f,0.f };

	Key_Input();
	

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

	D3DXVec3TransformNormal(&Po_Dir, &OriPo_Dir, &m_HeadInfo.matWorld);

	if (KEYMGR->Key_Up(VK_SPACE))
	{

		Bullet = new CJunBullet;
		Bullet->Initialize();
		Bullet->Set_Pos_Dir(Po.x, Po.y, Po_Dir);
 		BulletList.push_back(Bullet);
		int i = 5;
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

	MoveToEx(hDC, (int)Tank[0].x, (int)Tank[0].y,nullptr);
	LineTo(hDC, (int)Tank[1].x, (int)Tank[1].y);
	LineTo(hDC, (int)Tank[2].x, (int)Tank[2].y);
	LineTo(hDC, (int)Tank[3].x, (int)Tank[3].y);
	LineTo(hDC, (int)Tank[0].x, (int)Tank[0].y);


	MoveToEx(hDC, (int)TankHead[0].x, (int)TankHead[0].y, nullptr);
	LineTo(hDC, (int)TankHead[1].x, (int)TankHead[1].y);
	LineTo(hDC, (int)TankHead[2].x, (int)TankHead[2].y);
	LineTo(hDC, (int)TankHead[3].x, (int)TankHead[3].y);
	LineTo(hDC, (int)TankHead[0].x, (int)TankHead[0].y);
	Ellipse(hDC, (int)TankHead[1].x - 5, (int)TankHead[1].y - 5, (int)TankHead[1].x + 5, (int)TankHead[1].y + 5);



	Ellipse(hDC, (int)Po_One.x - 5, (int)Po_One.y - 5, (int)Po_One.x + 5, (int)Po_One.y + 5);
	MoveToEx(hDC, (int)Po_One.x, (int)Po_One.y, nullptr);
	LineTo(hDC, (int)Po.x , (int)Po.y);

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
		
		m_fPoAngle -= D3DXToRadian(3.f);
		m_fAngle -= D3DXToRadian(3.f);
		//m_fPoAngle += D3DXToRadian(3.f);

		
	}

	if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		m_fPoAngle += D3DXToRadian(3.f);
		m_fAngle += D3DXToRadian(3.f);
		//m_fPoAngle -= D3DXToRadian(3.f);

	}

	if (KEYMGR->Key_Pressing(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing('A'))
	{
		m_fPoAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing('D'))
	{
		m_fPoAngle += D3DXToRadian(3.f);
	}

	

	/*if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fAngle += D3DXToRadian(3.f);
	}*/
}

