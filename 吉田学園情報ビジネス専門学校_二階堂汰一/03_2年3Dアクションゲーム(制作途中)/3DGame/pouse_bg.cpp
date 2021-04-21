//=============================================================================
//
// ポーズ背景 [pouse_bg.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "pouse_bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/Logo_Title.png")							//テクスチャのパス
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 - 100.0f,0.0f))	//位置
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))							//サイズ
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.05f))										//色

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPouseBG::CPouseBG()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPouseBG::~CPouseBG()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CPouseBG * CPouseBG::Create()
{
	//ポーズ背景のポインタ
	CPouseBG * pPouseBG = nullptr;
	//タイトルロゴのポインタがnullptrの場合
	if (pPouseBG == nullptr)
	{
		//ポーズ背景のメモリ確保
		pPouseBG = new CPouseBG;
		//ポーズ背景のポインタがnullptrではない場合
		if (pPouseBG != nullptr)
		{
			//ポーズ背景の位置設定
			pPouseBG->SetPosition(POSITION);
			//ポーズ背景のサイズ設定
			pPouseBG->SetSize(SIZE);
			//ポーズ背景の色設定
			pPouseBG->SetColor(COLOR);
			//ポーズ背景の初期化処理関数呼び出し
			pPouseBG->Init();
		}
	}
	//タイトルロゴのボタンのポインタを返す
	return pPouseBG;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPouseBG::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ボタンの初期化処理関数呼び出し
	CScene2d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPouseBG::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPouseBG::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPouseBG::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CScene2d::Draw();
}