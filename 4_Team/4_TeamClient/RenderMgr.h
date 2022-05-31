#pragma once
#include "Obj.h"

class CRenderMgr
{
public:
	CRenderMgr();
	~CRenderMgr();

public:
	void Add_Render_Obj(CObj* _obj);
	void Render(HDC _hDC);

public:
	static		CRenderMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CRenderMgr;
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

private:
	static CRenderMgr*		m_pInstance;
	std::list<CObj*>	m_RenderSort[RENDER_END];
};

