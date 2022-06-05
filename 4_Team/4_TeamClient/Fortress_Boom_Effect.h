#pragma once
#include "Obj.h"
class CFortress_Boom_Effect : public CObj
{
public:
	CFortress_Boom_Effect();
	CFortress_Boom_Effect(const float & _fX, const float & _fY);
	virtual ~CFortress_Boom_Effect();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bDead;

	int m_iRed;

	float m_fMagnify;

	std::vector<float> m_vecSize;
	std::vector<D3DXVECTOR3> m_vecPoint;
	std::vector<D3DXVECTOR3> m_vecDrawPoint;
};

