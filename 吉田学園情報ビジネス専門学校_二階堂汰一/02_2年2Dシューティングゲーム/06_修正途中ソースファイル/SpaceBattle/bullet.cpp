//=============================================================================
//
// 弾 [bullet.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "bullet.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ATTACK_POINT (1)
#define MINIMUM_LIFE (0)
#define MINIMUM_ATTACK (0)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_nLife = MINIMUM_LIFE;			//体力
	m_nAttack = MINIMUM_ATTACK;		//攻撃力
	m_Move = INITIAL_MOVE;			//移動量
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBullet::Init(void)
{
	//2Dシーン管理初期化処理関数呼び出し
	CScene2d::Init();
	//攻撃力を設定する
	m_nAttack = ATTACK_POINT;
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBullet::Uninit(void)
{
	//2Dシーン管理終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBullet::Update(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//2Dシーン管理更新処理関数呼び出し
	CScene2d::Update();
	//体力減算処理関数呼び出し
	SubLife();
	//移動可能範囲処理関数呼び出し
	MovableRange();
	//位置更新
	Position += m_Move;
	//位置の設定
	SetPosition(Position);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBullet::Draw(void)
{
	//2Dシーン管理描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CBullet::SubLife(void)
{
	//体力を減算する
	m_nLife--;
}

//=============================================================================
// 移動可能範囲処理関数
//=============================================================================
void CBullet::MovableRange(void)
{
	//もし画面外に行ったら
	if (GetPosition().y < FIELD_HEIGHT_MIN ||
		GetPosition().y > FIELD_HEIGHT ||
		GetPosition().x < FIELD_WIDTH_MIN ||
		GetPosition().x > FIELD_WIDTH)
	{
		//体力を0にする
		m_nLife = MINIMUM_LIFE;
	}
}

//=============================================================================
// 体力設定関数
//=============================================================================
void CBullet::SetLife(int nLife)
{
	//体力を設定する
	m_nLife = nLife;
}

//=============================================================================
// 移動速度設定関数
//=============================================================================
void CBullet::SetMove(D3DXVECTOR3 Move)
{
	//移動速度を設定する
	m_Move = Move;
}
