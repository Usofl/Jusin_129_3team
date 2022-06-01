#pragma once
#include "Player.h"
class CJunPlayer :
	public CPlayer
{
public:
	CJunPlayer();
	virtual ~CJunPlayer();

	// CPlayer을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	
private:
	virtual void Key_Input(void) override;
private:
	D3DXVECTOR3 Tank[4];
	D3DXVECTOR3 TankHead[4];
	D3DXVECTOR3 Po;
	D3DXVECTOR3 Po_One;
	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;
	D3DXMATRIX		m_HmatScale, m_HmatRotZ, m_HmatTrans;
	D3DXVECTOR3 vHeadPos;
	INFO	m_HeadInfo;
	D3DXMATRIX m_HeadMat;
private:
	float m_fPoAngle;
};

