#pragma once
#include "Scene.h"
#include "Zelda_Obj.h"

class CZeldaEditScene : public CScene
{
public:
	CZeldaEditScene();
	virtual ~CZeldaEditScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

private:
	virtual void Key_Input(void) override;

private:
	float m_fSpeed;
	POINT					m_pt;
	CZelda_Obj*				m_pZelda_Obj;
	std::vector<CZelda_Obj*> m_vecZelda_Obj[ZELDAOBJ_END];
	ZELDA_OBJID				m_Zelda_Obj_Id;
};

