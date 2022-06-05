#include "stdafx.h"
#include "Fortress_HPBar.h"
#include "JunPlayer.h"


CFortress_HPBar::CFortress_HPBar()
{
	m_tInfo.vPos = { 100.f, 658.f, 0.f };
	m_fXSize = 100.f;
	m_fYSize = 40.f;
}

CFortress_HPBar::CFortress_HPBar(const float & _fX, const float & _fY, const float & _fCX, const float & _fCY)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
	m_fXSize = _fCX;
	m_fYSize = _fCY;
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
}

const int CFortress_HPBar::Update(void)
{
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = POINT_LEFT_TOP; i < POINT_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vHPPoint[i], &m_vOriginalPoint[i], &m_tInfo.matWorld);
	}
	return OBJ_NOEVENT;
}

void CFortress_HPBar::Late_Update(void)
{
	// ���� �ϳ��� �÷��̾� iHp / iMaxHp ����� Render �� �� �̸�ŭ ��� �ϰ� ����..

	//m_pTarget = Get_Instance()->Get_Player();

	//if (m_pTarget)
	//{
	//	float a = dynamic_cast<CJunPlayer*>(m_pTarget)->Get_Hp();
	//	float b = dynamic_cast<CJunPlayer*>(m_pTarget)->Get_MaxHp();

	//	m_fGague = m_fXSize * (a / b);
	//	//�� ��������... ����Ҷ� POINT_RIGHT �� x��ǥ�� �ְ� ��������.. ��� ������Ʈ �Ǿ�� �ϴа�..
	//}


}

void CFortress_HPBar::Render(HDC hDC)
{
	//MaxHpBar
	MoveToEx(hDC, (int)m_vHPPoint[POINT_LEFT_TOP].x, (int)m_vHPPoint[POINT_LEFT_TOP].y, nullptr);
	for (int i = POINT_LEFT_BOTTOM; i < POINT_END; ++i)
	{
		LineTo(hDC, (int)m_vHPPoint[i].x, (int)m_vHPPoint[i].y);
	}
	LineTo(hDC, (int)m_vHPPoint[POINT_LEFT_TOP].x, (int)m_vHPPoint[POINT_LEFT_TOP].y);

	//HpBar

	// maxhp�� �ϳ� ����� �� ���� hp�� �����ؼ� POINT_RIGHT ��ǥ�� �ٲٵ��� ����
}

void CFortress_HPBar::Release(void)
{
}