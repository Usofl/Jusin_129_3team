#pragma once
#include "Scene.h"
class CZeldaEditScene : public CScene
{
public:
	CZeldaEditScene();
	virtual ~CZeldaEditScene();

	// CScene��(��) ���� ��ӵ�
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
	//CNotBeing*				m_Tile;
	ZELDA_OBJID				m_Zelda_Obj_Id;
};

