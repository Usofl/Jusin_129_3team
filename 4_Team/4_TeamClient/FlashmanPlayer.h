#pragma once
#include "Player.h"
class CFlashmanPlayer :
	public CPlayer
{
public:
	enum POINT {POINT_HEAD, POINT_NECK, POINT_GROIN, 
		POINT_LEFT_KNEE, POINT_LEFT_FOOT,
		POINT_RIGHT_KNEE, POINT_RIGHT_FOOT,
		POINT_LEFT_ELBOW, POINT_LEFT_HAND,
		POINT_RIGHT_ELBOW, POINT_RIGHT_HAND, POINT_END};

	enum STATE {IDLE, WALK, JUMPING, CHANGE, ATTACK1, ATTACK2, END};

public:
	CFlashmanPlayer();
	virtual ~CFlashmanPlayer();

public:
	virtual void Initialize(void) PURE;
	virtual const int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

	inline void Set_State(const STATE& _State) { m_eCurState = _State; }

protected:
	virtual void Key_Input(void) PURE;
	void	Fallen(void);
	void	Jumping(void);
	void	Change(void);
	void	ChangeJumping(void);

protected:
	bool			m_bAir;

	float			m_fSize;
	float			m_fScale;
	float			m_fJumpPower;
	float			m_fJumpAngle;
	float			m_fJumpTime;

	STATE			m_ePreState;
	STATE			m_eCurState;

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];
};

