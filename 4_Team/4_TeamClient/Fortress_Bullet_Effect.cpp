#include "stdafx.h"
#include "Fortress_Bullet_Effect.h"


CFortress_Bullet_Effect::CFortress_Bullet_Effect()
	: m_bDead(false)
	, m_iSize(0)
	, m_fAngle(0.f)
	, m_fPower(0.f)
	, m_fTime(0.f)
	, m_fGravity(0.f)
{
	Initialize();
}

CFortress_Bullet_Effect::CFortress_Bullet_Effect(const float & _fX, const float & _fY)
	: m_bDead(false)
	, m_iSize(Random_Num(5, 20))
	, m_fAngle(D3DXToRadian((float)Random_Num(-60, 60)))
	, m_fPower((float)Random_Num(15, 20))
	, m_fTime(0.f)
	, m_fGravity((float)Random_Num(4, 8))
{
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
	Ellipse(hDC, m_tInfo.vPos.x - m_iSize, m_tInfo.vPos.y - m_iSize, m_tInfo.vPos.x + m_iSize, m_tInfo.vPos.y + m_iSize);
}

void CFortress_Bullet_Effect::Release(void)
{
}
