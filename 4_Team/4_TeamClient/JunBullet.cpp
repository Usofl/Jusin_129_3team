#include "stdafx.h"
#include "JunBullet.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CJunBullet::CJunBullet()
{
}


CJunBullet::~CJunBullet()
{
	Release();
}

void CJunBullet::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_BulletID = BULLET_END;

	vPoint[0] = { -20.f,-20.f,0.f };
	vPoint[1] = {  20.f, -20.f,0.f };
	vPoint[2] = {  20.f, 20.f,0.f };
	vPoint[3] = { -20.f, 20.f,0.f };

	vSu = NORMALVECTOR_X;
	m_vDpDir = NORMALVECTOR_X;
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
	vPoint[0] = { -20.f,-20.f,0.f };
	vPoint[1] = { 20.f, -20.f,0.f };
	vPoint[2] = { 20.f, 20.f,0.f };
	vPoint[3] = { -20.f, 20.f,0.f };
	
	m_fTempTime += 0.016f;
	Move();
	m_vDpDir.x = m_tInfo.vPos.x;
	m_vDpDir.y = m_tInfo.vPos.y;

	D3DXVec3Normalize(&m_vDpDir, &m_vDpDir);
	m_fAngle = D3DXVec3Dot(&m_vDpDir, &vSu);
	//m_tInfo.
	//d3dxvector3
	//D3DXVECTOR3Rotation
	//m_tInfo.matWorld = 
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);

	m_tInfo.matWorld = m_matRotZ;

	D3DXVec3TransformNormal(&m_vDpDir, &m_vDpDir, &m_tInfo.matWorld);


	//m_HeadInfo.
	return 0;
}

void CJunBullet::Late_Update(void)
{
	if (KEYMGR->Key_Down('F'))
	{
		D3DXVECTOR3 vTemp = { 0.3f,0.3f,0.f };
		
		/*for (int i = 0; 10 > i; ++i)
		{
			if (m_DpBullet[i] == nullptr)
			{
				m_DpBullet[i] = new CJunBullet;
				m_DpBullet[i]->Initialize();
				m_DpBullet[i]->Set_Pos_Dir(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vDir - (vTemp * i), -1, m_fSpeed);
				m_DpBullet[i]->Update();
				dynamic_cast<CFortress*>(SCENEMGR->Get_Instance()->Get_Scene(SC_FORTRESS))->Get_JunBulletList()->push_back(m_DpBullet[i]);
			}
			
		}*/
		//SCENEMGR->Get_Instance()->Get_Scene(SC_FORTRESS)
		/*D3DXVECTOR3 vTemp2 = m_tInfo.vDir - vTemp;
		D3DXVECTOR3 vTemp3 = m_tInfo.vDir + vTemp;*/
		//m_BulletID = BULLET_DP;
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

	

	Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);

}

void CJunBullet::Release(void)
{

}

void CJunBullet::Move(void)
{
	/*	m_tInfo.vPos.x += iBulletDir * (m_fSpeed * cosf(m_fAngle) * m_fTempTime);
		m_tInfo.vPos.y -= (m_fSpeed * sinf(m_fAngle) * m_fTempTime) - (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
	*/
	switch (m_BulletID)
	{
	case BULLET_BASIC:
		m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;
		m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
		break;
	case BULLET_DP:
		m_tInfo.vPos += m_fSpeed* m_tInfo.vDir;
		m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
		break;
	case BULLET_END:
		break;
	}	
}
