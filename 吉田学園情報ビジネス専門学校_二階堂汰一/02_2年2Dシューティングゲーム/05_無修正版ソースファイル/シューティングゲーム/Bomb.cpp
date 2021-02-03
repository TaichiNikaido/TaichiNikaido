//=============================================================================
//
//	爆弾 [bomb.cpp]
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
#include "Bomb.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"

LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBomb::CBomb()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_Type = TYPE_NONE;	//タイプ
	m_nLife = 0;		//ライフ
	m_nAttack = 0;		//攻撃力
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//=============================================================================
//デストラクタ
//=============================================================================
CBomb::~CBomb()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CBomb::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BOMB,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CBomb::Unload(void)
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
CBomb * CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack)
{
	CBomb * pBomb;
	pBomb = new CBomb;
	pBomb->Init(pos, move, SizeHeight, SizeWidth,  nLife, nAttack);
	pBomb->SetPosition(pos);
	return pBomb;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack)
{
	CScene2d::Init(pos, SizeHeight,SizeWidth);
	//オブジェタイプを爆弾に
	SetObjType(CScene::OBJTYPE_BOMB);
	//位置を設定する
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = move;			//移動量
	m_Type = TYPE_NONE;		//タイプ
	m_nLife = nLife;		//ライフ
	m_nAttack = nAttack;	//攻撃力
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight;	//高さ
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの設定
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBomb::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBomb::Update(void)
{
	CScene2d::Update();
	//位置の取得
	m_pos = GetPosition();
	//位置に移動量を加算
	m_pos += m_move;
	//体力減算処理関数
	SubLife();
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//頂点座標の設定
	SetVertexPosition(m_vpos);
	//テクスチャの設定
	SetTex(0.0f,
		   0.0f, 
		   1.0f,
		   1.0f);
	//位置の設定
	SetPosition(m_pos);
}

//=============================================================================
// 描画関数
//=============================================================================
void CBomb::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CBomb::SubLife(void)
{
	//音楽の取得
	CSound * pSound = CManager::GetSound();
	//ライフの減算
	m_nLife--;
	//もしライフが0以下になったら
	if (m_nLife <= 0)
	{
		//爆発の生成
		CExplosion::Create(m_pos, BOMB_EXPLOSION_SIZE, BOMB_EXPLOSION_SIZE, CExplosion::TYPE_BOMB);
		//爆発音の生成
		pSound->PlaySound(CSound::SOUND_LABEL_BOMBEXPLOSION);
		Uninit();
		return;
	}
}
