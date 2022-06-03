#pragma once
#include "Zelda_Obj.h"
class CZelda_Wall : public CZelda_Obj
{
public:
	CZelda_Wall();
	CZelda_Wall(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY);
	virtual ~CZelda_Wall();

public:
	// CZelda_Obj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
};
