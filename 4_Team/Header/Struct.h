#pragma once

typedef	struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;

}INFO;

typedef	struct tagInfo_Mat
{
	D3DXMATRIX matScale;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;
}MATINFO;
