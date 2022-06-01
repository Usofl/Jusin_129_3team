#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_eRender(RENDER_BACKGROUND)
	, m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

	// �׵���ķ� ����� �ʱ�ȭ �ϴ� �Լ�
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	// ũ�� ��ȯ ��� ���� �Լ�
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

