//******************************************************************************
// 円形のパーティクル [circle_particle.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
//	インクルードファイル
//******************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "circle_particle.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define SUB_COLOR_VALUE (0.05f)											// 色減算値
#define MIN_COLOR_VALUE	(0.0f)											// 色の最小値
#define RANDOM_ANGLE	(180)											// 角度ランダム
#define RANDOM_POS		(100)											// 位置ランダム
#define MUT_2			(2)												// 2倍
#define DEVEIDE			(2)												// 割る２
#define MAX_PARTICLE	(10)											// パーティクルの最大数
#define POS				(D3DXVECTOR3(pos.x + fRandomPos_X,pos.y + fRandomPos_Y,pos.z))	// 位置
#define SIZE			(D3DXVECTOR3(20.0f,20.0f,0.0f))					// サイズ
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// 向き
#define COLOR			(D3DXCOLOR(1.0f,0.3f,0.0f,1.0f))				// 色

// 移動
#define MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*10.0f, sinf(D3DXToRadian(fAngle))*10.0f,10.0f))
//******************************************************************************
//	コンストラクタ
//******************************************************************************
CCircle_Particle::CCircle_Particle(int nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	デストラクタ
//******************************************************************************
CCircle_Particle::~CCircle_Particle()
{
}
//******************************************************************************
//	生成関数
//******************************************************************************
CCircle_Particle * CCircle_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// CParticle_Fireクラスのポインタ
	CCircle_Particle *pCircle_Particle;

	// メモリ確保
	pCircle_Particle = new CCircle_Particle;

	// 情報設定
	pCircle_Particle->SetParticle(pos, size, ROT, col, CParticle::TEX_TYPE_1);

	// 移動量代入
	pCircle_Particle->m_move = move;

	// 初期化
	pCircle_Particle->Init();

	// ポインタを返す
	return pCircle_Particle;
}
//******************************************************************************
//	初期化
//******************************************************************************
HRESULT CCircle_Particle::Init(void)
{
	// 初期化
	CParticle::Init();

	// カラー減算値
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;
}
//******************************************************************************
//	終了関数
//******************************************************************************
void CCircle_Particle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
//	更新関数
//******************************************************************************
void CCircle_Particle::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 色取得
	D3DXCOLOR col = GetColor();

	// カラー減算
	col.a -= m_fMinColor;

	// 色設定
	SetColor(col);

	// 位置更新
	pos += m_move;

	// 位置座標設定
	SetPosition(pos);

	// αが0.0f以下の場合
	if (col.a <= MIN_COLOR_VALUE)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
//	描画関数
//******************************************************************************
void CCircle_Particle::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
//	エフェクト生成
//******************************************************************************
void CCircle_Particle::Effect_Create(D3DXVECTOR3 pos)
{
	for (int nCnt = INIT_INT; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 角度を360ランダム
		float fAngle = float(rand() % RANDOM_ANGLE);

		// X座標ランダム
		float fRandomPos_X = float(rand() % RANDOM_POS * MUT_2 - RANDOM_POS);

		// X座標ランダム
		float fRandomPos_Y = float(rand() % RANDOM_POS * MUT_2 - RANDOM_POS);

		// 生成
		Create(POS, SIZE, COLOR, MOVE);
	}
}