#pragma once
#include "Obj.h"
class CFortress_HPBar :
	public CObj
{
public:
	CFortress_HPBar();
	virtual ~CFortress_HPBar();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

