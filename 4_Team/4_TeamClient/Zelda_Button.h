#pragma once
#include "Zelda_Obj.h"
class CZelda_Button : public CZelda_Obj
{
public:
	CZelda_Button();
	CZelda_Button(const float& _fX, const float& _fY);
	virtual ~CZelda_Button();

public:
	// CZelda_Obj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
};

