#pragma once

#include  "Brawl_Stars_Block.h"

class CBlockMgr
{
public:
	CBlockMgr();
	~CBlockMgr();

public:
	void			Initialize(void);
	const int		Update(void);
	void			Late_Update(void);
	void			Render(HDC hDC);
	void			Release(void);

	void			Key_Input(void);

public:
	static			CBlockMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBlockMgr;
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
	static CBlockMgr*					m_pInstance;
	list<CBrawl_Stars_Block*>			m_Block_List;
};

