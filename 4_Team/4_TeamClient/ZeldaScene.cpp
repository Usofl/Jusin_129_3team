#include "stdafx.h"
#include "ZeldaScene.h"
#include "RenderMgr.h"


CZeldaScene::CZeldaScene()
	: m_pPlayer(nullptr)
{
	Initialize();
}


CZeldaScene::~CZeldaScene()
{
	Release();
}

void CZeldaScene::Initialize(void)
{
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CZeldaPlayer;
	}
	
}

void CZeldaScene::Update(void)
{
	m_pPlayer->Update();
}

void CZeldaScene::Late_Update(void)
{
	m_pPlayer->Late_Update();
	RENDERMGR->Add_Render_Obj(m_pPlayer);
}

void CZeldaScene::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);
}

void CZeldaScene::Release(void)
{
	Safe_Delete<CZeldaPlayer*>(m_pPlayer);
}

void CZeldaScene::Key_Input(void)
{

}
