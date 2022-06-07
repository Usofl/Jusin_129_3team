#pragma once
#include "Obj.h"
class CJunBullet : public CObj
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

private:
	void Move(void);
	void Local_Initialize(void);
	void Dp_Local_Initialize(void);

public:
	inline void Set_Pos_Dir(const float& _x, const float& _y, const D3DXVECTOR3& _vDir, const int& _iBullDir, const float& _fSpeed,  D3DXVECTOR3 _vOne)
	{
		m_tInfo.vPos.x = _x;  
		m_tInfo.vPos.y = _y; 
		m_tInfo.vDir = _vDir; 
		D3DXVec3Normalize(&_vOne, &_vOne);
		if (_vOne.y < 0)
		{
			m_fAngle = -acosf(D3DXVec3Dot(&vSu, &_vOne));
		}
		else
		{
			m_fAngle = acosf(D3DXVec3Dot(&vSu, &_vOne));
		}

		m_iBulletDir = _iBullDir;
		m_fSpeed = _fSpeed;

		m_vOne = _vOne;
	}; //m_tInfo.vPos.x = _x;};

	inline BULLET_ID Get_BulletID(void) { return m_BulletID; };
	inline void		 Set_BulletID(const BULLET_ID& _ID) { m_BulletID = _ID; };
	D3DXVECTOR3		 Get_DpBullet(int _iIndex) { return m_vDpPoint[_iIndex]; };
	void			 Set_DpBullet_Die(int _iIndex) {m_vDpPoint[_iIndex] -= {3000.f, 3000.f, 0.f }; m_bDp_Line = true; m_iDestroy_Count--;};
	bool Get_Destroy_Count(void) { 
		if (m_iDestroy_Count <= 0)
		{
			return true;
		}
		return false;
	}
	const bool		 Get_Dp_Line(void) { return m_bDp_Line; };

private:
	/*D3DXVECTOR3 m_vLocalPoint[4];
	D3DXVECTOR3 m_vWorldPoint[4];*/
	D3DXVECTOR3 m_vLocalPoint[12];
	D3DXVECTOR3 m_vWorldPoint[12];

	D3DXVECTOR3 m_vDpPoint[10];

	INFO m_DpINFO_Local[6];
	INFO m_DpINFO_World[6];



	D3DXVECTOR3 m_vLocalWind[16];
	D3DXVECTOR3 m_vWorldWind[16];

	//D3DXVECTOR3 vDir;
	float m_fTempTime;
	float m_fFallValue;
	int m_iBulletDir;
	bool m_bDp_Line;
	int m_iDestroy_Count;
	BULLET_ID m_BulletID;
	D3DXVECTOR3 vSu;
	D3DXVECTOR3 m_vOne;
	D3DXVECTOR3 m_vDpDir;
	

	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;
	CJunBullet* m_DpBullet[10];
};

