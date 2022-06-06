#pragma once
#include "Player.h"
#include "JunBullet.h"
#include "Fortress_TargetLine.h"

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
	inline void Set_TargetLine(CFortress_TargetLine* _pTargetLine) { m_pTargetLine = _pTargetLine; };


public:
	inline void			ReSet_Bullet(void)	{ m_pBullet = nullptr; };
	inline CJunBullet*	Get_Bullet(void)	{ return m_pBullet; };
	inline void			Minus_Hp(const int& _iDamage) { m_iHp -= _iDamage; };
	inline void			Plus_Hp(const int& _iHeal) { m_iHp += _iHeal; };
	inline void			Reset_Hp(void)		{ m_iHp = 100; };
	inline const int&	Get_Hp(void)		{ return m_iHp; };
	inline const int&	Get_MaxHp(void)		{ return m_iMaxHp; }

	inline CJunPlayer* Get_Player(void) { return this; }
	inline void Set_ReSetLine(void) { m_fShootPower = 0.f; m_fTempPower = 0.f; m_bTargetLine = false; }
	inline const bool& Get_RenderLine(void) { return m_bTargetLine; };
	inline void Set_RenderLine(void) { m_bTargetLine = false; };

public:
	

private:
	virtual void Key_Input(void) override;

	void Shoot(void);
	void Fallen(void);
	void Line_Calculation(void);

private:
	D3DXVECTOR3 m_vLocalTank[4];
	D3DXVECTOR3 m_vLocalTankHead[4];

	D3DXVECTOR3 m_vTank[4];
	D3DXVECTOR3 m_vTankHead[4];

	D3DXVECTOR3 m_vPo_One;
	D3DXVECTOR3 m_vLocal_Po_One;

	D3DXVECTOR3 m_vPo;
	D3DXVECTOR3 m_vLocal_Po;

	D3DXVECTOR3 Po_Dir;
	D3DXVECTOR3 OriPo_Dir;
	D3DXVECTOR3 m_vAfter_RenderLine[30];

	D3DXMATRIX		m_matScale, m_matRotZ, m_matTrans;
	D3DXMATRIX		m_HmatScale, m_HmatRotZ, m_HmatTrans;
	
	D3DXVECTOR3 m_vLineArray[200] ;
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
	float m_fRenderPower;
	float m_fFallenTime;

	bool  m_bNextLine;
	bool  m_bMaxPower;
	bool  m_bGageRender;
	bool  m_bTargetLine;
	float  m_fTempPower;
	bool m_bPlayer_Turn;
	CJunBullet* m_pBullet;
	CFortress_TargetLine* m_pTargetLine ;
	int m_iHp;
	int m_iMaxHp;

	
	//list<CJunBullet*> BulletList;
};

