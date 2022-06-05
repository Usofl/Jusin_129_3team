#include "stdafx.h"
#include "Fortress_Boom_Effect.h"
#include "ScrollMgr.h"

CFortress_Boom_Effect::CFortress_Boom_Effect()
	: m_bDead(false)
	, m_fMagnify(0.f)
	, m_iRed(0)
{
	Initialize();
}

CFortress_Boom_Effect::CFortress_Boom_Effect(const float & _fX, const float & _fY)
	: m_bDead(false)
	, m_fMagnify(0.f)
	, m_iRed(Random_Num(120, 255))
{
	m_tInfo.vPos = { _fX, _fY, 0.f };

	Initialize();
}

CFortress_Boom_Effect::~CFortress_Boom_Effect()
{
	Release();
}

void CFortress_Boom_Effect::Initialize(void)
{
	m_eRender = RENDER_EFFECT;

	int num = Random_Num(4, 6);
	m_vecPoint.reserve(num);
	m_vecDrawPoint.reserve(num);
	m_vecSize.reserve(num);

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for(int i = 0; i < num; ++i)
	{
		m_vecPoint.push_back(D3DXVECTOR3({ (float)Random_Num(-5, 5),  (float)Random_Num(-5, 5), 0.f }));
		m_vecDrawPoint.push_back(D3DXVECTOR3({ 0.f, 0.f, 0.f }));

		D3DXVec3TransformCoord(&m_vecDrawPoint[i], &m_vecPoint[i], &m_tInfo.matWorld);

		m_vecSize.push_back((float)Random_Num(30, 50));
	}
}

const int CFortress_Boom_Effect::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_fMagnify += 0.05f;

	return 0;
}

void CFortress_Boom_Effect::Late_Update(void)
{
	if (m_fMagnify >= 1.f)
	{
		m_bDead = true;
	}
}

void CFortress_Boom_Effect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(240, 30, 30));
	OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

	for (unsigned int i = 0; i < m_vecDrawPoint.size(); ++i)
	{
		Ellipse(hDC, (int)(m_vecDrawPoint[i].x - m_vecSize[i] * m_fMagnify) + iScrollX, (int)(m_vecDrawPoint[i].y - m_vecSize[i] * m_fMagnify) + iScrollY,
			(int)(m_vecDrawPoint[i].x + m_vecSize[i] * m_fMagnify) + iScrollX, (int)(m_vecDrawPoint[i].y + m_vecSize[i] * m_fMagnify) + iScrollY);
	}

	SelectObject(hDC, OldBrush);
	DeleteObject(MyBrush);
}

void CFortress_Boom_Effect::Release(void)
{
}
