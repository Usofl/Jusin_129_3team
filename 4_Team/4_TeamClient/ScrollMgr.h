#pragma once
#include "Include.h"

class CObj;

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	inline const float&		Get_ScrollX(void) { return m_fScrollX; }
	inline const float&		Get_ScrollY(void) { return m_fScrollY; }

	inline void		Plus_ScrollX(const float& _fX) { m_fScrollX += _fX; }
	inline void		Plus_ScrollY(const float& _fY) { m_fScrollY += _fY; }

	inline void		Set_ScrollX(const float& _fX) { m_fScrollX = _fX; }
	inline void		Set_ScrollY(const float& _fY) { m_fScrollY = _fY; }

	void			Main_Scroll_Lock(void);
	void			Scroll_Lock_Fortress(void);

	const bool		Fix_Cheak(const CObj* _pTarget);

public:
	static		CScrollMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
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
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
	float					m_fScrollY;
};

