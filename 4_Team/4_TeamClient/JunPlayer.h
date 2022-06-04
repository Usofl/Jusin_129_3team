#pragma once
#include "Player.h"
#include "JunBullet.h"
#include "Fortress_Monster.h"
class CJunPlayer : public CPlayer
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

public:
	//list<CJunBullet*>* Get_BulletList(void) { return &BulletList; };
	INFO* Get_InfoJun(void) { return &m_tInfo; };
	float* Get_InfoY(void) { return &m_tInfo.vPos.y; };
	void Set_Angle(float _f) {
		m_fAngle = (_f);
	}
	const bool Get_NextLine(void) { return m_bNextLine; };
	void Set_NextLine(bool _b) { m_bNextLine = _b; };

public:
	void	Set_Turn(bool _Turn) { m_bPlayer_Turn = _Turn; }
	bool	Get_Turn() { return m_bPlayer_Turn; }

private:
	virtual void Key_Input(void) override;
	void OffSet(void);

private:
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
private:
	int m_iAngleCount;
	float m_fPoAngle;
	float BeforePoAngle;
	float BeforeAngle;
	float m_fShootPower;
	bool  m_bNextLine;

	bool m_bPlayer_Turn;
	CJunBullet* Bullet;

	//list<CJunBullet*> BulletList;
};

