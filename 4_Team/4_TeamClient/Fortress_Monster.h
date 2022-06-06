#pragma once
#include "Obj.h"
#include "JunPlayer.h"
#include "Fortress_Monster_Bullet.h"

class CFortress_Monster : public CObj
{
public:
	CFortress_Monster();
	virtual ~CFortress_Monster();

public:
	virtual void Initialize(void) override;
	virtual const int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	inline const int&	Get_Hp() { return m_iHp; }

	inline void			Set_Player(CJunPlayer* _pPlayer) { pJunPlayer = _pPlayer; }		// 플레이어를 선언을했지만 동적할당(new)를 하지않아서 원본값을 가지고올수없다. 그래서 함수를 사용해서 주소값을 가지고와야됨

	inline void			Set_Hp(const int& _Hp) { m_iHp -= _Hp; }
	inline void			Set_Move_On(const bool& _bOn) { m_bMove_On = _bOn; }

public:
	void		Shoot_Bullet();
	void		Move();

	void		Set_Angle(float _f) {	m_fAngle = (_f);}
	

private:
	INFO			m_tInfo_Body_Local[16];
	INFO			m_tInfo_Body_World[16];

	INFO			m_tInfo_Head_Local[4];
	INFO			m_tInfo_Head_World[4];
		
	INFO			m_tInfo_Posin_Local[5];
	INFO			m_tInfo_Posin_World[5];

	D3DXVECTOR3		m_tInfo_Test_Dir;
	D3DXMATRIX		matTrans_Posin;

private:
	int				m_iHp;
	int				m_iRandom_Move;

	float			m_fRandom;
		
	float			m_fAngle_Body;
	float			m_fAngle_Posin;

	bool			m_bRandom;
	bool			m_bRandom_Move;
	bool			m_bShoot;
	bool			m_bMonster_Turn;
	bool			m_bMove_On;

	DWORD			m_dwShootCount;
	DWORD			m_dwShootDelay;
	D3DXMATRIX		m_PosinWorld;

	D3DXMATRIX		m_Po;		// 포신값실험중

	CFortress_Monster_Bullet*	Fortress_Monster_Bullet;

	CJunPlayer*		pJunPlayer;		// 플레이어 포인터로 플레이어 선언( nullptr 로 초기화 해야됨 , 쓰래기 값이 들어가있음 ), (객체 생성( new ) 할당을 안하면 원본에 있는 값을 가지고올수없다 )
};

