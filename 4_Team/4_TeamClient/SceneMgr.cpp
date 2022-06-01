#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene()
	, m_eCurScene(SC_END)
	, m_ePreScene(SC_END)
{
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
		switch (m_eCurScene)
		{
		case SC_FORTRESS:
			m_pScene[SC_FORTRESS] = new CFortress;
			break;
		}
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
