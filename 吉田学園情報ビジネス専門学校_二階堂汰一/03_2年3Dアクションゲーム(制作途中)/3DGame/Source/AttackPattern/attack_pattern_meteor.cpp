//=============================================================================
//
// 攻撃パターン(メテオ) [attack_pattern_meteor.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "attack_pattern_meteor.h"
#include "Object/object_meteor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_METEOR_CREATE_TIME (0)		//メテオを生成する時間の最小値
#define MINIMUM_METEOR_CREATE_COUNT (0)		//メテオの生成数の最小値
#define MAX_METEOR (32)						//生成するメテオの最大数
#define METEOR_CREATE_POSITION_Y (1000.0f)	//メテオを生成する位置(Y軸)
#define METEOR_CREATE_MAX_AREA (500)		//メテオを生成する最大エリア
#define METEOR_SIZE (50.0f)					//メテオの大きさ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackPatternMeteor::CAttackPatternMeteor()
{
	m_nMeteorCreateTime = MINIMUM_METEOR_CREATE_TIME;		//メテオを生成する時間
	m_nMeteorCreateCount = MINIMUM_METEOR_CREATE_COUNT;		//メテオの生成数
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackPatternMeteor::~CAttackPatternMeteor()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CAttackPatternMeteor * CAttackPatternMeteor::Create(void)
{
	//攻撃パターン(メテオ)のポインタ
	CAttackPatternMeteor * pAttackPatternMeteor = nullptr;
	//攻撃パターン(メテオ)がnullptrの場合
	if (pAttackPatternMeteor == nullptr)
	{
		//攻撃パターン(メテオ)のメモリ確保
		pAttackPatternMeteor = new CAttackPatternMeteor;
		//攻撃パターン(メテオ)のポインタがnullptrではない場合
		if (pAttackPatternMeteor != nullptr)
		{
			//攻撃パターン(メテオ)の初期化処理関数呼び出し
			pAttackPatternMeteor->Init();
		}
	}
	//攻撃パターン(メテオ)のポインタを返す
	return pAttackPatternMeteor;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CAttackPatternMeteor::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CAttackPatternMeteor::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CAttackPatternMeteor::Update(void)
{
	if (m_nMeteorCreateTime % 60 == 0)
	{
		//もしメテオの生成するが最大値に到達していない場合
		if (m_nMeteorCreateCount <= MAX_METEOR)
		{
			//メテオを生成する
			MeteorCreate();
		}
	}
	//メテオの生成時間を加算する
	m_nMeteorCreateTime++;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CAttackPatternMeteor::Draw(void)
{
}

//=============================================================================
// メテオ生成処理関数
//=============================================================================
void CAttackPatternMeteor::MeteorCreate(void)
{
	//生成の真偽
	bool bCreate = false;
	//生成の真偽が偽の場合
	while (bCreate == false)
	{
		//メテオの生成位置
		D3DXVECTOR3 MeteorCreatePosition = INITIAL_D3DXVECTOR3;
		//メテオの生成位置のX座標をランダムで求める
		MeteorCreatePosition.x = float((rand() % METEOR_CREATE_MAX_AREA * 2) - METEOR_CREATE_MAX_AREA);
		//メテオの生成位置のZ座標をランダムで求める
		MeteorCreatePosition.z = float((rand() % METEOR_CREATE_MAX_AREA * 2) - METEOR_CREATE_MAX_AREA);
		//原点からメテオまでの距離を求める
		D3DXVECTOR3 Distance = D3DXVECTOR3(MeteorCreatePosition.x - INITIAL_D3DXVECTOR3.x, MeteorCreatePosition.y - INITIAL_D3DXVECTOR3.y, MeteorCreatePosition.z - INITIAL_D3DXVECTOR3.z);
		//ベクトルの長さを求める
		float Vector_length = sqrtf((Distance.x * Distance.x) * (Distance.z * Distance.z));
		//メテオを生成する範囲(円形)を求める
		if (powf(Distance.x, 2) + powf(Distance.z, 2)
			<= pow(((METEOR_CREATE_MAX_AREA / 2) + (METEOR_SIZE / 2)), 2))
		{
			//メテオを生成しない範囲(円形)を求める
			if (powf(Distance.x, 2) + powf(Distance.z, 2)
				>= pow(((METEOR_CREATE_MAX_AREA / 6) + (METEOR_SIZE / 2)), 2))
			{
				//メテオを生成する
				CMeteor::Create(D3DXVECTOR3(MeteorCreatePosition.x, METEOR_CREATE_POSITION_Y, MeteorCreatePosition.z));
				//生成の真偽を真にする
				bCreate = true;
				//メテオの生成数を加算する
				m_nMeteorCreateCount++;
			}
		}
	}
}