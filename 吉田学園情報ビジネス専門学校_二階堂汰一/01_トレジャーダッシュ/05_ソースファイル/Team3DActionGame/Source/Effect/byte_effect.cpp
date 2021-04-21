//******************************************************************************
// スタンエフェクト [stan_effect.cpp]
// Author : 管原 司
//******************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/billboard.h"
#include "circle_particle.h"
#include "effect.h"
#include "byte_effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(0.0f,30.0f,0.0f))					// 移動量
#define COL			(D3DXCOLOR(1.0f,0.3f,0.0f,0.9f))				// 色
#define UP_POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// 位置
#define DOWN_POS	(D3DXVECTOR3(pos.x,pos.y - size.y,pos.z))		// 位置
#define UP_ROT		(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(0.0f)))		// 位置
#define DOWN_ROT	(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)))	// 位置
#define SIZE_DEVIDE	(2)												// 割る2
#define MAX_BYTE	(3)												// 最大数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CByte_Effect::CByte_Effect(int nPriority) : CEffect(nPriority)
{
	m_SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = TYPE_NONE;
	m_nCount = INIT_INT;
	bEndByte = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CByte_Effect::~CByte_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CByte_Effect *CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CEffect::TEX_TYPE TexType, TYPE type)
{
	// CByte_Effectクラスのポインタ
	CByte_Effect *pByte_Effect;

	// メモリ確保
	pByte_Effect = new CByte_Effect;

	// 代入
	pByte_Effect->m_Type = type;

	// 向き
	D3DXVECTOR3 rot;

	// UPの場合
	if (pByte_Effect->m_Type == TYPE_UP)
	{
		// 向き
		rot = UP_ROT;
	}
	// DOWNの場合
	if (pByte_Effect->m_Type == TYPE_DOWN)
	{
		// 向き
		rot = DOWN_ROT;
	}

	// 初期化
	pByte_Effect->SetEffect(pos, size, rot, col, TexType);

	// 初期化
	pByte_Effect->Init();

	// Byte_Effectクラスのポインタを返す
	return pByte_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CByte_Effect::Init(void)
{
	// 初期化処理
	CEffect::Init();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();
	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 代入
		m_SavePos.y = pos.y - size.y;
	}
	// UPの場合
	if (m_Type == TYPE_DOWN)
	{
		// 代入
		m_SavePos.y = pos.y + size.y;
	}

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CByte_Effect::Uninit(void)
{
	// 終了
	CEffect::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CByte_Effect::Update(void)
{
	// 更新
	CEffect::Update();

	// インクリメント
	m_nCount++;

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// カラー設定
	SetColor(col);

	// 向き設定
	SetRotation(rot);

	// UPの場合
	if (m_Type == TYPE_UP)
	{

		// 位置がpos.y以下の場合
		if (pos.y >= m_SavePos.y)
		{
			// 移動
			Move();
		}
		else
		{
			// trueに
			bEndByte = true;
		}
	}
	// UPの場合
	if (m_Type == TYPE_DOWN)
	{

		// 位置がpos.y以下の場合
		if (pos.y <= m_SavePos.y)
		{
			// 移動
			Move();
		}
		else
		{
			// trueに
			bEndByte = true;
		}
	}
	// trueの場合
	if (bEndByte == true)
	{
		CCircle_Particle::Effect_Create(pos);
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CByte_Effect::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カリング処理を無効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CEffect::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// カリング処理を有効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//******************************************************************************
// エフェクト生成関数
//******************************************************************************
void CByte_Effect::ByteEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = INIT_INT; nCnt < MAX_BYTE; nCnt++)
	{
		// 上生成
		Create(UP_POS, size, COL, CEffect::TEX_TYPE_BYTE, TYPE_UP);

		// 下生成
		Create(DOWN_POS, size, COL, CEffect::TEX_TYPE_BYTE, TYPE_DOWN);
	}
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CByte_Effect::Move(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動
	D3DXVECTOR3 move;

	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 移動
		move = -MOVE_VALUE;
	}
	// DOWNの場合
	if (m_Type == TYPE_DOWN)
	{
		// 移動
		move = MOVE_VALUE;
	}
	// 位置更新
	pos += move;

	// 位置設定
	SetPosition(pos);
}