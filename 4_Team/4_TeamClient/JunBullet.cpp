#include "stdafx.h"
#include "JunBullet.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CJunBullet::CJunBullet():
	m_BulletID(BULLET_END),
	vSu(NORMALVECTOR_X),
	m_vDpDir(NORMALVECTOR_X),
	m_vOne(NORMALVECTOR_X)
{
	ZeroMemory(m_vLocalPoint, sizeof(m_vLocalPoint));
}


CJunBullet::~CJunBullet()
{
	Release();
}

void CJunBullet::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_vLocalPoint[0] = { -20.f,-10.f,0.f };
	m_vLocalPoint[1] = {  20.f, -10.f,0.f };
	m_vLocalPoint[2] = {  25.f, -6.f,0.f };
	m_vLocalPoint[3] = {  27.5f, 0.f,0.f };
	m_vLocalPoint[4] = {  25.f,  6.f,0.f };
	m_vLocalPoint[5] = {  20.f, 10.f,0.f };
	m_vLocalPoint[6] = { -20.f, 10.f,0.f };
	

	m_tInfo.vDir = NORMALVECTOR_X;

	m_fAngle = 0.f;
	m_fTempTime = 0.f;

	int i = 5;

	for (int i = 0; i < 10; ++i)
	{
		m_DpBullet[i] = nullptr;
	}
	
}

const int CJunBullet::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	for (int i = 0; 7 > i; ++i)
	{
		m_vWorldPoint[i] = m_vLocalPoint[i];
	}

	D3DXVECTOR3  m_vTemp = m_tInfo.vPos;

	float fTempAngle = m_fAngle;
	m_fTempTime += 0.016f;

	m_fFallValue = m_tInfo.vPos.y;
	Move();

	D3DXVECTOR3  m_vTemp2 = m_tInfo.vPos;

	D3DXVECTOR3 m_vTemp3 = m_vTemp2 - m_vTemp;

	D3DXVec3Normalize(&m_vTemp3, &m_vTemp3);
	
	/*if(D3DXVec3Dot(&m_vTemp3, &vSu) > D3DX_PI)
		m_fAngle = */
	float fSour = 0.f;

	//노력의 결과니까 혼내지 않기로 약속~
	if (m_vTemp2.y > m_vTemp.y)
	{
		fSour = D3DXVec3Dot(&m_vTemp3, &vSu);
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	}
	else
	{
		fSour = -D3DXVec3Dot(&m_vTemp3, &vSu);
		D3DXMatrixScaling(&m_matScale, -1.f, 1.f, 0.f);
	}
	
	/*if (-1 > fSour || 1 < fSour)
		fSour *= -1;*/
	m_fAngle = acosf(fSour);
	//m_fAngle = acosf(D3DXVec3Dot(&vSu, &_vOne));
	
	int i = 5;

	//D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

	//D3DXMatrixScaling();

	//D3DXVec3TransformNormal(&m_vDpDir, &m_vDpDir, &m_tInfo.matWorld);
	for (int i = 0; 7 > i; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vWorldPoint[i], &m_tInfo.matWorld);
	}
	return 0;
}

void CJunBullet::Late_Update(void)
{
	if (KEYMGR->Key_Down('F'))
	{
		//D3DXVECTOR3 vTemp = { 0.3f,0.3f,0.f };
	}
}

void CJunBullet::Render(HDC hDC)
{
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10, (int)m_tInfo.vPos.y - 10, (int)m_tInfo.vPos.x + 10, (int)m_tInfo.vPos.y + 10);
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	switch (m_BulletID)
	{
	case BULLET_BASIC:
		
		break;
	case BULLET_DP:
		//테스트용 DP
		//Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX + 100, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX + 100, (int)m_tInfo.vPos.y + 10 + iScrollY);
		break;
	case BULLET_END:
		break;
	}


	MoveToEx(hDC, (int)m_vWorldPoint[0].x + iScrollX, (int)m_vWorldPoint[0].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vWorldPoint[1].x+ iScrollX, (int)m_vWorldPoint[1].y+ iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[2].x+ iScrollX, (int)m_vWorldPoint[2].y+ iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[3].x + iScrollX, (int)m_vWorldPoint[3].y + iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[4].x + iScrollX, (int)m_vWorldPoint[4].y + iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[5].x + iScrollX, (int)m_vWorldPoint[5].y + iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[6].x+ iScrollX, (int)m_vWorldPoint[6].y+ iScrollY);
	LineTo(hDC, (int)m_vWorldPoint[0].x+ iScrollX, (int)m_vWorldPoint[0].y+ iScrollY);
									  


	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);

}

void CJunBullet::Release(void)
{

}

void CJunBullet::Move(void)
{
	/*	m_tInfo.vPos.x += iBulletDir * (m_fSpeed * cosf(m_fAngle) * m_fTempTime);
		m_tInfo.vPos.y -= (m_fSpeed * sinf(m_fAngle) * m_fTempTime) - (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
	*/
	//int i;
	switch (m_BulletID)
	{
	case BULLET_BASIC:
		m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;
		m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
		//i = 5;
		break;
	case BULLET_DP:
		m_tInfo.vPos += m_fSpeed* m_tInfo.vDir;
		m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
		break;
	case BULLET_END:
		break;
	}	
}
