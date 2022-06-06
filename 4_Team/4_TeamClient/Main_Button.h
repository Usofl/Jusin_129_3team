#pragma once
#include "Obj.h"
class CMain_Button : public CObj
{
public:
	enum POINT { POINT_LEFT_TOP, POINT_RIGHT_TOP, POINT_RIGHT_BOTTOM, POINT_LEFT_BOTTOM, POINT_END };

public:
	CMain_Button();
	CMain_Button(const float& _fX, const float& _fY);
	virtual ~CMain_Button();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	inline	const SCENEID& Get_SceneId(void) { return m_eSceneId; }
	inline	void Set_SceneId(const SCENEID& _eSceneId) { m_eSceneId = _eSceneId; }

private:
	float			m_fXSize;
	float			m_fYSize;

	SCENEID			m_eSceneId;

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];
};

