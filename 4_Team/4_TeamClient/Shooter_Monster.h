#pragma once
#include "Monster.h"
class CShooter_Monster : public CMonster
{
public:
	CShooter_Monster();
	CShooter_Monster(const float& _fX, const float& _fY);
	~CShooter_Monster();

public:
	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	float m_fXSize;
	float m_fYSize; 
	float m_fRevolutionAngle;

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];

	D3DXVECTOR3		m_vHeadPoint[2];
	D3DXVECTOR3		m_vHeadDrawPoint[2];
};

