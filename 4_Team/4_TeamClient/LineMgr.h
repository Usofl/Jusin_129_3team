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

	bool		Collision_Line(float& _fX, float* _pY);
	const bool  Collision_JunLine(float & _fX, float & _fY, float& _fAngle);
	const bool  Collision_TargetLine(float _fX, float  _fY);
	const float Collision_Monster_Line(float& _fX, float* _pY);
	bool		Collision_DeLine(const float& _fX, const float& _fY);
	void		Load_Line();
	void		Create_Line(const float& _fLX, const float& _fLY, const float& _fRX, const float& _fRY);
	
public:
	list<CLine*> Get_LineList(void) {
		return m_LineList;
	}
		
	
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


