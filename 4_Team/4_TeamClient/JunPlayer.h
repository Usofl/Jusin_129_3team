#pragma once
#include "Player.h"
#include "JunBullet.h"
class CJunPlayer : public CPlayer
{
public:
	enum STATE {IDLE, FALLEN ,END};
public:
	CJunPlayer();
	virtual ~CJunPlayer();

	// CPlayer을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	inline const bool& Get_NextLine(void) { return m_bNextLine; };
	inline const STATE& Get_State(void) { return m_eCurState; };

	inline void Set_NextLine(const bool& _bNextLine) { m_bNextLine = _bNextLine; };
	inline void Set_State(const STATE& _eState) { m_eCurState = _eState; };

private:
	virtual void Key_Input(void) override;
	void OffSet(void);

	void Shoot(void);

private:
	D3DXVECTOR3 Tank[4];
	D3DXVECTOR3 TankHead[4];

	D3DXVECTOR3 Po;
	D3DXVECTOR3 Po_One;
	D3DXVECTOR3 Po_Dir;
	D3DXVECTOR3 OriPo_Dir;
	
	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;
	D3DXMATRIX		m_HmatScale, m_HmatRotZ, m_HmatTrans;
	
	D3DXVECTOR3 vHeadPos;
	
	INFO	m_HeadInfo;
	
	D3DXMATRIX m_HeadMat;

	STATE			m_ePreState;
	STATE			m_eCurState;

private:
	int m_iAngleCount;

	float m_fPoAngle;
	float BeforePoAngle;
	float BeforeAngle;
	float m_fShootPower;

	float m_fFallenTime;

	bool  m_bNextLine;

	CJunBullet* Bullet;
	//list<CJunBullet*> BulletList;
};

