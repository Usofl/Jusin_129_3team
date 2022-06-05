#include "stdafx.h"
#include "MomoSword.h"


CMomoSword::CMomoSword()
{
}


CMomoSword::~CMomoSword()
{
	Release();
}

void CMomoSword::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;

	m_vLocalSwordPoint[0] = { -120.f, 0.f, 0.f };
	m_vLocalSwordPoint[1] = { -80.f, 0.f, 0.f };
	m_vLocalSwordPoint[2] = { 80.f, 0.f, 0.f };
	m_vLocalSwordPoint[3] = { 120.f, 0.f, 0.f };
}

const int CMomoSword::Update(void)
{
	//플레이어 좌표 받아오기
	m_fAngle += m_fSpeed;

	m_tInfo.vPos.x = m_pTarget->Get_Info().vPos.x + m_fDistance * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.vPos.y = m_pTarget->Get_Info().vPos.y - m_fDistance * sinf((m_fAngle * PI) / 180.f);

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0);

	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vSwordPoint[i], &m_vLocalSwordPoint[i], &m_tInfo.matWorld);
	}

	return OBJ_NOEVENT;
}

void CMomoSword::Late_Update(void)
{
}

void CMomoSword::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vSwordPoint[0].x, (int)m_vSwordPoint[0].y, nullptr);
	LineTo(hDC, (int)m_vSwordPoint[1].x, (int)m_vSwordPoint[1].y);
	MoveToEx(hDC, (int)m_vSwordPoint[2].x, (int)m_vSwordPoint[2].y, nullptr);
	LineTo(hDC, (int)m_vSwordPoint[3].x, (int)m_vSwordPoint[3].y);
}

void CMomoSword::Release(void)
{
}
