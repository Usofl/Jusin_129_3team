#pragma once
#include "Momo_Obj.h"
class CMomoSword : public CMomo_Obj
{
public:
	CMomoSword();
	virtual ~CMomoSword();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	D3DXVECTOR3		m_vSwordPoint[4];
	D3DXVECTOR3		m_vLocalSwordPoint[4];
	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;

	float			m_fDistance;
};

