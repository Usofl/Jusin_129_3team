#pragma once
#include "Player.h"
class CJunPlayer :
	public CPlayer
{
public:
	CJunPlayer();
	virtual ~CJunPlayer();

	// CPlayer��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;
};

