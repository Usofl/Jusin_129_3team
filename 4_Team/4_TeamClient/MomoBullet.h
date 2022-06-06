#pragma once
#include "Momo_Obj.h"
class CMomoBullet :
	public CMomo_Obj
{
public:
	CMomoBullet();
	virtual ~CMomoBullet();
	
public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	D3DXVECTOR3 m_vBulletPoint[12];
	D3DXVECTOR3 m_vOriginalBulletPoint[12];
};

