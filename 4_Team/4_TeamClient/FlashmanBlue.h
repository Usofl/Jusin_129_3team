#pragma once
#include "FlashmanPlayer.h"
class CFlashmanBlue : public CFlashmanPlayer
{
public:
	CFlashmanBlue();
	virtual ~CFlashmanBlue();

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

