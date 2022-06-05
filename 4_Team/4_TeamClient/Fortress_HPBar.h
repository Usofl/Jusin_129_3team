#pragma once
#include "Obj.h"
class CFortress_HPBar :
	public CObj
{
public:
	enum POINT { POINT_LEFT_TOP, POINT_RIGHT_TOP, POINT_RIGHT_BOTTOM, POINT_LEFT_BOTTOM, POINT_END };

public:
	CFortress_HPBar();
	CFortress_HPBar(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY);
	virtual ~CFortress_HPBar();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	/*CJunPlayer*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CJunPlayer;
		}

		return m_pInstance;
	}*/
private:
	D3DXVECTOR3		m_vHPPoint[4];
	D3DXVECTOR3		m_vOriginalPoint[4];
	D3DXMATRIX		matScale, matRotZ, matTrans;
	D3DXVECTOR3		m_vLookX;

	float			m_fXSize;
	float			m_fYSize;
	float			m_fGague;

//	CJunPlayer * JunPlayer;
//	CJunPlayer*		m_pInstance;
};

