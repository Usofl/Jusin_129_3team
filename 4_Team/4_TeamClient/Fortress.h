#pragma once
#include "Scene.h"
#include "JunPlayer.h"
#include "JunBullet.h"
#include "Fortress_Monster.h"
#include "Fortress_Bullet_Effect.h"
#include "LineMgr.h"
#include "Fortress_HPBar.h"
class CFortress :
	public CScene
{
public:
	CFortress();
	virtual ~CFortress();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;

	void LineMaker(void);
	void OffSet(void);

public:
	const bool MonsterCollision_Check(float _fMonX, float _fMonY,float _fBulletX, float _fBulletY);
	
public:
	inline list<CJunBullet*>* Get_JunBulletList(void) { return &JunBulletList;	};
	inline list<CFortress_Monster_Bullet*>* Get_Monster_Bullet_List(void) { return &Monster_Bullet_List; };
	inline const bool&	Get_Player_Turn() { return m_bPlayer_Turn; }
	inline const bool&	Get_Monster_Turn() { return m_bMonster_Turn; }

	inline void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	inline void	Set_Player_Turn(const bool& _bPTurn) { m_bPlayer_Turn = _bPTurn; }
	inline void	Set_Monster_Turn(const bool& _bMTurn) { m_bMonster_Turn = _bMTurn; }

private:
	CObj* m_pTarget;
	
	CJunPlayer * JunPlayer;
	CJunBullet * JunBullet;
	CFortress_Monster * FortressMonster;
	list<CJunBullet*> JunBulletList;
	list<CFortress_Bullet_Effect*> m_list_Bullet_Effect;
	list<CFortress_Monster_Bullet*> Monster_Bullet_List;

	CFortress_HPBar	* HPBar;

	//static list<CJunBullet*>* BulletList;
	/*LINEPOINT TempLine = { 50,100 };
	LINEPOINT TempLine2 = { 270,100 };*/

	LINE m_Line;
	//CLine TempL = {};
	
	//Line Temp;
	int iArray[5];

	bool m_bPlayer_Turn;
	bool m_bMonster_Turn;

	int iEnemyDamage;
	int iPlayerDamage;
};

