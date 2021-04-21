//=============================================================================
//
// パーティクル [particle.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_tool.h"
#include "renderer.h"
#include "particle.h"
#include "tool.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/particle.jpg")	//テクスチャのパス
#define STANDARD_SCALE (1.0f)						//等倍
#define DEATH_LIBNE (0)								//死亡ライン

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle::CParticle()
{
	m_Move = INITIAL_D3DXVECTOR3;	//移動量
	m_nLife = 0;					//体力
	m_fAngle = D3DXToRadian(0.0f);	//角度
	m_bLife = false;				//体力を使用するか
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CParticle::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_PASS,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CParticle::TextureUnload(void)
{
	// テクスチャの破棄
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
CParticle * CParticle::Create(void)
{
	//パーティクルのポインタ
	CParticle * pParticle = NULL;
	//もしパーティクルのポインタをNULLだった場合
	if (pParticle == NULL)
	{
		//パーティクルのメモリ確保
		pParticle = new CParticle;
		//ツールの取得
		CTool * pTool = CToolMode::GetTool();
		if (pTool != NULL)
		{
			//位置を取得する
			D3DXVECTOR3 Position = pTool->GetPosition();
			//回転を取得する
			D3DXVECTOR3 Rotation = pTool->GetRotation();
			//サイズを取得する
			D3DXVECTOR3 Size = pTool->GetSize();
			//移動量を取得する
			pParticle->m_Move = pTool->GetMove();
			//色を取得する
			D3DXCOLOR Color = pTool->GetColor();
			//拡縮を取得する
			float fScale = pTool->GetScale();
			//角度を取得する
			pParticle->m_fAngle = D3DXToRadian(pTool->GetAngle());
			//ライフの使用状態を取得する
			pParticle->m_bLife = pTool->GetbLife();
			//もしパーティクルのポインタをNULLじゃない場合
			if (pParticle != NULL)
			{
				//位置を設定する
				pParticle->SetPosition(Position);
				//回転を設定する
				pParticle->SetRotation(Rotation);
				//サイズを設定する
				pParticle->SetSize(Size);
				//色を設定する
				pParticle->SetColor(Color);
				//拡縮の使用状態がtrueだったら
				if (pTool->GetbScale() == true)
				{
					//拡縮を設定する
					pParticle->SetScale(fScale);
				}
				else
				{
					//拡縮を等倍で設定する
					pParticle->SetScale(STANDARD_SCALE);
				}
				//パーティクルの初期化関数呼び出し
				pParticle->Init();
			}
		}
	}
	//パーティクルのポインタを返す
	return pParticle;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CParticle::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ビルボードの初期化処理関数呼び出し
	CBillboard::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//ツールの取得
	CTool * pTool = CToolMode::GetTool();
	//もしツールのポインタがNULLじゃない場合
	if (pTool != NULL)
	{
		//体力を取得する
		m_nLife = pTool->GetLife();
		float fAngle = float(rand() % (int)pTool->GetAngle());
		m_fAngle = fAngle;
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CParticle::Uninit(void)
{
	//ビルボードの終了処理関数呼び出し
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CParticle::Update(void)
{
	//ビルボードの更新処理関数呼び出し
	CBillboard::Update();
	//ツールの取得
	CTool * pTool = CToolMode::GetTool();
	//もしツールのポインタがNULLじゃない場合
	if (pTool != NULL)
	{
		//回転を取得する
		D3DXVECTOR3 Rotation = pTool->GetRotation();
		//サイズを取得する
		D3DXVECTOR3 Size = pTool->GetSize();
		//移動量を取得する
		m_Move = pTool->GetMove();
		//色を取得する
		D3DXCOLOR Color = pTool->GetColor();
		//拡縮を取得する
		float fScale = pTool->GetScale();
		//角度を取得する
		//m_fAngle = D3DXToRadian(pTool->GetAngle());
		//体力の使用状態を取得する
		m_bLife = pTool->GetbLife();
		//回転を設定する
		SetRotation(Rotation);
		//サイズを設定する
		SetSize(Size);
		//色を設定する
		SetColor(Color);
		//もし拡縮の使用状態がtrueだったら
		if (pTool->GetbScale() == true)
		{
			//拡縮を設定する
			SetScale(fScale);
		}
		else
		{
			//拡縮を等倍に設定する
			SetScale(STANDARD_SCALE);
		}
	}
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//X座標の位置更新
	Position.x += m_Move.x * cosf(D3DXToRadian(m_fAngle));
	//Y座標の位置更新
	Position.y += m_Move.y * sinf(D3DXToRadian(m_fAngle));
	//Z座標の位置更新
	Position.z += m_Move.z * sinf(D3DXToRadian(m_fAngle));
	//位置を設定する
	SetPosition(Position);
	//もし体力の使用状態がtrueの場合
	if (m_bLife == true)
	{
		//体力を減算する
		m_nLife--;
		//もし体力が0になったら
		if (m_nLife <= DEATH_LIBNE)
		{
			//終了処理関数呼び出し
			Uninit();
			return;
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CParticle::Draw(void)
{
	//ビルボードの描画処理関数呼び出し
	CBillboard::Draw();
}
