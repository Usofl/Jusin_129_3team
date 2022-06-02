#pragma once
#include "Obj.h"
class CJunBullet :
	public CObj
{
public:
	CJunBullet();
	virtual ~CJunBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	inline void Set_Pos_Angle(float _x, float _y, float _Angle) { m_tInfo.vPos.x = _x;  m_tInfo.vPos.y = _y; }; //m_tInfo.vPos.x = _x;};
};

