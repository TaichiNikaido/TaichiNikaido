//=============================================================================
//
// 敵 [enemy.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_LIFE (0)	//体力の最小値
#define MINIMUM_ATTACK (0)	//攻撃力の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
	m_Move = INITIAL_D3DXVECTOR3;							//移動量
	m_CollisionSize = INITIAL_D3DXVECTOR3;					//衝突判定用サイズ
	m_nLife = MINIMUM_LIFE;									//体力
	m_nAttack = MINIMUM_ATTACK;								//攻撃力
	memset(m_apScriptPass, NULL, sizeof(m_apScriptPass));	//スクリプトのパス
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//データ読み込み関数呼び出し
	DataLoad();
	//キャラクターの初期化処理関数呼び出し
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemy::Uninit(void)
{
	//キャラクターの終了処理関数呼び出し
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemy::Update(void)
{
	//キャラクターの更新処理関数呼び出し
	CCharacter::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemy::Draw(void)
{
	//キャラクターの描画処理関数呼び出し
	CCharacter::Draw();
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CEnemy::Hit(void)
{
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CEnemy::SubLife(void)
{
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CEnemy::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;				//位置
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;					//サイズ
	D3DXVECTOR3 CollisionSize = INITIAL_D3DXVECTOR3;		//衝突判定用サイズ
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;				//回転
	D3DXVECTOR3 Move = INITIAL_D3DXVECTOR3;					//移動量
	int nLife = 0;											//体力
	int nAttack = 0;										//攻撃力
	char aReadText[MAX_TEXT];								//読み込んだテキスト
	char aCurrentText[MAX_TEXT];							//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];						//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルの読み込み
		pFile = fopen(m_apScriptPass[0], "r");
		//ファイルを開くことができたら
		if (pFile != NULL)
		{
			//SCRIPTの文字を見つける
			while (strcmp(aCurrentText, "SCRIPT") != 0)
			{
				//読み込んだテキストを格納する
				fgets(aReadText, sizeof(aReadText), pFile);
				//読み込んだテキストを現在のテキストに格納
				sscanf(aReadText, "%s", &aCurrentText);
			}
			//現在のテキストがSCRIPTだったら
			if (strcmp(aCurrentText, "SCRIPT") == 0)
			{
				//END_SCRIPTの文字が見つかるまで読む
				while (strcmp(aCurrentText, "END_SCRIPT") != 0)
				{
					//読み込んだテキストを格納する
					fgets(aReadText, sizeof(aReadText), pFile);
					//読み込んだテキストを現在のテキストに格納
					sscanf(aReadText, "%s", &aCurrentText);
					//現在のテキストがPARAMETER_SETだったら
					if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
					{
						//END_PARAMETER_SETの文字が見つかるまで読む
						while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
						{
							//読み込んだテキストを格納する
							fgets(aReadText, sizeof(aReadText), pFile);
							//読み込んだテキストを現在のテキストに格納
							sscanf(aReadText, "%s", &aCurrentText);
							//現在のテキストがPositionだったら
							if (strcmp(aCurrentText, "Position") == 0)
							{
								//位置情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
								//位置を設定する
								SetPosition(Position);
							}
							//現在のテキストがSizeだったら
							if (strcmp(aCurrentText, "Size") == 0)
							{
								//サイズ情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
								//サイズを設定する
								SetSize(Size);
							}
							//現在のテキストがCollisionSizeだったら
							if (strcmp(aCurrentText, "CollisionSize") == 0)
							{
								//衝突判定用サイズ情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
								//衝突判定用サイズの設定
								SetCollisionSize(CollisionSize);
							}
							//現在のテキストがRotationだったら
							if (strcmp(aCurrentText, "Rotation") == 0)
							{
								//回転情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
								//回転を設定する
								SetRotation(Rotation);
							}
							//現在のテキストがMoveだったら
							if (strcmp(aCurrentText, "Move") == 0)
							{
								//移動量の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Move.x, &Move.y, &Move.z);
								//移動量の読み込み
								SetMove(Move);
							}
							//現在のテキストがLifeだったら
							if (strcmp(aCurrentText, "Life") == 0)
							{
								//体力情報の読み込み
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nLife);
								//体力の設定
								SetLife(nLife);
							}
							//現在のテキストがAttackだったら
							if (strcmp(aCurrentText, "Attack") == 0)
							{
								//攻撃力情報の読み込み
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nAttack);
								//攻撃力の設定
								SetAttack(nAttack);
							}
						}
					}
				}
			}
			//ファイルを閉じる
			fclose(pFile);
		}
	}
}
