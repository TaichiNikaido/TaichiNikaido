//=============================================================================
//
// ゲームオーバー背景 [game_over_bg.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_over_bg.h"
#include "Button/game_over_button_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//位置
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//サイズ
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.1f))								//色
#define BUTTON_MANAGER_CREATE_MINIMUM_COUNT (0)								//ボタンマネージャーの生成カウントの最小値
#define BUTTON_MANAGER_CREATE_MAX_COUNT (1)									//ボタンマネージャーの生成カウントの最大値
#define BUTTON_MANAGER_CREATE_MINIMUM_TIME (0)								//ボタンマネージャーの生成タイミングの最小値
#define BUTTON_MANAGER_CREATE_MAX_TIME (100)								//ボタンマネージャーの生成タイミングの最大値
#define BUTTON_MANAGER_CREATE_ADD_TIME (5)									//ボタンマネージャーの生成タイミングの加算地
#define MINIMUM_ALPHA (0.0f)												//アルファ値の最小値
#define MAX_ALPHA (1.0f)													//アルファ値の最大値
#define ADD_ALPHA (0.0035f)													//アルファ値の加算量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameOverBG::CGameOverBG(int nPriority) : CScene2d(nPriority)
{
	m_nButtonCreateTime = BUTTON_MANAGER_CREATE_MINIMUM_TIME;		//ボタンマネージャーの生成タイミング
	m_nButtonCreateCount = BUTTON_MANAGER_CREATE_MINIMUM_COUNT;		//ボタンマネージャーの生成カウント
	m_fAlpha = MINIMUM_ALPHA;										//アルファ値
	m_fAddAlpha = MINIMUM_ALPHA;									//加算するアルファ値
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameOverBG::~CGameOverBG()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameOverBG * CGameOverBG::Create(void)
{
	//ゲームオーバー背景のポインタ
	CGameOverBG * pGameOverBG = nullptr;
	//ゲームオーバー背景のポインタがnullptrの場合
	if (pGameOverBG == nullptr)
	{
		//ゲームオーバー背景のメモリ確保
		pGameOverBG = new CGameOverBG;
		//ゲームオーバー背景のポインタがnullptrではない場合
		if (pGameOverBG != nullptr)
		{
			//ゲームオーバー背景の位置設定
			pGameOverBG->SetPosition(POSITION);
			//ゲームオーバー背景のサイズ設定
			pGameOverBG->SetSize(SIZE);
			//ゲームオーバー背景の色設定
			pGameOverBG->SetColor(COLOR);
			//ゲームオーバー背景の初期化処理関数呼び出し
			pGameOverBG->Init();
		}
	}
	//ゲームオーバー背景のポインタを返す
	return pGameOverBG;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameOverBG::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//アルファ値の加算量を設定
	m_fAddAlpha = ADD_ALPHA;
	//テクスチャの設定
	SetTexture(aTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameOverBG::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameOverBG::Update(void)
{
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//もしアルファチが最大値より下の場合
	if (m_fAlpha < MAX_ALPHA)
	{
		//アルファ値を加算する
		m_fAlpha += m_fAddAlpha;
		//色を設定する
		SetColor(D3DXCOLOR(COLOR.r, COLOR.g, COLOR.b, m_fAlpha));
	}
	else
	{
		//ボタンマネージャー生成タイミングを加算する
		m_nButtonCreateTime += BUTTON_MANAGER_CREATE_ADD_TIME;
		//もしボタンマネージャー生成タイミングが最大値以上かつボタン生成カウントが最小値になった場合
		if (m_nButtonCreateTime >= BUTTON_MANAGER_CREATE_MAX_TIME && m_nButtonCreateCount == BUTTON_MANAGER_CREATE_MINIMUM_COUNT)
		{
			//ボタンマネージャ生成カウントを最大値にする
			m_nButtonCreateCount = BUTTON_MANAGER_CREATE_MAX_COUNT;
			//もしボタンマネージャ生成カウントが最大値になった場合
			if (m_nButtonCreateCount == BUTTON_MANAGER_CREATE_MAX_COUNT)
			{
				//ゲームオーバーボタンマネージャーの生成
				CGameOverButtonManager::Create();
			}
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameOverBG::Draw(void)
{
	//2Dシーンの描画処理関数呼び出し
	CScene2d::Draw();
}
