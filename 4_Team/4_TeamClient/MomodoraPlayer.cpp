#include "stdafx.h"
#include "MomodoraPlayer.h"
#include "MomoDoraMgr.h"
#include "KeyMgr.h"
#include "MomoSword.h"
#include "MomoAbstractFactory.h"


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
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	//m_vLookX = { 1.f, 0.f, 0.f };

	/*m_vOriginalPoint[0] = { -50.f, -50.f, 0.f };
	m_vOriginalPoint[1] = { 50.f, -50.f, 0.f };
	m_vOriginalPoint[2] = { 50.f, 50.f, 0.f };
	m_vOriginalPoint[3] = { -50.f, 50.f, 0.f };*/

	m_fSpeed = 4.f;
}

const int CMomodoraPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	/* //Key_Input으로 상하좌우로 움직이는 코드

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginalPoint[i], &m_tInfo.matWorld);
	} */

	Key_Input();

	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
	m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);

	return OBJ_NOEVENT;
}

void CMomodoraPlayer::Late_Update(void)
{
}

void CMomodoraPlayer::Render(HDC _hDC)
{
	/*MoveToEx(_hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(_hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 0)
			continue;

	}

	LineTo(_hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);*/

	Ellipse(_hDC,
		int(m_tInfo.vPos.x - 30.f),
		int(m_tInfo.vPos.y - 30.f),
		int(m_tInfo.vPos.x + 30.f),
		int(m_tInfo.vPos.y + 30.f));

}

void CMomodoraPlayer::Release(void)
{
}

void CMomodoraPlayer::Key_Input(void)
{
	/*if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('A'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_vLookX, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('D'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_vLookX, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}*/

	if (GetAsyncKeyState(0x31))
	{
		//CMomoDoraMgr::Get_Instance()->Weapon_Change(MOMOWEAPON_GUN);

	}

	else if (KEYMGR->Key_Down('D'))
	{
		//CMomoDoraMgr::Get_Instance()->Weapon_Change(MOMOWEAPON_SWORD);
		m_pMomoSword->push_back(Create_Sword());
	}

}

CObj * CMomodoraPlayer::Create_Sword(void)
{
	CObj*	pMomoSword = new CMomoSword;
	pMomoSword->Initialize();
	pMomoSword->Set_Target(this);

	return pMomoSword;
	
}
