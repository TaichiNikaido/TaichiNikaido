//=============================================================================
//
// 警告 [warning.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Mode/mode_game.h"
#include "Base/text.h"
#include "warning.h"
#include "Player/player.h"
#include "Enemy/enemy_dragon.h"
#include "Bullet/bullet_fireball.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/warning.png")
#define SIZE (D3DXVECTOR3(920.0f,270.0f,0.0f))
#define RED_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define YELLOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define MINIMUM_COLOR_CHANGE_TIME (0)
#define MINIMUM_COLOR_CHANGE_COUNT (0)
#define INIT_POSITION (D3DXVECTOR3(DragonPosition.x, PlayerPosition.y, 0.0f))
#define COLOR_CHANGE_TIME (10)
#define COLOR_CHANGE_COUNT (2)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CWarning::CWarning()
{
	m_nColorChangeTime = MINIMUM_COLOR_CHANGE_TIME;					//色を変更する時間
	m_nColorChangeCount = MINIMUM_COLOR_CHANGE_COUNT;				//色を変更するカウント
}

//=============================================================================
// デストラクタ
//=============================================================================
CWarning::~CWarning()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CWarning::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE,						// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWarning::TextureUnload(void)
{
	//もしテクスチャがNULLじゃない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CWarning * CWarning::Create(void)
{
	//警告のポインタ
	CWarning * pWarning = NULL;
	//もし警告のポインタがNULLの場合
	if (pWarning == NULL)
	{
		//警告のメモリ確保
		pWarning = new CWarning;
		//もし警告のポインタがNULLじゃない場合
		if (pWarning != NULL)
		{
			//初期化処理関数呼び出し
			pWarning->Init();
		}
	}
	//警告のポインタを返す
	return pWarning;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CWarning::Init()
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//プレイヤーの位置を取得
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//ドラゴンを取得
	CEnemyDragon * pDragon = CGameMode::GetDragon();
	//ドラゴンの位置を取得
	D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
	//2Dシーン初期化処理関数呼び出し
	CScene2d::Init();
	//位置の初期設定
	SetPosition(INIT_POSITION);
	//サイズの初期設定
	SetSize(SIZE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CWarning::Uninit()
{
	//2Dシーン終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CWarning::Update()
{
	//2Dシーン更新処理関数呼び出し
	CScene2d::Update();
	//位置設定処理関数呼び出し
	Position();
	//色変更処理関数呼び出し
	ColorChange();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CWarning::Draw()
{
	//2Dシーン描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// 位置決定処理関数
//=============================================================================
void CWarning::Position(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//ドラゴンを取得
	CBulletFireball * pBulletFireBall = CGameMode::GetBulletFireBall();
	//プレイヤーの位置を取得
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//火球の位置を取得
	D3DXVECTOR3 FireBallPosition = pBulletFireBall->GetPosition();
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//X座標をドラゴンのX座標に合わせる
	Position.x = FireBallPosition.x;
	//Y座標をプレイヤーのY座標に合わせる
	Position.y = PlayerPosition.y;
	//位置を設定する
	SetPosition(Position);
}

//=============================================================================
// 色変更処理関数
//=============================================================================
void CWarning::ColorChange(void)
{
	//もし色変更時間になったら
	if (m_nColorChangeTime % COLOR_CHANGE_TIME == REMAINDER)
	{
		//色をカウントに合わせて変更する
		if (m_nColorChangeCount % COLOR_CHANGE_COUNT == REMAINDER)
		{
			//色を設定する
			SetColor(YELLOW_COLOR);
		}
		else
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				//色を設定する
				SetColor(RED_COLOR);
			}
		}
		//色を変更するカウントを加算する
		m_nColorChangeCount++;
	}
	//色を変更する時間を加算する
	m_nColorChangeTime++;
}
