//******************************************************************************
// スタンエフェクト [stan_effect.cpp]
// Author : 管原 司
//******************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/billboard.h"
#include "effect.h"
#include "stan_effect.h"
#include "Character/player.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define ANGLE		(0.1f)
#define MULTIPLY	(2)
#define MAX_CREATE	(5)
#define ADD_ROT		(D3DXToRadian(5.0f))
#define MAX_ROT		(D3DXToRadian(360.0f))
#define MIN_ROT		D3DXToRadian((0.0f))
//******************************************************************************
// コンストラクタ
//******************************************************************************
CStan_Effect::CStan_Effect(int nPriority) : CEffect(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_fRadian = INIT_FLOAT;
	m_fLength = INIT_FLOAT;
	m_fAngle = INIT_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CStan_Effect::~CStan_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CStan_Effect *CStan_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CEffect::TEX_TYPE TexType, float fRadian, float fLength)
{
	// pStan_Effectクラスのポインタ
	CStan_Effect *pStan_Effect;

	// メモリ確保
	pStan_Effect = new CStan_Effect;

	// 初期化
	pStan_Effect->SetEffect(pos, size, rot, col, TexType);

	pStan_Effect->m_pos = pos;

	// 角度代入
	pStan_Effect->m_fRadian = fRadian;

	// 距離代入
	pStan_Effect->m_fLength = fLength;

	// 初期化
	pStan_Effect->Init();

	// pStan_Effectクラスのポインタを返す
	return pStan_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CStan_Effect::Init(void)
{
	// 初期化処理
	CEffect::Init();

	// 角度0.1f
	m_fAngle = ANGLE;

	// ラジアン計算
	m_fRadian = m_fRadian * D3DX_PI * MULTIPLY;

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CStan_Effect::Uninit(void)
{
	// 終了
	CEffect::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CStan_Effect::Update(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	// 更新
	CEffect::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 向き取得
	D3DXVECTOR3 rot = GetRotation();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// 向き加算
	rot.y += ADD_ROT;

	if (rot.y >= MAX_ROT)
	{
		rot.y = MIN_ROT;
	}

	// ラジアンに角度を加算
	m_fRadian += m_fAngle;

	// 座標を求める
	pos.x = m_pos.x + cosf(m_fRadian) * m_fLength;
	pos.z = m_pos.z + sinf(m_fRadian) * m_fLength;

	// カラー設定
	SetColor(col);

	// 位置座標設定
	SetPosition(pos);

	// 向き設定
	SetRotation(rot);
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//もしプレイヤーがヒット状態じゃない場合
		if (pPlayer->GetbHit() == false)
		{
			//全破棄処理関数呼び出し
			AllRelease();
		}
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CStan_Effect::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カリング処理を無効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画
	CEffect::Draw();

	// カリング処理を有効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//******************************************************************************
// 生成
//******************************************************************************
void CStan_Effect::StanEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, float fLength)
{
	// nMax回繰り返す
	for (int nCnt = INIT_INT; nCnt < MAX_CREATE; nCnt++)
	{
		// 弧度
		float fRadian = (float)nCnt / MAX_CREATE;

		// パーティクル生成
		Create(pos, size, rot, col, CEffect::TEX_TYPE_STAR, fRadian, fLength);
	}
}
//******************************************************************************
// 全破棄
//******************************************************************************
void CStan_Effect::AllRelease(void)
{
	// 終了
	Uninit();
	return;
}