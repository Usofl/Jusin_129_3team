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

	inline void			Set_Player(CJunPlayer* _pPlayer) { pJunPlayer = _pPlayer; }		// �÷��̾ ������������ �����Ҵ�(new)�� �����ʾƼ� �������� ������ü�����. �׷��� �Լ��� ����ؼ� �ּҰ��� ������;ߵ�

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

	D3DXMATRIX		m_Po;		// ���Ű�������

	CFortress_Monster_Bullet*	Fortress_Monster_Bullet;

	CJunPlayer*		pJunPlayer;		// �÷��̾� �����ͷ� �÷��̾� ����( nullptr �� �ʱ�ȭ �ؾߵ� , ������ ���� ������ ), (��ü ����( new ) �Ҵ��� ���ϸ� ������ �ִ� ���� ������ü����� )
};

