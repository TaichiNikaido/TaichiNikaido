//=============================================================================
//
// 警告 [warning.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "text.h"
#include "warning.h"
#include "player.h"
#include "enemy_dragon.h"
#include "bullet_fireball.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/warning.png")
#define SIZE (D3DXVECTOR3(920.0f,270.0f,0.0f))
#define RED_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define YELLOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CWarning::CWarning()
{
	m_nColorChangeTime = 0;					//色を変更する時間
	m_nColorChangeCount = 0;				//色を変更するカウント
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
	CRenderer *pRenderer = CManager::GetRenderer();
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
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CWarning * CWarning::Create(void)
{
	CWarning * pWarning;
	pWarning = new CWarning;
	pWarning->Init();
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
	SetPosition(D3DXVECTOR3(DragonPosition.x, PlayerPosition.y, 0.0f));
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
	CEnemyDragon * pDragon = CGameMode::GetDragon();
	//プレイヤーの位置を取得
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//火球の位置を取得
	D3DXVECTOR3 FireBallPosition = pDragon->GetBulletFireBall()->GetPosition();
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
	if (m_nColorChangeTime % 10 == 0)
	{
		if (m_nColorChangeCount % 2 == 0)
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
