//=============================================================================
//
// ワームホール処理 [wormhole.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "wormhole.h"
#include "player.h"
#include "dragon.h"
#include "enemy.h"

LPDIRECT3DTEXTURE9 CWormhole::m_pTexture[MAX_WORMHOLE_TEXTURE] = {};
bool CWormhole::m_bSpawn = false;
//=============================================================================
// コンストラクタ
//=============================================================================
CWormhole::CWormhole(int nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//頂点座標
		m_col[nCount] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//頂点カラー
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_Type = TYPE_NONE;						//タイプ
	m_fAngle = 0.0f;						//角度
	m_fLength = 0.0f;						//長さ
	m_fScale = 0.1f;						//大きさ
	m_fAddScale = 0.01f;					//大きさの加算量
	m_Texture = TEX_NONE;
	m_nCountSpawn = 0;
	m_bSpawn = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWormhole::~CWormhole()
{
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CWormhole::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_WORMHOLE,							// ファイルの名前
		&m_pTexture[TEX_HOLE]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_WORMHOLEEFFECT,						// ファイルの名前
		&m_pTexture[TEX_EFFECT]);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CWormhole::Unload(void)
{
	for (int nCount = 0; nCount < MAX_WORMHOLE_TEXTURE; nCount++)
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
CWormhole * CWormhole::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col)
{
	CWormhole * pWormhole;
	pWormhole = new CWormhole;
	pWormhole->Init(pos, SizeWidth, SizeHeight, type,texture, col);
	return pWormhole;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CWormhole::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col)
{
	CScene2d::Init(pos, SizeWidth,SizeHeight);
	
	//オブジェタイプをワームホールに
	SetObjType(CScene::OBJTYPE_WORMHOLE);

	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = col;							//頂点カラー
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 10.0f);				//向き
	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//長さ
	m_fAngle = atan2f((SizeWidth / 2), (SizeWidth / 2));														//角度
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_Type = type;			//タイプ
	m_Texture = texture;
	m_fScale = 0.1f;		//大きさ
	m_fAddScale = 0.01f;	//大きさの加算量
	m_nCountSpawn = 0;
	m_bSpawn = false;
	//頂点カラーのセット
	SetColor(m_col);

	//頂点座標の設定
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//頂点座標の設定
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//頂点座標の設定
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//頂点座標の設定
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャのセット
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//テクスチャの割り当て
	BindTexture(m_pTexture[m_Texture]);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CWormhole::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CWormhole::Update(void)
{
	CScene2d::Update();

	//位置の取得
	m_pos = GetPosition();

	// 回転
	m_rot.z -= D3DX_PI * 0.01f;

	if (m_rot.z >= D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2.0f;
	}

	if (m_bSpawn == false)
	{
		if (m_fScale <= 2.0f)
		{
			m_fScale += m_fAddScale;
		}
		else
		{
			if (m_nCountSpawn == 70)
			{
				Spawn();
			}
			m_nCountSpawn++;
		}
	}

	if (CDragon::GetSpawn() == true)
	{
			m_fScale -= m_fAddScale;
	}

	if (m_fScale <= 0.0f)
	{
		m_bSpawn = false;
		Uninit();
		return;
	}

	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_SCENE; nCountScene++)
		{
			//シーンを取得
			CScene * pScene = GetScene(nCountPriority, nCountScene);

			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJTYPE objType;
				objType = pScene->GetObjType();

				//プレイヤーの位置を取得
				D3DXVECTOR3 player_pos;
				player_pos = pScene->GetPosition();
			}
		}
	}

	//頂点座標の設定
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//頂点座標の設定
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//頂点座標の設定
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//頂点座標の設定
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//現在位置のセット
	SetPosition(m_pos);
	//テクスチャのセット
	SetTex(0.0f, 0.0f, 1.0f,1.0f);
}

//=============================================================================
// 描画関数
//=============================================================================
void CWormhole::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// スポーン関数
//=============================================================================
void CWormhole::Spawn(void)
{
	//もしテクスチャがホールだったら
	if (m_Texture == TEX_HOLE)
	{
		//もしタイプがドラゴンだった時
		if (m_Type == TYPE_DRAGON)
		{
			//ドラゴンの生成
			CDragon::Create(m_pos, DRAGON_SIZE_WIDTH, DRAGON_SIZE_HEIGHT, DRAGON_MAX_HP);
		}
		m_bSpawn = true;
		m_nCountSpawn = 0;
	}
}

void CWormhole::SetSpawn(bool bSpawn)
{
	m_bSpawn = bSpawn;
}
