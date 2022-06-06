#pragma once
#include "Scene.h"
#include "Main_Button.h"

class CJunPlayer;
class CJunBullet;
class CFortress_Bullet_Effect;
class CFortress_Boom_Effect;

class CMainScene : public CScene
{
public:
	CMainScene();
	virtual ~CMainScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	inline void Set_Bullet(CJunBullet* _pBullet) { m_pBullet = _pBullet; }

private:
	virtual void Key_Input(void) override;

	void Selete_Button(CMain_Button*& _pButton);

private:
	bool		m_bReady;
	SCENEID		m_eScene_Id;

	vector<CMain_Button*> m_vecButton;
	list<CFortress_Bullet_Effect*> m_list_Bullet_Effect;
	list<CFortress_Boom_Effect*> m_list_Boom_Effect;

	CJunPlayer* m_pPlayer;
	CJunBullet* m_pBullet;
};

