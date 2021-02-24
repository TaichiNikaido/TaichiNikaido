//=============================================================================
//
// 火球の爆発 [explosion_fireball.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "explosion_dragon.h"
#include "explosion_death.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_TIMNE (0)
#define EXPLOSION_DRAGON_SIZE D3DXVECTOR3(200.0f,200.0f,200.0f)
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionDragon::CExplosionDragon()
{
	m_nTime = INITIAL_TIMNE;	//時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosionDragon::~CExplosionDragon()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CExplosionDragon * CExplosionDragon::Create(void)
{
	//ドラゴンの爆発のポインタ
	CExplosionDragon * pExplosionDragon = NULL;
	//もしドラゴンの爆発のポインタがNULLの場合
	if (pExplosionDragon == NULL)
	{
		//ドラゴンの爆発のメモリ確保
		pExplosionDragon = new CExplosionDragon;
		//もしドラゴンの爆発のポインタがNULLじゃない場合
		if (pExplosionDragon != NULL)
		{
			//初期化処理関数呼び出し
			pExplosionDragon->Init();
		}
	}
	//ドラゴンの爆発のポインタを返す
	return pExplosionDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosionDragon::Init(void)
{
	//ドラゴンの取得
	CEnemyDragon * pEnemyDragon = CGameMode::GetDragon();
	//もしドラゴンのポインタがNULLじゃない場合
	if (pEnemyDragon != NULL)
	{
		//ドラゴンの位置を取得する
		D3DXVECTOR3 DoragonPosition = pEnemyDragon->GetPosition();
		CExplosionDeath::Create(DoragonPosition, EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x + 50.0f, DoragonPosition.y + 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x + 50.0f, DoragonPosition.y - 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x - 50.0f, DoragonPosition.y + 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x - 50.0f, DoragonPosition.y - 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExplosionDragon::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExplosionDragon::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExplosionDragon::Draw(void)
{
}
