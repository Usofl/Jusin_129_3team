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

	// �׵���ķ� ����� �ʱ�ȭ �ϴ� �Լ�
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	// ũ�� ��ȯ ��� ���� �Լ�
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

