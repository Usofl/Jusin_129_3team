#pragma once
#include "Obj.h"
class CFortress_HPBar :
	public CObj
{
public:
	enum POINT { POINT_LEFT_TOP, POINT_RIGHT_TOP, POINT_RIGHT_BOTTOM, POINT_LEFT_BOTTOM, POINT_END };

public:
	CFortress_HPBar();
	CFortress_HPBar(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY);
	virtual ~CFortress_HPBar();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	inline void Set_Lest_HP(const int& _MaxHP, const int& _LestHP) 
	{
		if (0 < _LestHP)
		{
			m_fLest_HP = (float)((_LestHP * 100 / _MaxHP)) * 0.01f;
		}
		else
		{
			m_fLest_HP = 0.f;
		}
	}

private:
	D3DXVECTOR3		m_vHP_Point[POINT_END];
	D3DXVECTOR3		m_vOriginalPoint[POINT_END];

	D3DXVECTOR3		m_vLest_HP_Point;
	D3DXVECTOR3		m_vLest_OriginalPoint;

	float			m_fLest_HP;

	float			m_fXSize;
	float			m_fYSize;

	float			m_fGague;

//	CJunPlayer * JunPlayer;
//	CJunPlayer*		m_pInstance;
};

