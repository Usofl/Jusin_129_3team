#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_eRender(RENDER_BACKGROUND)
	, m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

	// 항등행렬로 행렬을 초기화 하는 함수
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	// 크기 변환 행렬 생성 함수
	D3DXMatrixScaling(&m_tMatInfo.matScale, 1.f, 1.f, 1.f);

	D3DXMatrixIdentity(&m_tMatInfo.matRotZ);
	D3DXMatrixIdentity(&m_tMatInfo.matTrans);
}

CObj::~CObj()
{
}

void CObj::Update_Matrix(void)
{
	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;
}

