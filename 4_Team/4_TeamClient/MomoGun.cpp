#include "stdafx.h"
#include "MomoGun.h"
#include "MomoDoraMgr.h"


CMomoGun::CMomoGun()
{
}


CMomoGun::~CMomoGun()
{
	Release();
}

void CMomoGun::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.vPos = { /*m_pMomoPlayer->Get_Info().vPos.x +*/ 50.f, /*m_pMomoPlayer->Get_Info().vPos.y*/0.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_vOriginalGunPoint[0] = { -10.f, -10.f, 0.f };
	m_vOriginalGunPoint[1] = { +10.f, -10.f, 0.f };
	m_vOriginalGunPoint[2] = { +10.f, +10.f, 0.f };
	m_vOriginalGunPoint[3] = { -10.f, +10.f, 0.f };
}

const int CMomoGun::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	Update_Matrix();

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vGunPoint[i], &m_vOriginalGunPoint[i], &m_tInfo.matWorld);
	}
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CMomoGun::Late_Update(void)
{
}

void CMomoGun::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vGunPoint[i].x, (int)m_vGunPoint[i].y);

		if (i > 0)
			continue;

	}

	LineTo(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y);
}

void CMomoGun::Release(void)
{
}
