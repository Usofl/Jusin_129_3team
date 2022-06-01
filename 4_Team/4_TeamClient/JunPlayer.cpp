#include "stdafx.h"
#include "JunPlayer.h"
#include "KeyMgr.h"

CJunPlayer::CJunPlayer()
{

}


CJunPlayer::~CJunPlayer()
{

}

void CJunPlayer::Initialize(void)
{
	//m_tInfo.
	//int iArray[4] = { 0,0,50,50 };
	Tank[0] = { -50.f,-50.f,0.f };
	Tank[1] = { 50.f, -50.f,0.f };
	Tank[2] = { 50.f,50.f,0.f };
	Tank[3] = { -50.f,50.f,0.f };

	m_HeadInfo.vPos = { 0.f,-50.f,0.f };
	TankHead[0] = { -1.f,-1.f,0.f };
	TankHead[1] = { 1.f, -1.f,0.f };
	TankHead[2] = { 1.f,1.f,0.f };
	TankHead[3] = { -1.f,1.f,0.f };
	m_tInfo.vPos = { 300.f,300.f,0.f };
	
	//vHeadPos = { m_tInfo.vPo,300.f,0.f };
	//m_tInfo.vDir = { 0.f,1.f,0.f };

	m_tInfo.vLook = { 1.f,0.f,0.f };
	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	
}

const int CJunPlayer::Update(void)
{
	Tank[0] = { -50.f,-30.f,0.f };
	Tank[1] = { 50.f, -30.f,0.f };
	Tank[2] = { 50.f,30.f,0.f };
	Tank[3] = { -50.f,30.f,0.f };
	TankHead[0] = { -20.f,-20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[1] = { 20.f, -20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[2] = { 20.f,20.f + m_HeadInfo.vPos.y,0.f };
	TankHead[3] = { -20.f,20.f + m_HeadInfo.vPos.y,0.f };
	Po = { 100.f, 0.f + m_HeadInfo.vPos.y,0.f };
	Po_One = { 0.f, 0.f + m_HeadInfo.vPos.y,0.f };



	//m_fAngle = 40.f;
	//m_HeadInfo.vPos.y = m_tInfo.vPos.y - 50;
	Key_Input();
	//D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0);
	//D3DXMatrixScaling(&m_HmatScale, 20.f, 20.f, 0);

	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);
	//D3DXMatrixRotationZ(&m_HmatRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	//D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	//D3DXMatrixTranslation(&m_HmatTrans, m_HeadInfo.vPos.x, m_HeadInfo.vPos.y, 0.f);

	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;
	//m_HeadMat = m_HmatScale * m_HmatRotZ* m_HmatTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&Tank[i], &Tank[i], &m_tInfo.matWorld);
		D3DXVec3TransformCoord(&TankHead[i], &TankHead[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformCoord(&Po, &Po, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&Po_One, &Po_One, &m_tInfo.matWorld);

	//m_tInfo.matWorld =  *D3DXMatrixInverse(&m_matRotZ, 0, &m_matRotZ);

	//for (int i = 0; i < 4; ++i)
	//{
	//	D3DXVec3TransformCoord(&TankHead[i], &TankHead[i], &m_HeadMat);
	//}

	
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

	MoveToEx(hDC, Tank[0].x, Tank[0].y,nullptr);
	LineTo(hDC, Tank[1].x, Tank[1].y);
	LineTo(hDC, Tank[2].x, Tank[2].y);
	LineTo(hDC, Tank[3].x, Tank[3].y);
	LineTo(hDC, Tank[0].x, Tank[0].y);


	MoveToEx(hDC, TankHead[0].x, TankHead[0].y, nullptr);
	LineTo(hDC,TankHead[1].x, TankHead[1].y);
	LineTo(hDC, TankHead[2].x, TankHead[2].y);
	LineTo(hDC, TankHead[3].x, TankHead[3].y);
	LineTo(hDC, TankHead[0].x, TankHead[0].y);
	
	MoveToEx(hDC, Po_One.x, Po_One.y, nullptr);
	LineTo(hDC, Po.x , Po.y);
}

void CJunPlayer::Release(void)
{

}

void CJunPlayer::Key_Input(void)
{
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		
		m_fAngle -= D3DXToRadian(3.f);
		
	}

	if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		m_fAngle += D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		//m_HeadInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
	/*if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fAngle += D3DXToRadian(3.f);
	}*/
}

