#pragma once
#include "Scene.h"
#include "JunPlayer.h"
#include "JunBullet.h"
#include "Fortress_Monster.h"
#include "LineMgr.h"
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
	virtual void Key_Input(void) override;

private:
	CJunPlayer * JunPlayer;
	CJunBullet * JunBullet;
	CFortress_Monster * FortressMonster;

	list<CObj*> RenderList;
	list<CJunBullet*>* BulletList;
	list<CFortress_Monster_Bullet*>* Monster_Bullet_List;
	/*LINEPOINT TempLine = { 50,100 };
	LINEPOINT TempLine2 = { 270,100 };*/

	

	LINE m_Line;
	//CLine TempL = {};
	
	//Line Temp;
	int iArray[5];
};

