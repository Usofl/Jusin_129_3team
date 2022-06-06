#include "stdafx.h"
#include "Momo_HpBar.h"


CMomo_HpBar::CMomo_HpBar()
	: m_fXSize(150.f)
	, m_fYSize(20.f)
{
	m_tInfo.vPos = { 175.f, WINCY - 55.f, 0.f };
	Initialize();
}

CMomo_HpBar::CMomo_HpBar(const float & _fX, const float & _fY, const float & _fCX, const float & _fCY)
	: m_fXSize(_fCX)
	, m_fYSize(_fCY)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
	Initialize();
}

CMomo_HpBar::~CMomo_HpBar()
{
}

void CMomo_HpBar::Initialize(void)
{
	m_eRender = RENDER_UI;

	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_vOriginalPoint[POINT_LEFT_TOP] = { -m_fXSize, -m_fYSize, 0.f };
	m_vOriginalPoint[POINT_LEFT_BOTTOM] = { -m_fXSize, m_fYSize, 0.f };
	m_vOriginalPoint[POINT_RIGHT_BOTTOM] = { m_fXSize, m_fYSize, 0.f };
	m_vOriginalPoint[POINT_RIGHT_TOP] = { m_fXSize, -m_fYSize, 0.f };

	m_vLest_OriginalPoint = { 0.f, m_fYSize , 0.f };

	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = POINT_LEFT_TOP; i < POINT_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vHP_Point[i], &m_vOriginalPoint[i], &m_tInfo.matWorld);
	}
}

const int CMomo_HpBar::Update(void)
{
	m_tInfo.vPos = { 25.f + (300.f * m_fLest_HP), WINCY - 55.f, 0.f };

	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	D3DXVec3TransformCoord(&m_vLest_HP_Point, &m_vLest_OriginalPoint, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CMomo_HpBar::Late_Update(void)
{
}

void CMomo_HpBar::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vHP_Point[POINT_LEFT_TOP].x, (int)m_vHP_Point[POINT_LEFT_TOP].y, nullptr);
	for (int i = POINT_RIGHT_TOP; i < POINT_END; ++i)
	{
		LineTo(hDC, (int)m_vHP_Point[i].x, (int)m_vHP_Point[i].y);
	}
	LineTo(hDC, (int)m_vHP_Point[POINT_LEFT_TOP].x, (int)m_vHP_Point[POINT_LEFT_TOP].y);

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

	Rectangle(hDC, (int)m_vHP_Point[POINT_LEFT_TOP].x, (int)m_vHP_Point[POINT_LEFT_TOP].y, (int)m_vLest_HP_Point.x, (int)m_vLest_HP_Point.y);

	SelectObject(hDC, OldBrush);
	DeleteObject(MyBrush);
}

void CMomo_HpBar::Release(void)
{
}
