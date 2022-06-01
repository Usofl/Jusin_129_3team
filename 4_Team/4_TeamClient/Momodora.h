#pragma once
#include "Scene.h"
#include "MomodoraPlayer.h"

class CMomodora :
	public CScene
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

private:
	CMomodoraPlayer*	m_pPlayer;
};

