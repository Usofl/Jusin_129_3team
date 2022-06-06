#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_eRender(RENDER_BACKGROUND)
	, m_fAngle(0.f)
	, m_fSpeed(0.f)
	, m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.vDir = NORMALVECTOR_X;

	// 항등행렬로 행렬을 초기화 하는 함수
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	// 크기 변환 행렬 생성 함수
	D3DXMatrixScaling(&m_tMatInfo.matScale, 1.f, 1.f, 1.f);

	D3DXMatrixIdentity(&m_tMatInfo.matRotZ);
	D3DXMatrixIdentity(&m_tMatInfo.matTrans);
	D3DXMatrixIdentity(&m_tMatInfo.matRevolutionZ);
	D3DXMatrixIdentity(&m_tMatInfo.matParents);
}

CObj::~CObj()
{
}

void CObj::Update_Matrix(void)
{
	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans * m_tMatInfo.matRevolutionZ * m_tMatInfo.matParents;
}

