#include "stdafx.h"
#include "Fortress_HPBar.h"
#include "JunPlayer.h"


CFortress_HPBar::CFortress_HPBar()
	: m_fXSize(150.f)
	, m_fYSize(20.f)
{
	m_tInfo.vPos = { 175.f, WINCY - 55.f, 0.f };
	Initialize();
}

CFortress_HPBar::CFortress_HPBar(const float & _fX, const float & _fY, const float & _fCX, const float & _fCY)
	: m_fXSize(_fCX)
	, m_fYSize(_fCY)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
	Initialize();
}


CFortress_HPBar::~CFortress_HPBar()
{
	Release();
}

void CFortress_HPBar::Initialize(void)
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

const int CFortress_HPBar::Update(void)
{
	m_tInfo.vPos = { 25.f + (300.f * m_fLest_HP), WINCY - 55.f, 0.f };

	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	D3DXVec3TransformCoord(&m_vLest_HP_Point, &m_vLest_OriginalPoint, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CFortress_HPBar::Late_Update(void)
{
	// 변수 하나를 플레이어 iHp / iMaxHp 만들고 Render 할 때 이만큼 출력 하고 싶음..

	//m_pTarget = Get_Instance()->Get_Player();

	//if (m_pTarget)
	//{
	//	float a = dynamic_cast<CJunPlayer*>(m_pTarget)->Get_Hp();
	//	float b = dynamic_cast<CJunPlayer*>(m_pTarget)->Get_MaxHp();

	//	m_fGague = m_fXSize * (a / b);
	//	//이 게이지를... 출력할때 POINT_RIGHT 의 x좌표로 넣고 싶은데요.. 계속 업데이트 되어야 하닉가..
	//}
}

void CFortress_HPBar::Render(HDC hDC)
{
	//MaxHpBar
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

	//HpBar

	// maxhp바 하나 만들고 그 위에 hp바 생성해서 POINT_RIGHT 좌표만 바꾸도록 생성
}

void CFortress_HPBar::Release(void)
{
}