#pragma once
#include "Scene.h"
#include "FlashmanPlayer.h"

class CFlashmanScene : public CScene
{
public:
	CFlashmanScene();
	virtual ~CFlashmanScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;

private:
	CFlashmanPlayer*	m_pPlayer[FLASHMAN_END];
	FLASHMAN_PLAYERID	m_eFlashMan_id;

	D3DXVECTOR3			m_vFeildLine[2];
};

