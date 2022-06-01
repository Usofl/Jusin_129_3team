#include "stdafx.h"
#include "ZeldaPlayer.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CZeldaPlayer::CZeldaPlayer()
	: m_fSize(30.f)
	, m_iHandSize(10)
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

	m_vPoint[ZELDA_LEFT_TOP] = { -m_fSize, -m_fSize, 0.f };
	m_vPoint[ZELDA_RIGHT_TOP] = { m_fSize, -m_fSize, 0.f };
	m_vPoint[ZELDA_RIGHT_BOTTOM] = { m_fSize, m_fSize, 0.f };
	m_vPoint[ZELDA_LEFT_BOTTOM] = { -m_fSize, m_fSize, 0.f };

	m_vPoint[ZELDA_LEFT_HAND] = { -m_fSize * 1.5f, m_fSize * 0.5f, 0.f };
	m_vPoint[ZELDA_RIGHT_HAND] = { m_fSize * 1.5f, m_fSize * 0.5f, 0.f };

	m_fAngle = D3DXToRadian(0.f);

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
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	
	Update_Matrix();

	for (int i = ZELDA_LEFT_TOP; i < ZELDA_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CZeldaPlayer::Late_Update(void)
{
}

void CZeldaPlayer::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_hDC, (int)m_vDrawPoint[ZELDA_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[ZELDA_LEFT_TOP].y + iScrollY, nullptr);
	
	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	OldPen = (HPEN)::SelectObject(_hDC, (HGDIOBJ)MyPen);
	
	LineTo(_hDC, (int)m_vDrawPoint[ZELDA_RIGHT_TOP].x + iScrollX, (int)m_vDrawPoint[ZELDA_RIGHT_TOP].y + iScrollY);

	SelectObject(_hDC, OldPen);
	DeleteObject(MyPen);

	for (int i = ZELDA_RIGHT_BOTTOM; i < 4; ++i)
	{
		LineTo(_hDC, (int)m_vDrawPoint[i].x + iScrollX, (int)m_vDrawPoint[i].y + iScrollY);
	}
	LineTo(_hDC, (int)m_vDrawPoint[ZELDA_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[ZELDA_LEFT_TOP].y + iScrollY);

	Ellipse(_hDC, (int)m_vDrawPoint[ZELDA_LEFT_HAND].x - m_iHandSize + iScrollX, (int)m_vDrawPoint[ZELDA_LEFT_HAND].y - m_iHandSize + iScrollY
		, (int)m_vDrawPoint[ZELDA_LEFT_HAND].x + m_iHandSize + iScrollX, (int)m_vDrawPoint[ZELDA_LEFT_HAND].y + m_iHandSize + iScrollY);

	Ellipse(_hDC, (int)m_vDrawPoint[ZELDA_RIGHT_HAND].x - m_iHandSize + iScrollX, (int)m_vDrawPoint[ZELDA_RIGHT_HAND].y - m_iHandSize + iScrollY
		, (int)m_vDrawPoint[ZELDA_RIGHT_HAND].x + m_iHandSize + iScrollX, (int)m_vDrawPoint[ZELDA_RIGHT_HAND].y + m_iHandSize + iScrollY);
}

void CZeldaPlayer::Release(void)
{
}

void CZeldaPlayer::Key_Input(void)
{
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		if (!KEYMGR->Key_Pressing(VK_DOWN) && !KEYMGR->Key_Pressing(VK_UP))
		{
			m_fAngle = D3DXToRadian(270.f);
		}
		else if (KEYMGR->Key_Pressing(VK_DOWN))
		{
			m_fAngle = D3DXToRadian(225.f);
		}
		else if (KEYMGR->Key_Pressing(VK_UP))
		{
			m_fAngle = D3DXToRadian(315.f);
		}
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		if (!KEYMGR->Key_Pressing(VK_DOWN) && !KEYMGR->Key_Pressing(VK_UP))
		{
			m_fAngle = D3DXToRadian(90.f);
		}
		else if (KEYMGR->Key_Pressing(VK_DOWN))
		{
			m_fAngle = D3DXToRadian(135.f);
		}
		else if (KEYMGR->Key_Pressing(VK_UP))
		{
			m_fAngle = D3DXToRadian(45.f);
		}

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else if (KEYMGR->Key_Pressing(VK_UP))
	{
		m_fAngle = D3DXToRadian(0.f);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fAngle = D3DXToRadian(180.f);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
}
