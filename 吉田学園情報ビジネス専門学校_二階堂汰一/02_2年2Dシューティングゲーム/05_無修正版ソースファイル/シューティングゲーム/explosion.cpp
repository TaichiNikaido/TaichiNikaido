//=============================================================================
//
//	爆発処理 [explosion.cpp]
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
#include "explosion.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion()
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_nCounterAnim = 0;	//アニメカウンタ
	m_nPatternAnim = 0;	//アニメパターン
	m_fWidth = 0;		//幅
	m_fHeight = 0;		//高さ
	m_type = TYPE_NONE;	//タイプ
}

//=============================================================================
//デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CExplosion::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EXPLOSION,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CExplosion::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type)
{
	CExplosion * pExplosion;
	pExplosion = new CExplosion;
	pExplosion->SetPosition(pos);
	pExplosion->Init(pos,SizeWidth,SizeHeight,type);

	return pExplosion;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CScene2d::Init(pos,SizeWidth,SizeHeight);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_nCounterAnim = 0;		//アニメカウンタ
	m_nPatternAnim = 0;		//アニメパターン
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight; //高さ
	m_type = type;			//タイプ

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);

	//テクスチャセット
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 爆発更新関数
//=============================================================================
void CExplosion::Update(void)
{
	//更新
	CScene2d::Update();
	//位置の取得
	D3DXVECTOR3 pos = GetPosition();

	//タイプによる処理分け
	switch (m_type)
	{
	case TYPE_BULLET:
		break;
	case TYPE_BOMB:
		for (int nCountPriority = 1; nCountPriority < 5; nCountPriority++)
		{
			for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
			{
				CScene * pScene = GetScene(nCountPriority, nCountScene);
				if (pScene != NULL)
				{
					//オブジェタイプの取得
					OBJTYPE objType;
					objType = pScene->GetObjType();
					//シーンオブジェクトの位置を取得
					D3DXVECTOR3 Scene_pos;
					Scene_pos = pScene->GetPosition();

					switch (objType)
					{
					case OBJTYPE_ENEMY:
						if (pos.x + m_fWidth / 2 > Scene_pos.x - (EYE_SIZE / 2) &&
							pos.x - m_fWidth / 2 < Scene_pos.x + (EYE_SIZE / 2) &&
							pos.y + m_fHeight / 2 > Scene_pos.y - (EYE_SIZE / 2) &&
							pos.y - m_fHeight / 2 < Scene_pos.y + (EYE_SIZE / 2))
						{
							//エネミーのライフ減算
							CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
							if (pScene != NULL)
							{
								pEnemy->SubLife(100);
							}
						}
						break;
					case OBJTYPE_BULLET:
						if (pos.x + BOMB_EXPLOSION_SIZE / 2 > Scene_pos.x - (BULLET_SIZE / 2) &&
							pos.x - BOMB_EXPLOSION_SIZE / 2 < Scene_pos.x + (BULLET_SIZE / 2) &&
							pos.y + BOMB_EXPLOSION_SIZE / 2 > Scene_pos.y - (BULLET_SIZE / 2) &&
							pos.y - BOMB_EXPLOSION_SIZE / 2 < Scene_pos.y + (BULLET_SIZE / 2))
						{
							pScene->Uninit();
						}
						break;
					default:
						break;
					}
				}
			}
		}
		
	
	case TYPE_FIERBALL:
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(4, nCountScene);
			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//シーンオブジェクトの位置を取得
				D3DXVECTOR3 Scene_pos;
				Scene_pos = pScene->GetPosition();

				if (objType == OBJTYPE_PLAYER)
				{
					if (pos.x + m_fWidth / 2 > Scene_pos.x - (PLAYER_SIZE / 2) &&
						pos.x - m_fWidth / 2 < Scene_pos.x + (PLAYER_SIZE / 2) &&
						pos.y + m_fHeight / 2 > Scene_pos.y - (PLAYER_SIZE / 2) &&
						pos.y - m_fHeight / 2 < Scene_pos.y + (PLAYER_SIZE / 2))
					{
						//エネミーのライフ減算
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						if (pScene != NULL)
						{
							pPlayer->SubOwn(1);
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
	//カウントインクリメント
	m_nCounterAnim++;
	//カウントが4以上になった場合
	if (m_nCounterAnim > 4)
	{
		//カウントを0にする
		m_nCounterAnim = 0;

		//パターンのインクリメント
		m_nPatternAnim++;
		//パターンが8になった場合
		if (m_nPatternAnim > 8)
		{
			//終了
			Uninit();
			return;
		}
	}
	//テクスチャセット
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);

	//頂点座標の設定
	SetVertexPosition(m_vpos);
}


//=============================================================================
// 描画関数
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}