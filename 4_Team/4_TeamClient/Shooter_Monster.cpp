#include "stdafx.h"
#include "Shooter_Monster.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Momodora.h"

CShooter_Monster::CShooter_Monster() 
	: m_fXSize(20.f)
	, m_fYSize(20.f)
	, m_fRevolutionAngle(0.f)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	switch (Random_Num(1, 4))
	{
	case 1:
		m_tInfo.vPos = { (float)(0 - iScrollX),(float)(Random_Num(0, WINCY) - iScrollY), 0.f };
		break;
	case 2:
		m_tInfo.vPos = { (float)(Random_Num(0, WINCX) - iScrollX), (float)(0.f - iScrollY), 0.f };
		break;
	case 3:
		m_tInfo.vPos = { (float)(Random_Num(0, WINCX) - iScrollX), (float)(WINCY - iScrollY), 0.f };
		break;
	case 4:
		m_tInfo.vPos = { (float)(WINCX - iScrollX),  (float)(Random_Num(0, WINCY) - iScrollY), 0.f };
		break;
	}
	Initialize();
}

CShooter_Monster::CShooter_Monster(const float & _fX, const float & _fY)
	: m_fXSize(20.f)
	, m_fYSize(20.f)
	, m_fRevolutionAngle(0.f)
{
	m_tInfo.vPos = { _fX, _fY, 0.f };
	Initialize();
}


CShooter_Monster::~CShooter_Monster()
{
	Release();
}

void CShooter_Monster::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	m_MonsterID = MOMO_ROTATION;
	m_iHP = 20;

	m_fSpeed = 3.f;

	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[POINT_LEFT_TOP] = { -m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_TOP] = { m_fXSize, -m_fYSize, 0.f };
	m_vPoint[POINT_RIGHT_BOTTOM] = { m_fXSize, m_fYSize, 0.f };
	m_vPoint[POINT_LEFT_BOTTOM] = { -m_fXSize, m_fYSize, 0.f };

	m_vHeadPoint[0] = { -m_fXSize * 0.3f, -m_fYSize * 0.7f, 0.f };
	m_vHeadPoint[1] = { m_fXSize * 0.3f,  -m_fYSize * 0.7f, 0.f };

	m_fAngle = D3DXToRadian(0.f);
}

const int CShooter_Monster::Update(void)
{
	if (0 >= m_iHP)
	{
		return OBJ_DEAD;
	}

	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

	D3DXVECTOR3 vPlayer_pos = static_cast<CMomodora*>(SCENEMGR->Get_Scene(SC_MOMO))->Get_Player()->Get_Info().vPos;

	m_tInfo.vDir = vPlayer_pos - m_tInfo.vPos;

	float fDigonal = sqrtf((m_tInfo.vDir.x * m_tInfo.vDir.x) + (m_tInfo.vDir.y * m_tInfo.vDir.y));

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_fAngle = acosf(m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y);

	if (m_tInfo.vPos.x > vPlayer_pos.x)
	{
		m_fAngle = -m_fAngle;
	}

	if (fDigonal >= 300.f)
	{
		D3DXMatrixIdentity(&m_tMatInfo.matParents);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_fRevolutionAngle += D3DXToRadian(1.5f);
		// 이동 행렬 생성 함수
		// z축 회전 행렬 생성 함수
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

		//D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	}
	else if (fDigonal <= 280.f)
	{
		D3DXMatrixIdentity(&m_tMatInfo.matParents);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		m_fRevolutionAngle += D3DXToRadian(1.5f);
		// 이동 행렬 생성 함수
		// z축 회전 행렬 생성 함수
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

		//D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	}
	else 
	{

		m_fRevolutionAngle += D3DXToRadian(1.5f);
		// 이동 행렬 생성 함수
	}
	D3DXVECTOR3 vTarget = m_tInfo.vPos - vPlayer_pos;

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRevolutionZ, m_fRevolutionAngle);
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, vTarget.x, vTarget.y, 0.f);
	D3DXMatrixTranslation(&m_tMatInfo.matParents, vPlayer_pos.x, vPlayer_pos.y, 0.f);

	Update_Matrix();

	for (int i = POINT_LEFT_TOP; i < POINT_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformCoord(&m_vHeadDrawPoint[0], &m_vHeadPoint[0], &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_vHeadDrawPoint[1], &m_vHeadPoint[1], &m_tInfo.matWorld);


	return OBJ_NOEVENT;
}

void CShooter_Monster::Late_Update(void)
{

}

void CShooter_Monster::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY, nullptr);

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
	OldPen = (HPEN)::SelectObject(_hDC, (HGDIOBJ)MyPen);

	for (int i = POINT_RIGHT_TOP; i < POINT_END; ++i)
	{
		LineTo(_hDC, (int)m_vDrawPoint[i].x + iScrollX, (int)m_vDrawPoint[i].y + iScrollY);
	}
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_TOP].x + iScrollX, (int)m_vDrawPoint[POINT_LEFT_TOP].y + iScrollY);

	SelectObject(_hDC, OldPen);
	DeleteObject(MyPen);

	Ellipse(_hDC, (int)m_vHeadDrawPoint[0].x - 5 + iScrollX, (int)m_vHeadDrawPoint[0].y - 5 + iScrollY
		, (int)m_vHeadDrawPoint[0].x + 5 + iScrollX, (int)m_vHeadDrawPoint[0].y + 5 + iScrollY);

	Ellipse(_hDC, (int)m_vHeadDrawPoint[1].x - 5 + iScrollX, (int)m_vHeadDrawPoint[1].y - 5 + iScrollY
		, (int)m_vHeadDrawPoint[1].x + 5 + iScrollX, (int)m_vHeadDrawPoint[1].y + 5 + iScrollY);
}

void CShooter_Monster::Release(void)
{
}
