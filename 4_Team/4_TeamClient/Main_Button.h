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

	void Selected_Button(void);

public:
	inline	const SCENEID& Get_SceneId(void) { return m_eSceneId; }
	inline	void Set_SceneId(const SCENEID& _eSceneId) 
	{ 
		m_eSceneId = _eSceneId;
		switch (m_eSceneId)
		{
		case SC_START:
			swprintf_s(m_szButton_Name, L"START");
			m_iTextSize = 5;
			break;
		case SC_MAIN:
			swprintf_s(m_szButton_Name, L"MAIN");
			m_iTextSize = 4;
			break;
		case SC_ZELDA:
			swprintf_s(m_szButton_Name, L"ZELDA");
			m_iTextSize = 5;
			break;
		case SC_FLASHMAN:
			swprintf_s(m_szButton_Name, L"FLASHMAN");
			m_iTextSize = 8;
			break;
		case SC_ZELDA_EDIT:
			swprintf_s(m_szButton_Name, L"ZELDA_EDIT");
			m_iTextSize = 10;
			break;
		case SC_FORTRESS:
			swprintf_s(m_szButton_Name, L"FORTRESS");
			m_iTextSize = 8;
			break;
		case SC_BRAWL_STARS:
			swprintf_s(m_szButton_Name, L"BRAWL_STARS");
			m_iTextSize = 11;
			break;
		case SC_MOMO:
			swprintf_s(m_szButton_Name, L"UNTITLE");
			m_iTextSize = 7;
			break; 
		case SC_END:
			swprintf_s(m_szButton_Name, L"EXIT");
			m_iTextSize = 4;
			break;
		}
	}

private:
	float			m_fXSize;
	float			m_fYSize;

	int				m_iWidth;
	int				m_iRed;
	int				m_iTextSize;

	TCHAR			m_szButton_Name[32];

	SCENEID			m_eSceneId;

	D3DXVECTOR3		m_vPoint[POINT_END];
	D3DXVECTOR3		m_vDrawPoint[POINT_END];
};

