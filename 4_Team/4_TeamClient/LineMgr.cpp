#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float* pY)
{
	// ������ ������

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	float	x1(0.f), x2(0.f), y1(0.f), y2(0.f);

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			x1 = iter->Get_Info().tLPoint.fX;
			x2 = iter->Get_Info().tRPoint.fX;

			y1 = iter->Get_Info().tLPoint.fY;
			y2 = iter->Get_Info().tRPoint.fY;

			pTarget = iter;

			break;
		}
	}

	if (!pTarget)
		return false;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return true;
}

bool CLineMgr::Collision_DeLine(const float& _fX, const float& _fY)
{
	// ������ ������

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	//pTarget = *m_LineList.begin();

	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); )
	{
		bool bX = false, bY = false;

		float	LX = (*iter)->Get_Info().tLPoint.fX;
		float	RX = (*iter)->Get_Info().tRPoint.fX;

		float	LY = (*iter)->Get_Info().tLPoint.fY;
		float	RY = (*iter)->Get_Info().tRPoint.fY;

		float	pY(0.f);

		if ((_fX >= LX - 20.f && _fX <= RX + 20.f) || (_fX >= RX + 20.f && _fX <= LX - 20.f))
		{
			bX	= true;
		}

		if ((_fY <= LY + 20.f && _fY >= RY - 20.f) || (_fY <= RY - 20.f && _fY >= LY + 20.f))
		{
			bY = true;
		}

		// ���� ������ ���� ���� �����ؼ� �� ���̿� ������ �浹�ǰԲ�
		////L����  R������ �۴� ������ �����̶� �ݴ� ��찡 ���� �ȸԴ� �� 
		//if ((_fX >= (*iter)->Get_Info().tLPoint.fX && 
		//	_fX <= (*iter)->Get_Info().tRPoint.fX) && (_fY  <= (*iter)->Get_Info().tLPoint.fY &&
		//		_fY  >= (*iter)->Get_Info().tRPoint.fY))

		if (bX&&bY)
		{
			if (_fX - LX > 20.f && RX - _fX > 20.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX - 20.f - LX)) + LY;
				Create_Line(LX, LY, _fX - 20.f, pY);

				pY = (((RY - LY) / (RX - LX)) * (_fX + 20.f - LX)) + LY;
				Create_Line(_fX + 20.f, pY, RX, RY);
			}
			else if (_fX - LX > 30.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX - 30.f - LX)) + LY;
				Create_Line(LX, LY, _fX - 30.f, pY);
			}
			else if (RX - _fX > 30.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX + 30.f - LX)) + LY;
				Create_Line(_fX + 30.f, pY, RX, RY);
			}
			
			Safe_Delete(*iter);
			(iter) = m_LineList.erase((iter));

			return true;
		}

	/*	else if ((_fX >= (*iter)->Get_Info().tLPoint.fX &&
			_fX <= (*iter)->Get_Info().tRPoint.fX) && (_fY <= (*iter)->Get_Info().tRPoint.fY &&
				_fY >= (*iter)->Get_Info().tLPoint.fY))
		{
			Safe_Delete(*iter);
			(iter) = m_LineList.erase((iter));
			return true;
		}*/

		/*else if ()
		{

		}*/
		else
		{
			++iter;
		}

		//	int i = 5;

	}
	//for (auto& iter : m_LineList)
	//{
	//	if ((_fX >= iter->Get_Info().tLPoint.fX &&
	//		_fX <= iter->Get_Info().tRPoint.fX) && (_fY <= iter->Get_Info().tLPoint.fY &&
	//		_fY >= iter->Get_Info().tRPoint.fY))
	//	{
	//		pTarget = iter;
	//		/*&iter = m_LineList.erase(&iter);*/
	//		
	//	}
	//}

	if (!pTarget)
		return false;
	
	return true;
}

const bool CLineMgr::Collision_JunLine(float & _fX, float & _fY, float& _fAngle)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
			break;
		}
	}

	if (!pTarget)
	{
		for (auto& iter : m_LineList)
		{
			if ((_fX - 50.f >= iter->Get_Info().tLPoint.fX && _fX - 50.f <= iter->Get_Info().tRPoint.fX)
				|| (_fX + 50.f >= iter->Get_Info().tLPoint.fX && _fX + 50.f <= iter->Get_Info().tRPoint.fX))
			{
				pTarget = iter;
				break;
			}
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	D3DXVECTOR3 vTemp = { 1.f,0.f,0.f };
	D3DXVECTOR3 vTemp2 = { x2 - x1 ,y2 - y1,0.f };
	
	_fY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	//D3DXVec3Normalize(&vTemp, &vTemp);
	D3DXVec3Normalize(&vTemp2, &vTemp2);
	_fAngle = acosf(D3DXVec3Dot(&vTemp, &vTemp2));

	if (y1 > y2)
	{
		_fAngle *= -1.f;
	}

	return true;
}

const float CLineMgr::Collision_Monster_Line(float & _fX, float * pY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	D3DXVECTOR3 vTemp = { 1.f,0.f,0.f };
	D3DXVECTOR3 vTemp2 = { x2 - x1 ,y2 - y1,0.f };
	
	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	//D3DXVec3Normalize(&vTemp, &vTemp);
	D3DXVec3Normalize(&vTemp2, &vTemp2);
	float Temp = acosf(D3DXVec3Dot(&vTemp, &vTemp2));

	if (y1 > y2)
	{
		Temp *= -1.f;
	}

	return Temp;
}

void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

void CLineMgr::Create_Line(const float& _fLX, const float& _fLY, const float& _fRX, const float& _fRY)
{
	m_LineList.push_back(new CLine(LINEPOINT(_fLX, _fLY), LINEPOINT(_fRX, _fRY)));
}
