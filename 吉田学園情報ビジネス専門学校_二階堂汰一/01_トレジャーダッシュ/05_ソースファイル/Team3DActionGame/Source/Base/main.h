//=============================================================================
//
// メイン [main.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define MAX_TEXT		(1024)
#define MAX_POLYGON		(256)
#define NUM_POLYGON		(2)
#define NUM_VERTEX		(4)
#define REMAINDER (0)
#define INIT_INT			(0)														// int型初期化
#define INIT_FLOAT			(0.0f)													// float型初期化
#define INIT_D3DXVECTOR3	(D3DXVECTOR3(0.0f,0.0f,0.0f))							// D3DXVECTOR3初期化
#define INIT_COLOR			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						// D3DXCOLOR初期化
#define DEFAULT_VECTOR (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define DEFAULT_SCALE (D3DXVECTOR3(1.0f,1.0f,1.0f))
#define MAX_PASS_LETTER (128)

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"ws2_32.lib")

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float		rhw;	//座標変換用紙係数
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ
}VERTEX_3D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif
#endif