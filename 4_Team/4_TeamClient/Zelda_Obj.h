#pragma once
#include "Obj.h"
class CZelda_Obj : public CObj
{
public:
	CZelda_Obj();
	virtual ~CZelda_Obj();

public:
	virtual		void		Initialize(void)	PURE;
	virtual		const int	Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC hDC)		PURE;
	virtual		void		Release(void)		PURE;
};

