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
	virtual		void		Render(HDC _hDC)	PURE;
	virtual		void		Release(void)		PURE;

public:
	inline const float& Get_X_Size(void) { return m_fXSize; }
	inline const float& Get_Y_Size(void) { return m_fYSize; }

	inline void Set_X_Size(const float& _fCX) { m_fXSize = _fCX; }
	inline void Set_Y_Size(const float& _fCY) { m_fYSize = _fCY; }

protected:
	float			m_fXSize;
	float			m_fYSize;

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];
};

