#include "stdafx.h"
#include "Zelda_Button.h"
#include "ScrollMgr.h"


CZelda_Button::CZelda_Button()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
}

CZelda_Button::CZelda_Button(const float & _fX, const float & _fY)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
}


CZelda_Button::~CZelda_Button()
{
}

void CZelda_Button::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_fSize = 50.f;

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { -m_fSize, -m_fSize, 0.f };
	m_vPoint[1] = { m_fSize, -m_fSize, 0.f };
	m_vPoint[2] = { m_fSize, m_fSize, 0.f };
	m_vPoint[3] = { -m_fSize, m_fSize, 0.f };

	m_fAngle = D3DXToRadian(0.f);
}

const int CZelda_Button::Update(void)
{
	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = POINT_LEFT_TOP; i < POINT_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	return OBJ_NOEVENT;
}

void CZelda_Button::Late_Update(void)
{
}

void CZelda_Button::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY, nullptr);

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	OldPen = (HPEN)::SelectObject(_hDC, (HGDIOBJ)MyPen);

	for (int i = POINT_RIGHT_TOP; i < POINT_END; ++i)
	{
		LineTo(_hDC, (int)m_vDrawPoint[i].x + iScrollX, (int)m_vDrawPoint[i].y + iScrollY);
	}
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY);

	SelectObject(_hDC, OldPen);
	DeleteObject(MyPen);
}

void CZelda_Button::Release(void)
{
}
