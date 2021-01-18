//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "item.h"
#include "own.h"
#include "ownui.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_ITEM_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_Type = TYPE_NONE;						//タイプ
	m_fWidth = 0.0f;						//幅
	m_fHeight = 0.0f;						//高さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CItem::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_OWN_ITEM,							// ファイルの名前
		&m_pTexture[TYPE_OWN]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_LEVEL_ITEM,							// ファイルの名前
		&m_pTexture[TYPE_LEVEL]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE_ITEM,							// ファイルの名前
		&m_pTexture[TYPE_SCORE]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BOMB_ITEM,							// ファイルの名前
		&m_pTexture[TYPE_BOMB]);					// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ITEM_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CItem * pItem;
	pItem = new CItem;
	pItem->Init(pos, SizeWidth, SizeHeight,type);
	return pItem;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//オブジェタイプをアイテムに
	SetObjType(CScene::OBJTYPE_ITEM);

	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;			//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = D3DXVECTOR3(0.0f, ITEM_SPEED, 0.0f);	//移動量
	m_Type = type;			//タイプ
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight; //高さ

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//頂点座標をセット
	SetVertexPosition(m_vpos);
	//テクスチャのセット
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
	//テクスチャの割り当て
	BindTexture(m_pTexture[m_Type]);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CItem::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CItem::Update(void)
{
	CScene2d::Update();

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		//シーンの取得
		CScene * pScene = GetScene(4, nCountScene);
		//スコアの取得
		CScore * pScore = CGame::GetScore();
		//プレイヤーのポインタ
		CPlayer * pPlayer;

		if (pScene != NULL)
		{
			//オブジェタイプの取得
			OBJTYPE objType;
			objType = pScene->GetObjType();

			//オブジェの位置
			D3DXVECTOR3 objPos;
			objPos = pScene->GetPosition();

			//もしオブジェタイプがプレイヤーだったら
			if (objType == OBJTYPE_PLAYER)
			{
				//もし衝突判定がtureだったら
				if (isCollision(objPos) == true)
				{
					//タイプによる処理分け
					switch (m_Type)
					{
						//もしタイプが自機だったら
					case TYPE_OWN:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//プレイヤーの自機を加算
						pPlayer->AddOwn(PLAYER_ADD_OWN);
						Uninit();
						return;
						break;
						//もしタイプがレベルだったら
					case TYPE_LEVEL:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//プレイヤーのレベルを加算
						pPlayer->AddLevel(PLAYER_ADD_LEVEL);
						Uninit();
						return;
						break;
						//もしタイプがスコアだったら
					case TYPE_SCORE:
						//プレイヤーのスコアを加算
						pScore->AddScore(ADDSCORE_ITEM);
						Uninit();
						return;
						break;
						//もしタイプがボムだったら
					case TYPE_BOMB:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//プレイヤーの爆弾を加算
						pPlayer->AddBomb(PLAYER_ADD_BOMB);
						Uninit();
						return;
						break;
					default:
						break;
					}
				}
			}
		}
	}

	//位置に移動量を加算
	m_pos += m_move;

	//もしアイテムが画面外に言ったら
	if (m_pos.y > FIELD_HEIGHT ||
		m_pos.x < 0 ||
		m_pos.x > FIELD_WIDTH)
	{
		Uninit();
		return;
	}

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//現在位置のセット
	SetPosition(m_pos);
	//テクスチャのセット
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
}

//=============================================================================
// 描画関数
//=============================================================================
void CItem::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// 衝突処理
//=============================================================================
bool CItem::isCollision(D3DXVECTOR3 pos)
{
	if (CPlayer::GetbDeath() == false)
	{
		if (m_pos.x + ITEM_SIZE / 2 > pos.x - (PLAYER_SIZE / 2) &&
			m_pos.x - ITEM_SIZE / 2 < pos.x + (PLAYER_SIZE / 2) &&
			m_pos.y + ITEM_SIZE / 2 > pos.y - (PLAYER_SIZE / 2) &&
			m_pos.y - ITEM_SIZE / 2 < pos.y + (PLAYER_SIZE / 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}