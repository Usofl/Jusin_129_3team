#pragma once
#include "Player.h"

class CZeldaPlayer : public CPlayer
{
private:
	enum VERTEX { ZELDA_LEFT_TOP, ZELDA_RIGHT_TOP, ZELDA_RIGHT_BOTTOM, ZELDA_LEFT_BOTTOM, ZELDA_LEFT_HAND, ZELDA_RIGHT_HAND, ZELDA_END };

public:
	CZeldaPlayer();
	virtual ~CZeldaPlayer();

	// CPlayer을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;

private:
	float			m_fSize;
	int				m_iHandSize;

	D3DXVECTOR3		m_vPoint[ZELDA_END];
	D3DXVECTOR3		m_vDrawPoint[ZELDA_END];
};

