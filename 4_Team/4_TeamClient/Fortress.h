#pragma once
#include "Scene.h"
#include "JunPlayer.h"
#include "JunBullet.h"
#include "LineMgr.h"
class CFortress :
	public CScene
{
public:
	CFortress();
	virtual ~CFortress();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;
private:
	CJunPlayer * JunPlayer;
	CJunBullet * JunBullet;
	list<CObj*> RenderList;
	list<CJunBullet*>* BulletList;
	/*LINEPOINT TempLine = { 50,100 };
	LINEPOINT TempLine2 = { 270,100 };*/

	LINE m_Line;
	
	//CLine TempL = {};
	
	//Line Temp;
	int iArray[5];
};

