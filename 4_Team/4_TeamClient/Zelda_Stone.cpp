#include "stdafx.h"
#include "Zelda_Stone.h"
#include "ScrollMgr.h"


CZelda_Stone::CZelda_Stone()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fXSize = 50.f;
	m_fYSize = 50.f;
}

CZelda_Stone::CZelda_Stone(const float & _fX, const float & _fY, const float & _fCX, const float & _fCY)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
	m_fXSize = _fCX;
	m_fYSize = _fCY;
}

CZelda_Stone::~CZelda_Stone()
{
}

void CZelda_Stone::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[POINT_LEFT_TOP] = { -m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_TOP] = { m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_BOTTOM] = { m_fXSize, m_fYSize, 0.f };
	m_vPoint[POINT_LEFT_BOTTOM] = { -m_fXSize, m_fYSize, 0.f };

	m_fAngle = D3DXToRadian(0.f);
}

const int CZelda_Stone::Update(void)
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

void CZelda_Stone::Late_Update(void)
{
}

void CZelda_Stone::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY, nullptr);

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
	OldPen = (HPEN)::SelectObject(_hDC, (HGDIOBJ)MyPen);

	for (int i = POINT_RIGHT_TOP; i < POINT_END; ++i)
	{
		LineTo(_hDC, (int)m_vDrawPoint[i].x + iScrollX, (int)m_vDrawPoint[i].y + iScrollY);
	}
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY);

	SelectObject(_hDC, OldPen);
	DeleteObject(MyPen);
}

void CZelda_Stone::Release(void)
{
}
