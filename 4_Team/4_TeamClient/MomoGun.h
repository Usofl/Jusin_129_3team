#pragma once
#include "Momo_Obj.h"
class CMomoGun :
	public CMomo_Obj
{
public:
	CMomoGun();
	virtual ~CMomoGun();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	CObj*	m_pMomoPlayer;

private:
	D3DXVECTOR3		m_vGunPoint[4];
	D3DXVECTOR3		m_vOriginalGunPoint[4];
	D3DXMATRIX		matScale, matRotZ, matTrans;
};

