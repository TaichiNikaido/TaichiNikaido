//******************************************************************************
// ダイヤのパーティクル [dia_particle.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
//	インクルードファイル
//******************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "dia_particle.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define MAX_LIFE		(40)											// ライフの最大値
#define MIN_LIFE		(0)												// ライフ最小値
#define RANDOM_ANGLE	(360)											// 角度ランダム
#define MAX_PARTICLE	(20)											// パーティクルの最大数
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z))				// 位置
#define SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))					// サイズ
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// 向き
#define COLOR			(D3DXCOLOR(0.5f,1.0f,1.0f,1.0f))				// 色
#define ADD_ROT_VALUE	(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(15.0f)))
// 移動
#define MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*4.0f, sinf(D3DXToRadian(fAngle))*4.0f,0.0f))
//******************************************************************************
//	コンストラクタ
//******************************************************************************
CDia_Particle::CDia_Particle(int nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
	m_nLife = INIT_INT;
}
//******************************************************************************
//	デストラクタ
//******************************************************************************
CDia_Particle::~CDia_Particle()
{
}
//******************************************************************************
//	生成関数
//******************************************************************************
CDia_Particle * CDia_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// CDia_Particleクラスのポインタ
	CDia_Particle *pCDia_Particle;

	// メモリ確保
	pCDia_Particle = new CDia_Particle;

	// 情報設定
	pCDia_Particle->SetParticle(pos, size, ROT, col, CParticle::TEX_TYPE_3);

	// 移動量代入
	pCDia_Particle->m_move = move;

	// 初期化
	pCDia_Particle->Init();

	// ポインタを返す
	return pCDia_Particle;
}
//******************************************************************************
//	初期化
//******************************************************************************
HRESULT CDia_Particle::Init(void)
{
	// 初期化
	CParticle::Init();

	// ライフ設定
	m_nLife = MAX_LIFE;

	return S_OK;
}
//******************************************************************************
//	終了関数
//******************************************************************************
void CDia_Particle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
//	更新関数
//******************************************************************************
void CDia_Particle::Update(void)
{
	// 更新
	CParticle::Update();

	// デクリメント
	m_nLife--;

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	// 位置更新
	pos += m_move;

	// 向き加算
	rot.z += ADD_ROT_VALUE.z;

	// 位置座標設定
	SetPosition(pos);

	// 向き設定
	SetRotation(rot);

	// αが0.0f以下の場合
	if (m_nLife <= MIN_LIFE)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
//	描画関数
//******************************************************************************
void CDia_Particle::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// カリング処理を無効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画
	CParticle::Draw();

	// カリング処理を有効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}
//******************************************************************************
//	エフェクト生成
//******************************************************************************
void CDia_Particle::DiaEffect_Create(D3DXVECTOR3 pos)
{
	for (int nCnt = INIT_INT; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 角度を360ランダム
		float fAngle = float(rand() % RANDOM_ANGLE);

		// 生成
		Create(POS, SIZE, COLOR, MOVE);
	}
}