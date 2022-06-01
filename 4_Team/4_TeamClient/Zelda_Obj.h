#pragma once
#include "Obj.h"
class CZelda_Obj : public CObj
{
public:
	enum POINT {POINT_LEFT_TOP, POINT_RIGHT_TOP, POINT_RIGHT_BOTTOM, POINT_LEFT_BOTTOM, POINT_END};
public:
	CZelda_Obj();
	virtual ~CZelda_Obj();

public:
	virtual		void		Initialize(void)	PURE;
	virtual		const int	Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC _hDC)		PURE;
	virtual		void		Release(void)		PURE;

protected:
	float			m_fSize;

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vDrawPoint[4];
};

