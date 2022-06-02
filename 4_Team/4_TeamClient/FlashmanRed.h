#pragma once
#include "FlashmanPlayer.h"
class CFlashmanRed : public CFlashmanPlayer
{
public:
	CFlashmanRed();
	virtual ~CFlashmanRed();

public:
	// CFlashmanPlayer을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;
};

