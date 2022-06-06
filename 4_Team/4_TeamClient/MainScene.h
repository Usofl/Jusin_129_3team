#pragma once
#include "Scene.h"
class CMainScene :
	public CScene
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
	virtual void Key_Input(void) override;
};

