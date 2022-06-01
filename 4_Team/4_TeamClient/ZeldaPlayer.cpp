#include "stdafx.h"
#include "ZeldaPlayer.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CZeldaPlayer::CZeldaPlayer()
{
	Initialize();
}


CZeldaPlayer::~CZeldaPlayer()
{
}

void CZeldaPlayer::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vRectPoint[0] = { -50.f, -50.f, 0.f };
	m_vRectPoint[1] = { 50.f, -50.f, 0.f };
	m_vRectPoint[2] = { 50.f, 50.f, 0.f };
	m_vRectPoint[3] = { -50.f, 50.f, 0.f };

	m_fAngle = 90.f;

	for (int i = 0; i < 4; ++i)
	{
		m_vDrawPoint[i] = m_vRectPoint[i] + m_tInfo.vPos;
	}

	m_fSpeed = 3.f;
}

const int CZeldaPlayer::Update(void)
{
	// 연산을 진행
	Key_Input();

	//m_tInfo.vPos += m_tInfo.vDir;

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	
	Update_Matrix();

	for (int i = 0; i < 4; ++i)
	{
		m_vDrawPoint[i].x = (m_vRectPoint[i].x * m_tInfo.matWorld._11) - (m_vRectPoint[i].y * -m_tInfo.matWorld._12);
		m_vDrawPoint[i].y = (m_vRectPoint[i].x * m_tInfo.matWorld._21) + (m_vRectPoint[i].y * m_tInfo.matWorld._22);

		m_vDrawPoint[i] += m_tInfo.vPos;

		//m_vDrawPoint[i].x = (m_vRectPoint[i].x * cosf(m_fRadian)) - (m_vRectPoint[i].y * -sinf(m_fRadian)) + m_tInfo.vPos.x;
		//m_vDrawPoint[i].y = (m_vRectPoint[i].x * -sinf(m_fRadian)) + (m_vRectPoint[i].y * cosf(m_fRadian)) + m_tInfo.vPos.y;
	}
	return 0;
}

void CZeldaPlayer::Late_Update(void)
{
}

void CZeldaPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vDrawPoint[0].x, (int)m_vDrawPoint[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vDrawPoint[i].x, (int)m_vDrawPoint[i].y);
	}
	LineTo(hDC, (int)m_vDrawPoint[0].x, (int)m_vDrawPoint[0].y);
}

void CZeldaPlayer::Release(void)
{
}

void CZeldaPlayer::Key_Input(void)
{
	//GetKeyState
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		//m_tInfo.vPos.x -= m_fSpeed;
		m_fAngle += D3DXToRadian(3.f);
	}


	if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		//	m_tInfo.vPos.x += m_fSpeed;
		m_fAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle);
		m_tInfo.vPos.y -= m_fSpeed * sinf(m_fAngle);
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos.x -= m_fSpeed * cosf(m_fAngle);
		m_tInfo.vPos.y += m_fSpeed * sinf(m_fAngle);
	}
}
