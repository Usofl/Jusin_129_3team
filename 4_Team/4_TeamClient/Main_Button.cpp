#include "stdafx.h"
#include "Main_Button.h"
#include "ScrollMgr.h"

CMain_Button::CMain_Button()
	: m_fXSize(0.f)
	, m_fYSize(0.f)
	, m_iWidth(2)
	, m_iRed(0)
{
	Initialize();
}

CMain_Button::CMain_Button(const float & _fX, const float & _fY)
	: m_fXSize(100.f)
	, m_fYSize(30.f)
	, m_iWidth(2)
	, m_iRed(0)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };

	Initialize();
}


CMain_Button::~CMain_Button()
{
	Release();
}

void CMain_Button::Initialize(void)
{
	m_eRender = RENDER_UI;

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[POINT_LEFT_TOP] = { -m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_TOP] = { m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_BOTTOM] = { m_fXSize, m_fYSize, 0.f };
	m_vPoint[POINT_LEFT_BOTTOM] = { -m_fXSize, m_fYSize, 0.f };

	m_fAngle = D3DXToRadian(0.f);
}

const int CMain_Button::Update(void)
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

void CMain_Button::Late_Update(void)
{
}

void CMain_Button::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x, (int)m_vDrawPoint[POINT_LEFT_TOP].y, nullptr);

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, m_iWidth, RGB(m_iRed, 0, 0));
	OldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)MyPen);

	for (int i = POINT_RIGHT_TOP; i < POINT_END; ++i)
	{
		LineTo(hDC, (int)m_vDrawPoint[i].x, (int)m_vDrawPoint[i].y);
	}
	LineTo(hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x, (int)m_vDrawPoint[POINT_LEFT_TOP].y);

	SelectObject(hDC, OldPen);
	DeleteObject(MyPen);
}

void CMain_Button::Release(void)
{
}

void CMain_Button::Selected_Button(void)
{
	m_iWidth = 5;
	m_iRed = 255;
}
