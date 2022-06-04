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
	inline void Set_Pos_Dir(const float& _x, const float& _y, const D3DXVECTOR3& _vDir, const int& _iBullDir, const float& _fSpeed)
	{
		m_tInfo.vPos.x = _x;  
		m_tInfo.vPos.y = _y; 
		m_tInfo.vDir = _vDir; 
		m_fAngle = D3DXVec3Dot(&m_tInfo.vDir, &vSu);
		m_iBulletDir = _iBullDir;
		m_fSpeed = _fSpeed;
	}; //m_tInfo.vPos.x = _x;};

	inline BULLET_ID Get_BulletID(void) { return m_BulletID; };
	inline void		 Set_BulletID(const BULLET_ID& _ID) { m_BulletID = _ID; };

private:
	D3DXVECTOR3 vPoint[4];
	//D3DXVECTOR3 vDir;
	float m_fTempTime;
	int m_iBulletDir;
	BULLET_ID m_BulletID;
	D3DXVECTOR3 vSu;
	D3DXVECTOR3 m_vDpDir;
	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;
};

