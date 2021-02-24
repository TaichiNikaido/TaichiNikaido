//=============================================================================
//
// ドラゴン [enemy_dragon.cpp]
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
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "model.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Enemy/Dragon/Model.txt")		//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Enemy/Dragon/Data.txt")		//スケルトンのスクリプトのパス
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//サイズの初期値
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//衝突判定用サイズの初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//回転の初期値
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//移動量の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CDragon::m_aModelData[MAX_PARTS] = {};		//モデルデータのポインタ
D3DXMATERIAL * CDragon::m_pMaterial = NULL;						//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CDragon::CDragon()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CDragon::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = NULL;
	//もしパスのポインタがNULLの場合
	if (pPass == NULL)
	{
		//パスを取得
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしパスのポインタがNULLじゃない場合
		if (pPass != NULL)
		{
			//モデル読み込み
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aModelData[nCount].pBuffMat,
				NULL,
				&m_aModelData[nCount].nNumMat,
				&m_aModelData[nCount].pMesh);
			//もしモデルのマテリアル情報がNULLじゃない場合
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//マテリアルのポインタを取得
				m_pMaterial = (D3DXMATERIAL *)m_aModelData[nCount].pBuffMat->GetBufferPointer();
				//モデルデータ数分回す
				for (int nCountMat = 0; nCountMat < (int)m_aModelData[nCount].nNumMat; nCountMat++)
				{
					//もしファイルネームがNULLじゃない場合
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//テクスチャを読み込む
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_aModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//ポインタを捨てる
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CDragon::ModelUnload(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルデータのワールド変換行列がNULLじゃな場合
		if (m_aModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLじゃな場合
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_aModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLじゃな場合
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_aModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLじゃな場合
				if (m_aModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_aModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CDragon * CDragon::Create()
{
	//ドラゴンのポインタ
	CDragon * pDragon = NULL;
	//ドラゴンのポインタがNULLの場合
	if (pDragon == NULL)
	{
		//ドラゴンのメモリ確保
		pDragon = new CDragon;
	}
	//ドラゴンのポインタがNULLではない場合
	if (pDragon != NULL)
	{
		//ドラゴンの初期化処理関数呼び出し
		pDragon->Init();
	}
	//ドラゴンのポインタを返す
	return pDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CDragon::Init(void)
{
	//モデルのパスを設定
	SetMotionPass(MODEL_PASS);
	//モデルデータの設定
	SetModelData(m_aModelData);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//データ読み込み関数呼び出し
	DataLoad();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CDragon::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CDragon::Update(void)
{
	//敵の更新処理関数呼び出し
	CEnemy::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CDragon::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CDragon::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_POSITION;				//位置
	D3DXVECTOR3 Size = INITIAL_SIZE;						//サイズ
	D3DXVECTOR3 CollisionSize = INITIAL_COLLISION_SIZE;		//衝突判定用サイズ
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;				//回転
	D3DXVECTOR3 Move = INITIAL_MOVE;						//移動量
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
		pFile = fopen(SCRIPT_PASS, "r");
	}
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
						//現在のテキストがPOSだったら
						if (strcmp(aCurrentText, "POS") == 0)
						{
							//位置情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//位置を設定する
							SetPosition(Position);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//サイズを設定する
							SetSize(Size);
						}
						//現在のテキストがCOLLISION_SIZEだったら
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//衝突判定用サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							//衝突判定用サイズの設定
							SetCollisionSize(CollisionSize);
						}
						//現在のテキストがROTだったら
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//回転の設定
							SetRotation(D3DXVECTOR3(D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.z)));
						}
						//現在のテキストがMOVEだったら
						if (strcmp(aCurrentText, "MOVE") == 0)
						{
							//移動量の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Move.x, &Move.y, &Move.z);
							//移動量の読み込み
							SetMove(Move);
						}
						//現在のテキストがLIFEだったら
						if (strcmp(aCurrentText, "LIFE") == 0)
						{
							//体力情報の読み込み
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nLife);
							//体力の設定
							SetLife(nLife);
						}
						//現在のテキストがATTACKだったら
						if (strcmp(aCurrentText, "ATTACK") == 0)
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
