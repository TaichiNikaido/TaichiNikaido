//=============================================================================
//
// ゲームクリアロゴ [gameclear_logo.cpp]
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
#include "gameclear_logo.h"
#include "player.h"
#include "enemy.h"
#include "bullet_fireball.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/gameclear_logo.png")
#define SIZE (D3DXVECTOR3(1000.0f,300.0f,0.0f))
#define INIT_COUNT (0)
#define INIT_TIME (0)
#define CLEAR_TIMNE (200)
#define SHOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define HIDE_COLOR (D3DXCOLOR(0.0f,1.0f,1.0f,0.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameClearLogo::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameClearLogo::CGameClearLogo(int nPriority)
{
	m_nCount = INIT_COUNT;	//カウント
	m_nTime = INIT_TIME;	//時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameClearLogo::~CGameClearLogo()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGameClearLogo::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE,									// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CGameClearLogo::TextureUnload(void)
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
CGameClearLogo * CGameClearLogo::Create(D3DXVECTOR3 Position)
{
	//ゲームクリアロゴのポインタ
	CGameClearLogo * pWarning = NULL;
	//もしゲームクリアロゴのポインタがNULLの場合
	if (pWarning == NULL)
	{
		//ゲームクリアロゴのメモリ確保
		pWarning = new CGameClearLogo;
		//もしゲームクリアロゴのポインタがNULLじゃない場合
		if (pWarning != NULL)
		{
			//位置を指定する
			pWarning->SetPosition(Position);
			//初期化処理関数呼び出し
			pWarning->Init();
		}
	}
	//ゲームクリアロゴのポインタを返す
	return pWarning;
}

//=============================================================================
// 初期処理関数
//=============================================================================
HRESULT CGameClearLogo::Init()
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーン初期化処理関数呼び出し
	CScene2d::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//色の初期設定
	SetColor(SHOW_COLOR);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameClearLogo::Uninit()
{
	//2Dシーン終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameClearLogo::Update()
{
	//2Dシーン更新処理関数呼び出し
	CScene2d::Update();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//カウントを加算する
	m_nCount++;
	//時間を進める
	m_nTime++;
	//指定した間隔ごとに
	if (m_nCount % 20 == 0)
	{
		SetColor(SHOW_COLOR);
	}
	else if (m_nCount % 41 == 0)
	{
		SetColor(HIDE_COLOR);
	}
	if (m_nTime == CLEAR_TIMNE)
	{
		//もしプレイヤーのポインタがNULLじゃない場合
		if (pPlayer != NULL)
		{
			//プレイヤーの勝利処理関数呼び出し
			pPlayer->Clear();
		}
	}
	//弾～敵のプライオリティ分回す
	for (int nCountPriority = PRIORITY_BULLET; nCountPriority <= PRIORITY_ENEMY; nCountPriority++)
	{
		//シーンの総数分回す
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//シーンの取得
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//もしシーンがNULLじゃない場合
			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJTYPE ObjType = pScene->GetObjType();
				//もしオブジェクトタイプが敵だったら
				if (ObjType == OBJTYPE_ENEMY)
				{
					//敵のポインタ取得
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//もし敵のポインタがNULLじゃない場合
					if (pEnemy != NULL)
					{
						//敵の終了処理関数呼び出し
						pEnemy->Uninit();
					}
				}
				//もしオブジェクトタイプが火球だったら
				if (ObjType == OBJTYPE_FIRE_BALL)
				{
					//火球のポインタ取得
					CBulletFireball * pBulletFireball = dynamic_cast<CBulletFireball*> (pScene);
					//火球のポインタがNULLじゃない場合
					if (pBulletFireball != NULL)
					{
						//火球の終了処理関数呼び出し
						pBulletFireball->Uninit();
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameClearLogo::Draw()
{
	//2Dシーン描画処理関数呼び出し
	CScene2d::Draw();
}
