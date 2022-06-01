#pragma once
#include "Scene.h"

#include "Brawl_Stars_Player.h"

class CBrawl_Stars_Scene :
	public CScene
{
public:
	CBrawl_Stars_Scene();
	virtual ~CBrawl_Stars_Scene();

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;

private:
	list<CObj*> m_Brawl_List[BRAWL_END];

	CBrawl_Stars_Player*	m_pBrawl_Stars_Player;
	
};

