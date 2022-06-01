#pragma once
#include "Player.h"

class CZeldaPlayer : public CPlayer
{
public:
	CZeldaPlayer();
	virtual ~CZeldaPlayer();

	// CPlayer을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;

private:
	D3DXVECTOR3		m_vRectPoint[4];
	D3DXVECTOR3		m_vDrawPoint[4];
};

