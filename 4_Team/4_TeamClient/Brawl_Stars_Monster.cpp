#include "stdafx.h"
#include "Brawl_Stars_Monster.h"


CBrawl_Stars_Monster::CBrawl_Stars_Monster()
	:m_fAngle_Body(0.f)
{
}


CBrawl_Stars_Monster::~CBrawl_Stars_Monster()
{
}

void CBrawl_Stars_Monster::Initialize(void)
{
	m_tInfo.vPos = { 700.f , 500.f , 0.f };

	m_tInfo_Body_Local[0].vPos = { -40.f, -40.f, 0.f };
	m_tInfo_Body_Local[1].vPos = { +40.f, -40.f, 0.f };
	m_tInfo_Body_Local[2].vPos = { +40.f, +40.f, 0.f };
	m_tInfo_Body_Local[3].vPos = { -40.f, +40.f, 0.f };

}

const int CBrawl_Stars_Monster::Update(void)
{
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	
	m_tInfo.matWorld = m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		// �������� ��ġ���͸� ��ȯ ���ش� (���� ��ȯ�� ���� ��Ŀ� ����Ÿ�� �ٵ� ������ ������ ���ϱ⸦ ���Ŀ� �ٵ� ������ ������ ���� )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i].vPos, &m_tInfo_Body_Local[i].vPos, &m_tInfo.matWorld);
	}

	return 0;
}

void CBrawl_Stars_Monster::Late_Update(void)
{

}

void CBrawl_Stars_Monster::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo_Body_World[0].vPos.x, (int)m_tInfo_Body_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].vPos.x, (int)m_tInfo_Body_World[i].vPos.y);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[0].vPos.x, (int)m_tInfo_Body_World[0].vPos.y);
}

void CBrawl_Stars_Monster::Release(void)
{
}
