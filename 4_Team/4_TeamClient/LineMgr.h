#pragma once
#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);

	bool		Collision_Line(float& _fX, float* pY);
	const float Collision_JunLine(float& _fX, float* pY);
	void		Load_Line();
	void		Create_Line(int _x, int _y, int _x2, int _y2);
		
	
public:
	static		CLineMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	static CLineMgr*		m_pInstance;
	LINE					m_Line;
	CLine*					m_CLine;
	list<CLine*>			m_LineList;
};


