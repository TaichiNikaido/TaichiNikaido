//=============================================================================
//
// フェード処理 [fade.cpp]
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
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "bullet.h"
#include "background.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "title.h"
#include "result.h"
#include "fade.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_fade = FADE_NONE;
	m_ModeNext = CManager::MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
//生成関数
//=============================================================================
CFade * CFade::Create(D3DXVECTOR3 pos, int sizeX, int sizeY, CManager::MODE mode)
{
	CFade * pFade;
	//メモリ確保
	pFade = new CFade;
	//初期化
	pFade->Init(pos, sizeX, sizeY, mode);
	return pFade;
}

//=============================================================================
//初期化関数
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, int sizeX, int sizeY, CManager::MODE mode)
{
	//初期化
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報を設定
	VERTEX_2D *pVtx;
	m_pos = pos;
	m_nSizeX = sizeX;
	m_nSizeY = sizeY;
	m_ModeNext = mode;
	m_fade = FADE_IN;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_nSizeX / 2), m_pos.y + (-m_nSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_nSizeX / 2), m_pos.y + (-m_nSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_nSizeX / 2), m_pos.y + (m_nSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_nSizeX / 2), m_pos.y + (m_nSizeY / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定 
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//終了関数
//=============================================================================
void CFade::Uninit(void)
{
	//終了
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//更新関数
//=============================================================================
void CFade::Update(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//モード
	m_ModeNext = CManager::GetMode();
	//更新
	if (m_fade != FADE_NONE)
	{
		//フェードイン
		if (m_fade == FADE_IN)
		{
			//a値を加算
			m_colorFade.a += FADE_RATE;
			//画面が黒くなったら
			if (m_colorFade.a >= 1.0f)
			{
				//タイトルに遷移
				CManager::SetMode(m_ModeNext);
				//フェード終了処理
				m_colorFade.a = 1.0f;
				m_fade = FADE_OUT;
			}
		}
		//フェードアウト
		if (m_fade == FADE_OUT)
		{
			//α値を減算
			m_colorFade.a -= FADE_RATE;
			//画面の透過
			if (m_colorFade.a <= 0.0f)
			{
				//フェード処理切り替え
				m_colorFade.a = 0.0f;
				//モード設定
				m_fade = FADE_IN;
				CManager::StopFade();
			}
		}
		//頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定 
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;
		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//描画関数
//=============================================================================
void CFade::Draw(void)
{
	//描画
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}