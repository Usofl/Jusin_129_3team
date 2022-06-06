#pragma once
#include "Obj.h"
#include "JunPlayer.h"
class CFortress_Monster_Bullet : public CObj
{
public:
	CFortress_Monster_Bullet();
	virtual ~CFortress_Monster_Bullet();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;	
	virtual void Release(void) override;

public:
	inline void			Set_Player(CJunPlayer* _pPlayer) { pJunPlayer = _pPlayer; }	
	void				Get_Monster_PosX(const float& _fX) { m_fMonster_PosX = _fX; }
	
	void				Get_Monster_Dir(const D3DXVECTOR3& _Dir) { m_tInfo.vLook = _Dir; }		// �÷��̾� - ���� ���� ���� �������� �Լ�

private:
	D3DXVECTOR3		m_tInfo_Bullet_Local[11];
	D3DXVECTOR3		m_tInfo_Bullet_World[11];

	float		m_fAir_Shoot;
	float		m_fShoot_Power;

	float		m_fMonster_PosX;


	CJunPlayer*		pJunPlayer;
};

