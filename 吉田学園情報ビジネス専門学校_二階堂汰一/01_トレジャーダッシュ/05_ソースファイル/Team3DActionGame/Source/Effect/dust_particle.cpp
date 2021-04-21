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
#include "dust_particle.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define SUB_COLOR_VALUE (0.02f)											// 色減算値
#define ADD_SCALE_VALUE	(0.4f)											// 拡大率加算
#define MIN_COLOR_VALUE	(0.0f)											// 色の最小値
#define RANDOM_ANGLE	(180)											// 角度ランダム
#define RANDOM_POS		(200)											// 位置ランダム
#define MUT_2			(2)												// 2倍
#define DEVEIDE			(2)												// 割る２
#define MAX_PARTICLE	(10)											// パーティクルの最大数
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z))				// 位置
#define SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))					// サイズ
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// 向き
#define COLOR			(D3DXCOLOR(1.0f,0.8f,0.5f,1.0f))				// 色

// 移動
#define MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*2.0f, sinf(D3DXToRadian(fAngle))*3.0f,0.0f))
//******************************************************************************
//	コンストラクタ
//******************************************************************************
CDust_Particle::CDust_Particle(int nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
	m_fAddScale = INIT_FLOAT;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	デストラクタ
//******************************************************************************
CDust_Particle::~CDust_Particle()
{
}
//******************************************************************************
//	生成関数
//******************************************************************************
CDust_Particle * CDust_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// CParticle_Fireクラスのポインタ
	CDust_Particle *pDust_Particlee;

	// メモリ確保
	pDust_Particlee = new CDust_Particle;

	// 情報設定
	pDust_Particlee->SetParticle(pos, size, ROT, col, CParticle::TEX_TYPE_2);

	// 移動量代入
	pDust_Particlee->m_move = move;

	// 初期化
	pDust_Particlee->Init();

	// ポインタを返す
	return pDust_Particlee;
}
//******************************************************************************
//	初期化
//******************************************************************************
HRESULT CDust_Particle::Init(void)
{
	// 初期化
	CParticle::Init();

	// 拡大率加算
	m_fAddScale = ADD_SCALE_VALUE;

	// カラー減算値
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;
}
//******************************************************************************
//	終了関数
//******************************************************************************
void CDust_Particle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
//	更新関数
//******************************************************************************
void CDust_Particle::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 拡大率
	float fScale = GetScale();

	// 拡大率加算
	fScale += m_fAddScale;

	// 色設定
	SetScale(fScale);

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
void CDust_Particle::Draw(void)
{
	// 描画
	CParticle::Draw();
}
//******************************************************************************
//	エフェクト生成
//******************************************************************************
void CDust_Particle::SandDust_Create(D3DXVECTOR3 pos)
{
	for (int nCnt = INIT_INT; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 角度を360ランダム
		float fAngle = float(rand() % RANDOM_ANGLE);

		// 生成
		Create(POS, SIZE, COLOR, MOVE);
	}
}