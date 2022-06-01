#pragma once
#include "Obj.h"
class CMomoDoraMgr
{
private:
	CMomoDoraMgr();
	~CMomoDoraMgr();

public:
	void		Add_Object(MOMOID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(MOMOID eID);

private:
	list<CObj*>	m_MomodoraList[MOMO_END];

public:
	static		CMomoDoraMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CMomoDoraMgr;
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
	static CMomoDoraMgr*			m_pInstance;
};

