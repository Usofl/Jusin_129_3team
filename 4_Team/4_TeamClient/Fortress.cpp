#include "stdafx.h"
#include "Fortress.h"


CFortress::CFortress()
	: JunPlayer(nullptr)
{

}

CFortress::~CFortress()
{
	Release();
}

void CFortress::Initialize(void)
{
	if (nullptr == JunPlayer)
	{
		JunPlayer = new CJunPlayer;
		
	}

	BulletList = (JunPlayer->Get_BulletList());

	/*LINE TempPo[3]{};
	TempPo[0].tLPoint = { 300,50 };
	TempPo[0].tRPoint = { 300,200 };
	TempPo[1].tLPoint = { 300,50 };
	TempPo[1].tRPoint = { 300,200 };
	TempPo[2].tLPoint = { 300,50 };
	TempPo[2].tRPoint = { 300,200 };

	CLine LineArray[3];*/
	//for (int i = 0; 3 > i; ++i)
	//{
	//	LineArray[i] = { TempPo[i].tLPoint ,TempPo[i].tRPoint };
	//}

	/*for (int i = 0; 3 > i; ++i)
	{
		CLineMgr::Get_Instance()->Create_Line(&LineArray[i]);
	}*/

	
	TempLine.tLPoint = { 100,50 };
	TempLine.tRPoint = { 300,200 };
	TempL = { TempLine.tLPoint,TempLine.tRPoint };
	LINEMGR->Create_Line(&TempL);
	//CLineMgr::Get_Instance()->
		
	/*for (int i = 0; 6 > i; ++i)*/
	//LineArray =  TempLine,TempLine2 ;
	
	//RenderList.
}

void CFortress::Update(void)
{
	JunPlayer->Update();
	for (auto& iter : *BulletList)
	{
		iter->Update();
	}
}

void CFortress::Late_Update(void)
{
	JunPlayer->Late_Update();
	for (auto& iter : *BulletList)
	{
		iter->Update();
	}
}

void CFortress::Render(HDC _hDC)
{
	

	JunPlayer->Render(_hDC);
	for (auto& iter : *BulletList)
	{
		iter->Render(_hDC);
	}
	LINEMGR->Render(_hDC);

	/*for (int i = 0; 6 > i; ++i)
	{
		MoveToEx(_hDC, LineArray[i].tLPoint.fX, LineArray[i].tLPoint.fY, nullptr);
		LineTo(_hDC, LineArray[i+1].tLPoint.fX, LineArray[i + 1].tLPoint.fY);
	}
	*/
	//LineArray[0].Render(_hDC);
	/*MoveToEx(_hDC,., 320, nullptr);
	LineTo(_hDC, 500, 320);*/
	
	
}

void CFortress::Release(void)
{

	Safe_Delete<CJunPlayer*>(JunPlayer);
	for (auto& iter : *BulletList)
	{
		iter->Release();
	}

}

void CFortress::Key_Input(void)
{

}
