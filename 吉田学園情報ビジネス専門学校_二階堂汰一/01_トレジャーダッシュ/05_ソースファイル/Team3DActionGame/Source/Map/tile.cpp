//===============================================
//
// フィールドに敷き詰めるタイルの処理 (tile.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "tile.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Character/player.h"
#include "Mode/mode_game.h"
#include "Character/player.h"
#include "Character/enemy.h"

//========================
// 静的メンバ変数宣言
//========================
LPDIRECT3DTEXTURE9 CTile::m_apTexture[TILE_MAX] = {};


//=============================================================================
// コンストラクタ
// Author : 樋宮匠
//=============================================================================
CTile::CTile()
{
    D3DXMatrixIdentity(&m_mtxWorld);
    m_pVtxBuff = NULL;
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
    m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_type = TILE_DIRT;

    m_TexLeftX = 0.0f;
    m_TexRightX = 1.0f;
    m_TexTopY = 0.0f;
    m_TexBottomY = 1.0f;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CTile::~CTile()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTile::Init(TYPE type)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_type = type;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);

    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CTile::Uninit(void)
{
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CTile::Update(void)
{
	//プレイヤーを取得
	CPlayer *pPlayer = CGameMode::GetPlayer();
	//敵を取得する
	CEnemy * pEnemy = CGameMode::GetEnemy();
	//プレイヤーの位置を所得する
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	bool bJump = pPlayer->GetIsJump();
	// タイルの上なら
	if (playerPos.x >= m_pos.x - TILE_SIZE / 2 &&
		playerPos.x <= m_pos.x + TILE_SIZE / 2 &&
		playerPos.z >= m_pos.z - TILE_SIZE / 2 &&
		playerPos.z <= m_pos.z + TILE_SIZE / 2)
	{
		switch (m_type)
		{
		case TILE_MUD:
		case TILE_DIA_MUD:
			if (!bJump)
			{
				if (pPlayer != NULL)
				{
					pPlayer->SetbSlow(true);
				}
			}
			break;
		case TILE_NEEDLE:
			// 穴に落ちる
			break;
		case TILE_CHECK_POINT:
			// チェックポイント更新
			//もしプレイヤーがNULLの場合
			if (pPlayer != NULL)
			{
				//プレイヤーのコンティニューする位置を保存する
				pPlayer->SetbContinuePositionSave(true);
			}
			//もし敵がNULLの場合
			if (pEnemy != NULL)
			{
				//敵のコンティニューする位置を保存する
				pEnemy->SetbContinuePositionSave(true);
			}
			break;
		case TILE_GOAL:
			//リザルトに移動
			CManager::StartFade(CManager::MODE_RESULT);
			// ゴール（やったー）
			break;
		default:
			if (pPlayer != NULL)
			{
				pPlayer->SetbSlow(false);
				pPlayer->SetbContinuePositionSave(false);
			}
			if (pEnemy != NULL)
			{
				pEnemy->SetbContinuePositionSave(false);
			}
			break;
		}
	}

	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-TILE_SIZE / 2, 0.0f, TILE_SIZE / 2);
	pVtx[1].pos = D3DXVECTOR3(TILE_SIZE / 2, 0.0f, TILE_SIZE / 2);
	pVtx[2].pos = D3DXVECTOR3(-TILE_SIZE / 2, 0.0f, -TILE_SIZE / 2);
	pVtx[3].pos = D3DXVECTOR3(TILE_SIZE / 2, 0.0f, -TILE_SIZE / 2);

	pVtx[0].tex = D3DXVECTOR2(m_TexLeftX, m_TexTopY);
	pVtx[1].tex = D3DXVECTOR2(m_TexRightX, m_TexTopY);
	pVtx[2].tex = D3DXVECTOR2(m_TexLeftX, m_TexBottomY);
	pVtx[3].tex = D3DXVECTOR2(m_TexRightX, m_TexBottomY);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		if (m_type != TILE_NEEDLE)
		{
			pVtx[nCount].col = m_col;
		}
		else
		{
			pVtx[nCount].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		}
	}

	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CTile::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライトをオフにする

    D3DXMatrixIdentity(&m_mtxWorld);

    D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    pDevice->SetFVF(FVF_VERTEX_3D);

    pDevice->SetTexture(0, m_apTexture[m_type]);

    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

    pDevice->SetTexture(0, NULL);

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ライトをオンにする
}

//=============================================================================
// UV座標設定処理
// Author : 樋宮匠
//=============================================================================
void CTile::SetTexUV(const float leftX, const float rightX, const float topY, const float bottomY)
{
    m_TexLeftX = leftX;
    m_TexRightX = rightX;
    m_TexTopY = topY;
    m_TexBottomY = bottomY;
}

//=============================================================================
// UV座標取得用
// Author : 樋宮匠
//=============================================================================
void CTile::GetTexUV(float * leftX, float * rightX, float * topY, float * bottomY)
{
    if (leftX != NULL)
    {
        *leftX = m_TexLeftX;
    }
    if (rightX != NULL)
    {
        *rightX = m_TexRightX;
    }
    if (topY != NULL)
    {
        *topY = m_TexTopY;
    }
    if (bottomY != NULL)
    {
        *bottomY = m_TexBottomY;
    }
}

//=============================================================================
// テクスチャ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTile::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // テクスチャ
    D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_DIRT]);
    D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/grass.png", &m_apTexture[TILE_GRASS]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_TREE_DIRT]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/grass.png", &m_apTexture[TILE_TREE_GRASS]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_WOOD_DIRT]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/grass.png", &m_apTexture[TILE_WOOD_GRASS]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/mud.png", &m_apTexture[TILE_MUD]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_DIA_DIRT]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/.png", &m_apTexture[TILE_NEEDLE]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/mud.png", &m_apTexture[TILE_DIA_MUD]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_CHECK_POINT]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dirt.png", &m_apTexture[TILE_GOAL]);

    return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
// Author : 樋宮匠
//=============================================================================
void CTile::Unload(void)
{
    for (int nCount = 0; nCount < TILE_MAX; nCount++)
    {
        if (m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}
