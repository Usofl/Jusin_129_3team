#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

	// �׵���ķ� ����� �ʱ�ȭ �ϴ� �Լ�
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

