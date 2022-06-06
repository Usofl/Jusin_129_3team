#pragma once
#include "Momo_Obj.h"
#include "MomoSword.h"

class CMomodoraPlayer :
	public CMomo_Obj
{
public:
	CMomodoraPlayer();
	virtual ~CMomodoraPlayer();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	void Key_Input(void);

	inline void Set_HP(const int& _iHP) { m_iHP -= _iHP; }
	inline const int&	Get_Hp(void) { return m_iHP; };
	inline const int&	Get_MaxHp(void) { return m_iMaxHP; }

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginalPoint[4];
	D3DXVECTOR3		m_vHeadPoint[2];
	D3DXVECTOR3		m_vOriginalHeadPoint[2];
	D3DXVECTOR3		m_vLookX;

	int		m_iHP;
	int		m_iMaxHP;

};

