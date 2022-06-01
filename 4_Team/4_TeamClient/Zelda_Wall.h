#pragma once
#include "Zelda_Obj.h"
class CZelda_Wall : public CZelda_Obj
{
public:
	CZelda_Wall();
	virtual ~CZelda_Wall();

public:
	// CZelda_Obj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

