#include "stdafx.h"
#include "MomodoraPlayer.h"
#include "MomoDoraMgr.h"
#include "KeyMgr.h"
#include "MomoSword.h"
#include "ScrollMgr.h"


CMomodoraPlayer::CMomodoraPlayer()
{
	Initialize();
}


CMomodoraPlayer::~CMomodoraPlayer()
{
	Release();
}

void CMomodoraPlayer::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_vLookX = { 1.f, 0.f, 0.f };

	m_vOriginalPoint[0] = { -30.f, -30.f, 0.f };
	m_vOriginalPoint[1] = { 30.f, -30.f, 0.f };
	m_vOriginalPoint[2] = { 30.f, 30.f, 0.f };
	m_vOriginalPoint[3] = { -30.f, 30.f, 0.f };

	m_vOriginalHeadPoint[0] = { 0.f, -30.f, 0.f };

	//m_vOriginalHeadPoint[0] = { -5.f, -35.f, 0.f };
	//m_vOriginalHeadPoint[1] = { 5.f, -25.f, 0.f };

	m_fSpeed = 4.f;
	m_iHP = 50;
}

const int CMomodoraPlayer::Update(void)
{
	if (0 >= m_iHP)
	{
		return OBJ_DEAD;
	}

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	 //Key_Input으로 상하좌우로 움직이는 코드

	Key_Input();

	D3DXVECTOR3 Mouse_pos = ::Get_Mouse() + D3DXVECTOR3{(float)(-iScrollX), float(-iScrollY), 0.f};

	m_tInfo.vDir = Mouse_pos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_fAngle = acosf(m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y);

	if (m_tInfo.vPos.x > Mouse_pos.x)
	{
		m_fAngle = -m_fAngle;
	}

	D3DXMatrixScaling(&m_tMatInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginalPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformCoord(&m_vHeadPoint[0], &m_vOriginalHeadPoint[0], &m_tInfo.matWorld);

	//플레이어가 마우스 따라다니는 코드
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	////D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	//float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	//float	fAngle = acosf(fDot);

	//if (m_tInfo.vPos.y < Get_Mouse().y)
	//	fAngle = 2.f * D3DX_PI - fAngle;

	//m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
	//m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);

	//나는 이동하지 않고 고개만 돌리고싶다..
	//플레이어랑 마우스 좌표 사이의 각도를 구해서?
	return OBJ_NOEVENT;
}
  
void CMomodoraPlayer::Late_Update(void)
{
}

void CMomodoraPlayer::Render(HDC _hDC)
{
	MoveToEx(_hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(_hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 0)
			continue;
	}
	LineTo(_hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);

	Ellipse(_hDC, (int)m_vHeadPoint[0].x - 5, (int)m_vHeadPoint[0].y - 5, (int)m_vHeadPoint[0].x + 5, (int)m_vHeadPoint[0].y + 5);
}

void CMomodoraPlayer::Release(void)
{
}

void CMomodoraPlayer::Key_Input(void)
{

	if (GetAsyncKeyState('W'))
	{
		m_tInfo.vPos.y -= m_fSpeed;
	}

	if (GetAsyncKeyState('S'))
	{
		m_tInfo.vPos.y += m_fSpeed;
	}

	if (GetAsyncKeyState('A'))
	{
		m_tInfo.vPos.x -= m_fSpeed;
	}

	if (GetAsyncKeyState('D'))
	{
		m_tInfo.vPos.x += m_fSpeed;
	}
}