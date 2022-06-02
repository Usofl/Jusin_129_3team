#include "stdafx.h"
#include "MomoBullet.h"


CMomoBullet::CMomoBullet()
{
}


CMomoBullet::~CMomoBullet()
{
	Release();
}

void CMomoBullet::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_fSpeed = 10.f;

}

const int CMomoBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CMomoBullet::Late_Update(void)
{
}

void CMomoBullet::Render(HDC hDC)
{
}

void CMomoBullet::Release(void)
{
}
