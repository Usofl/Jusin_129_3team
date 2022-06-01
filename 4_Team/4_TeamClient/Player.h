#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	

	
	virtual void Initialize(void) PURE;

	virtual void Update(void) PURE;

	virtual void Late_Update(void) PURE;

	virtual void Render(HDC hDC) PURE;

	virtual void Release(void) PURE;

};


