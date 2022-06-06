#pragma once
#include "Monster.h"
class CFollower_Monster : public CMonster
{
public:
	enum POINT { POINT_LEFT_TOP, POINT_RIGHT_TOP, POINT_RIGHT_BOTTOM, POINT_LEFT_BOTTOM, POINT_END };

public:
	CFollower_Monster();
	CFollower_Monster(const float& _fX, const float& _fY);
	virtual ~CFollower_Monster();

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

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];

	D3DXVECTOR3		m_vHeadPoint[2];
	D3DXVECTOR3		m_vHeadDrawPoint[2];
};

