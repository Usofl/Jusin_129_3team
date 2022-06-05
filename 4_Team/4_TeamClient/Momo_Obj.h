#pragma once
#include "Obj.h"
class CMomo_Obj :
	public CObj
{
public:
	CMomo_Obj();
	~CMomo_Obj();

public:
	virtual		void		Initialize(void)	PURE;
	virtual		const int	Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC _hDC)	PURE;
	virtual		void		Release(void)		PURE;
};

