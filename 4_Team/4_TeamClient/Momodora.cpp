#include "stdafx.h"
#include "Momodora.h"
#include "MomoDoraMgr.h"
#include "RenderMgr.h"


CMomodora::CMomodora()
	: m_pPlayer(nullptr)
{
}


CMomodora::~CMomodora()
{
	Release();
}

void CMomodora::Initialize(void)
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CMomodoraPlayer;	
	}
}

void CMomodora::Update(void)
{
	m_pPlayer->Update();
}

void CMomodora::Late_Update(void)
{
	m_pPlayer->Late_Update();
	RENDERMGR->Add_Render_Obj(m_pPlayer);
}

void CMomodora::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);
}

void CMomodora::Release(void)
{
	Safe_Delete<CMomodoraPlayer*>(m_pPlayer);
}

void CMomodora::Key_Input(void)
{
}
