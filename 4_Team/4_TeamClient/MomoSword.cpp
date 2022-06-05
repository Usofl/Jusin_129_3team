#include "stdafx.h"
#include "Momodora.h"
#include "MomoSword.h"
#include "ScrollMgr.h"
#include "MomodoraPlayer.h"
#include "SceneMgr.h"

CMomoSword::CMomoSword()
{
	Initialize();
}


CMomoSword::~CMomoSword()
{
	Release();
}

void CMomoSword::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;

	m_vLocalSwordPoint[0] = { -120.f, 0.f, 0.f };
	m_vLocalSwordPoint[1] = { -80.f, 0.f, 0.f };
	m_vLocalSwordPoint[2] = { 80.f, 0.f, 0.f };
	m_vLocalSwordPoint[3] = { 120.f, 0.f, 0.f };
}

const int CMomoSword::Update(void)
{
	//플레이어 좌표 받아오기
	m_fAngle += D3DXToRadian(m_fSpeed);


	D3DXVECTOR3 vPlayer_pos = static_cast<CMomodora*>(SCENEMGR->Get_Scene(SC_MOMO))->Get_Player()->Get_Info().vPos;
	
	m_tInfo.vPos = vPlayer_pos;

	//m_tInfo.vPos.x = vPlayer_pos.x + m_fDistance * cosf((m_fAngle * PI) / 180.f);
	//m_tInfo.vPos.y = vPlayer_pos.y - m_fDistance * sinf((m_fAngle * PI) / 180.f);

	//D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);

	D3DXMatrixScaling(&m_tMatInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vSwordPoint[i], &m_vLocalSwordPoint[i], &m_tInfo.matWorld);
	}

	return OBJ_NOEVENT;
}

void CMomoSword::Late_Update(void)
{
}

void CMomoSword::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	D3DXVECTOR3 vPlayer_pos = static_cast<CMomodora*>(SCENEMGR->Get_Scene(SC_MOMO))->Get_Player()->Get_Info().vPos;

	//Ellipse(hDC, (int)vPlayer_pos.x - 50, (int)vPlayer_pos.y - 50, (int)vPlayer_pos.x + 50, (int)vPlayer_pos.y + 50);
	
	MoveToEx(hDC, (int)m_vSwordPoint[0].x + iScrollX, (int)m_vSwordPoint[0].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vSwordPoint[1].x + iScrollX, (int)m_vSwordPoint[1].y + iScrollY);
	MoveToEx(hDC, (int)m_vSwordPoint[2].x + iScrollX, (int)m_vSwordPoint[2].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vSwordPoint[3].x + iScrollX, (int)m_vSwordPoint[3].y + iScrollY);

	Ellipse(hDC, (int)m_vSwordPoint[0].x - 50, (int)m_vSwordPoint[0].y - 50, (int)m_vSwordPoint[0].x + 50, (int)m_vSwordPoint[0].y + 50);
	Ellipse(hDC, (int)m_vSwordPoint[1].x - 50, (int)m_vSwordPoint[1].y - 50, (int)m_vSwordPoint[1].x + 50, (int)m_vSwordPoint[1].y + 50);
	Ellipse(hDC, (int)m_vSwordPoint[2].x - 50, (int)m_vSwordPoint[2].y - 50, (int)m_vSwordPoint[2].x + 50, (int)m_vSwordPoint[2].y + 50);
	Ellipse(hDC, (int)m_vSwordPoint[3].x - 50, (int)m_vSwordPoint[3].y - 50, (int)m_vSwordPoint[3].x + 50, (int)m_vSwordPoint[3].y + 50);

}

void CMomoSword::Release(void)
{
}
