#pragma once
#include "Obj.h"
class CFortress_Bullet_Effect : public CObj
{
public:
	CFortress_Bullet_Effect();
	CFortress_Bullet_Effect(const float& _fX, const float& _fY);
	virtual ~CFortress_Bullet_Effect();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bDead;
	int m_iSize;
	float m_fAngle;
	float m_fTime;
	float m_fGravity;
	float m_fPower;

	D3DXVECTOR3		m_vPoint;
	D3DXVECTOR3		m_vDrawPoint;
};

