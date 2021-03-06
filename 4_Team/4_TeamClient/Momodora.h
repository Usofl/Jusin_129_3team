#pragma once
#include "Scene.h"
#include "MomodoraPlayer.h"
#include "MomoSword.h"
#include "Monster.h"
#include "MomoBullet.h"
#include "Momo_HpBar.h"

class CMomodora : public CScene
{
public:
	CMomodora();
	virtual ~CMomodora();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;

public:
	inline CMomodoraPlayer* Get_Player(void) { return m_pPlayer; }

private:
	CObj* m_pTarget;

	CMomodoraPlayer*	m_pPlayer;
	CMomo_HpBar	* m_pHPBar;

	list<CMomoSword*>	MomoSwordList;
	list<CMonster*>		m_listMonsterList;
	list<CMomoBullet*>	MomoBulletList;

	int					m_iRandom_Spawn;

	bool				m_bSword_On;
};

