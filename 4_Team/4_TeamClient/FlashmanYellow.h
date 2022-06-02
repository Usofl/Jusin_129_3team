#pragma once
#include "FlashmanPlayer.h"
class CFlashmanYellow : public CFlashmanPlayer
{
public:
	CFlashmanYellow();
	virtual ~CFlashmanYellow();

public:
	// CFlashmanPlayer��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;
};

