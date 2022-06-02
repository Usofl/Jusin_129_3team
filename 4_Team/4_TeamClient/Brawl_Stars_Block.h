#pragma once
#include "Obj.h"

class CBrawl_Stars_Block :
	public CObj
{
public:
	CBrawl_Stars_Block();
	virtual ~CBrawl_Stars_Block();

public:
	virtual void Initialize(void) override;
	virtual const int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	INFO	m_tInfo_Block_Local[7];
	INFO	m_tInfo_Block_World[7];



};

