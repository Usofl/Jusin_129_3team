#include "stdafx.h"
#include "Fortress_Bullet_Effect.h"
#include "ScrollMgr.h"


CFortress_Bullet_Effect::CFortress_Bullet_Effect()
	: m_bDead(false)
	, m_iSize(0)
	, m_iRed(0)
	, m_fPower(0.f)
	, m_fTime(0.f)
	, m_fGravity(0.f)
{
	Initialize();
}

CFortress_Bullet_Effect::CFortress_Bullet_Effect(const float & _fX, const float & _fY)
	: m_bDead(false)
	, m_iSize(Random_Num(5, 20))
	, m_iRed(Random_Num(150, 200))
	, m_fPower((float)Random_Num(10, 15))
	, m_fTime(0.f)
	, m_fGravity((float)Random_Num(4, 8))
{
	m_fAngle = D3DXToRadian((float)Random_Num(-60, 60));
	m_tInfo.vPos = { _fX, _fY, 0.f };
	Initialize();
}

CFortress_Bullet_Effect::~CFortress_Bullet_Effect()
{
	Release();
}

void CFortress_Bullet_Effect::Initialize(void)
{
	m_eRender = RENDER_EFFECT;

	if (0 == Random_Num(0, 1))
	{
		m_tInfo.vLook = { -1.f, 0.f, 0.f };
	}
	else
	{
		m_tInfo.vLook = { 1.f, 0.f, 0.f };
	}

	m_vPoint = { 0.f , 0.f , 0.f };
}

const int CFortress_Bullet_Effect::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_fTime += 0.1f;
	m_tInfo.vPos.x += 2.f * sinf(m_fAngle) * m_tInfo.vLook.x;
	m_tInfo.vPos.y -= m_fPower * m_fTime * sinf(m_fAngle) - (0.5f * 3.8f * (m_fTime * m_fTime));

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	D3DXVec3TransformCoord(&m_vDrawPoint, &m_vPoint, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CFortress_Bullet_Effect::Late_Update(void)
{
	if (m_tInfo.vPos.y >= WINCY)
	{
		m_bDead = true;
	}
}

void CFortress_Bullet_Effect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HBRUSH MyBrush, OldBrush;
	//MyBrush = (HBRUSH)CreateSolidBrush(RGB(m_iRed, 30, 30));
	//OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

	//Ellipse(hDC, (int)m_tInfo.vPos.x - m_iSize + iScrollX, (int)m_tInfo.vPos.y - m_iSize + iScrollY,
	//	(int)m_tInfo.vPos.x + m_iSize + iScrollX, (int)m_tInfo.vPos.y + m_iSize + iScrollY);

	//SelectObject(hDC, OldBrush);
	//DeleteObject(MyBrush);

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(m_iRed, 0, 0));
	OldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)MyPen);
	
	Ellipse(hDC, (int)m_tInfo.vPos.x - m_iSize + iScrollX, (int)m_tInfo.vPos.y - m_iSize + iScrollY,
		(int)m_tInfo.vPos.x + m_iSize + iScrollX, (int)m_tInfo.vPos.y + m_iSize + iScrollY);

	SelectObject(hDC, OldPen);
	DeleteObject(MyPen);
}

void CFortress_Bullet_Effect::Release(void)
{
}
