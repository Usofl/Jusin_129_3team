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
	void Move(void);
public:
	inline void Set_Pos_Dir(float _x, float _y, D3DXVECTOR3 _vDir, int _iBullDir, float _fSpeed) {
		m_tInfo.vPos.x = _x;  m_tInfo.vPos.y = _y; m_tInfo.vDir = _vDir; m_fAngle = D3DXVec3Dot(&m_tInfo.vDir, &vSu);
		iBulletDir = _iBullDir; m_fSpeed = _fSpeed;
	}; //m_tInfo.vPos.x = _x;};

private:
	D3DXVECTOR3 vPoint[4];
	//D3DXVECTOR3 vDir;
	float m_fSpeed;
	float m_fTempTime;
	int  iBulletDir;
	D3DXVECTOR3 vSu;
};

