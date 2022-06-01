#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	
public:
	
	virtual void Initialize(void) PURE;

	virtual int Update(void) PURE;

	virtual void Late_Update(void) PURE;

	virtual void Render(HDC hDC) PURE;

	virtual void Release(void) PURE;

};


