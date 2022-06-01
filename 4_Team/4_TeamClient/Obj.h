#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO&				Get_Info(void) const { return m_tInfo; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		const int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

	inline const RENDERID& Get_RenderID(void) { return m_eRender; }

	void Update_Matrix(void);

protected:
	INFO		m_tInfo;
	MATINFO		m_tMatInfo;

	float		m_fAngle;

	RENDERID	m_eRender;
};
