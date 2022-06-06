#pragma once
#include "Obj.h"

class CFortress_TargetLine :
	public CObj
{
public:
	CFortress_TargetLine();
	virtual ~CFortress_TargetLine();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:

	inline void Set_RenderArray(D3DXVECTOR3 _Array[30], bool _bRender) {
		for (int i = 0; 30 > i; ++i)
		{
			vRenderArray[i] = _Array[i];
			m_bRender = _bRender;
		}
	}

private:
	D3DXVECTOR3 vRenderArray[30];
	bool m_bRender;
	//CJunPlayer* m_pPlayer;

	
	
};

