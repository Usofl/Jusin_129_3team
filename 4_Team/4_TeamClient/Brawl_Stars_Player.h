#pragma once
#include "Player.h"
class CBrawl_Stars_Player :
	public CPlayer
{
public:
	CBrawl_Stars_Player();
	virtual ~CBrawl_Stars_Player();

public:
	virtual void Initialize(void) override;
	virtual const int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}

public:
	void		Key_Input(void);
	
private:
	INFO		m_tInfo_Body_Local[4];
	INFO		m_tInfo_Body_World[4];

	INFO		m_tInfo_Posin_Local[2];
	INFO		m_tInfo_Posin_World[2];


	D3DXMATRIX		m_PosinWorld;

private:
	float		m_fSpeed;

	float		m_fAngle_Body;
	float		m_fAngle_Posin;

	float		m_iRandom;
	
	DWORD		m_dwShoot_Bullet;

	std::list<CObj*>*	m_pBullet;

	/*

	D3DXVECTOR3		m_vPlayerPos;	// ¿ßƒ° ∫§≈Õ

	D3DXVECTOR3		m_vPlayerDir;	// πÊ«‚ ∫§≈Õ
	D3DXVECTOR3		m_vPlayerLook;	// πÊ«‚ ∫§≈Õ

	D3DXVECTOR3		m_vPlayerNormal;	// π˝º± ∫§≈Õ*/
};

