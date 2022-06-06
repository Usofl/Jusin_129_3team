#include "stdafx.h"
#include "MomoBullet.h"
#include "SceneMgr.h"
#include "Momodora.h"
#include "MomodoraPlayer.h"


CMomoBullet::CMomoBullet()
{
	Initialize();
}


CMomoBullet::~CMomoBullet()
{
	Release();
}

void CMomoBullet::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_fSpeed = 7.f;

	D3DXVECTOR3 vPlayer_pos = static_cast<CMomodora*>(SCENEMGR->Get_Scene(SC_MOMO))->Get_Player()->Get_Info().vPos;
	float fAngle = static_cast<CMomodora*>(SCENEMGR->Get_Scene(SC_MOMO))->Get_Player()->Get_Angle();

	m_tInfo.vPos = vPlayer_pos;
	m_fAngle = fAngle;
}

const int CMomoBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x += m_fSpeed * cosf((m_fAngle * D3DX_PI) / 180.f);
	m_tInfo.vPos.y -= m_fSpeed * sinf((m_fAngle * D3DX_PI) / 180.f);

	return OBJ_NOEVENT;
}

void CMomoBullet::Late_Update(void)
{
	if ( 0 > m_tInfo.vPos.x || WINCX < m_tInfo.vPos.x || 110 > m_tInfo.vPos.y || WINCY - 110 < m_tInfo.vPos.y)
	{
		m_bDead = true;
	}
}

void CMomoBullet::Render(HDC hDC)
{
	Ellipse(hDC, (int)m_tInfo.vPos.x - 10, (int)m_tInfo.vPos.y - 10, (int)m_tInfo.vPos.x + 10, (int)m_tInfo.vPos.y + 10);
}

void CMomoBullet::Release(void)
{
}
