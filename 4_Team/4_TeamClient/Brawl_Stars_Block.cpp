#include "stdafx.h"
#include "Brawl_Stars_Block.h"


CBrawl_Stars_Block::CBrawl_Stars_Block()
{
}


CBrawl_Stars_Block::~CBrawl_Stars_Block()
{
	Release();
}

void CBrawl_Stars_Block::Initialize(void)
{
	m_tInfo_Block_Local[0].vPos = { -30.f , -30.f , 0.f };
	m_tInfo_Block_Local[1].vPos = { +30.f , -30.f , 0.f };
	m_tInfo_Block_Local[2].vPos = { +30.f , +30.f , 0.f };
	m_tInfo_Block_Local[3].vPos = { -30.f , +30.f , 0.f };

}

const int CBrawl_Stars_Block::Update(void)
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_tInfo_Block_World[i].vPos, &m_tInfo_Block_Local[i].vPos, &m_tInfo.matWorld);
	}

	return 0;
}

void CBrawl_Stars_Block::Late_Update(void)
{
}

void CBrawl_Stars_Block::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo_Block_World[0].vPos.x, (int)m_tInfo_Block_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Block_World[i].vPos.x, (int)m_tInfo_Block_World[i].vPos.y);
	}
	LineTo(hDC, (int)m_tInfo_Block_World[0].vPos.x, (int)m_tInfo_Block_World[0].vPos.y);
}

void CBrawl_Stars_Block::Release(void)
{
}
