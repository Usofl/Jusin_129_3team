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

typedef	struct	tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {	}

}LINEPOINT;

typedef	struct	tagLineInfo
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {	}

}LINE;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;