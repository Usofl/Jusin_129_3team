#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual		void		Initialize(void)	PURE;
	virtual		const int	Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC hDC)		PURE;
	virtual		void		Release(void)		PURE;

	void Update_Matrix(void);

public:
	inline const RENDERID&  Get_RenderID(void) { return m_eRender; }

	inline const INFO&		Get_Info(void) const { return m_tInfo; }
	inline const MATINFO&	Get_Mat_Info(void) const { return m_tMatInfo; }
	inline const bool&		Get_Dead(void)		{ return m_bDead; }
	inline const float&		Get_Speed(void) const { return m_fSpeed; }

	inline void Set_Angle(const float& _fAngle) { m_fAngle = _fAngle; }
	inline void Set_Pos(const float& _fX, const float& _fY) { m_tInfo.vPos.x = _fX; m_tInfo.vPos.y = _fY; }
	inline void Set_Dead(const bool& _bDead) { m_bDead = _bDead; }
	inline void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

protected:
	INFO		m_tInfo;
	MATINFO		m_tMatInfo;

	float		m_fAngle;
	float		m_fSpeed;
	bool		m_bDead;

	RENDERID	m_eRender;
	CObj*		m_pTarget;
};
