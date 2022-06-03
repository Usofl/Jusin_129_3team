#include "stdafx.h"
#include "SceneMgr.h"
#include "ZeldaScene.h"
#include "Brawl_Stars_Scene.h"
#include "Momodora.h"
#include "ZeldaEditScene.h"
#include "FlashmanScene.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene()
	, m_eCurScene(SC_END)
	, m_ePreScene(SC_END)
{
	m_pScene[SC_BRAWL_STARS] = new CBrawl_Stars_Scene;
	m_pScene[SC_MOMO] = new CMomodora;
	m_pScene[SC_FORTRESS] = nullptr;
	m_pScene[SC_FORTRESS] = new CFortress;
	m_pScene[SC_ZELDA] = new CZeldaScene;
	m_pScene[SC_ZELDA_EDIT] = new CZeldaEditScene;
	m_pScene[SC_FLASHMAN] = new CFlashmanScene;
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(const SCENEID& eID)
{
	m_eCurScene = eID;
	
	if (m_ePreScene != m_eCurScene)
	{
		m_pScene[m_eCurScene]->Initialize();
		m_ePreScene = m_eCurScene;
	}
	
}

void CSceneMgr::Update(void)
{
	m_pScene[m_eCurScene]->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene[m_eCurScene]->Late_Update();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pScene[m_eCurScene]->Render(_hDC);
}

void CSceneMgr::Release(void)
{
	for (int i = SC_START; i < SC_END; ++i)
	{
		Safe_Delete<CScene*>(m_pScene[i]);
	}
}
