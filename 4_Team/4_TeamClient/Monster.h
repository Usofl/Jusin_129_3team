#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual		void		Initialize(void)	PURE;
	virtual		const int	Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC _hDC)	PURE;
	virtual		void		Release(void)		PURE;

public:
	inline void Set_HP(const int& _iHP) { m_iHP = _iHP; }
	
	inline const int& Get_HP(void) { return m_iHP; }

protected:
	int		m_iHP;
};
