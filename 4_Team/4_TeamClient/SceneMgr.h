#pragma once
#include "Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(const SCENEID& eID);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _hDC);
	void		Release(void);

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	inline CScene*&	Get_Scene(const SCENEID& _SceneID) { return m_pScene[_SceneID]; }

	inline const SCENEID&	Get_Scene_ID(void) { return m_eCurScene; }

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene[SC_END];

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;
};


