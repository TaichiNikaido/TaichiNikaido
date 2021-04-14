//=============================================================================
//
// 剣 [sword.cpp]
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
#include "renderer.h"
#include "mode_game.h"
#include "weapon_sword.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Weapon/Sword.x")				//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Weapon/Sword/Data.txt")		//剣のスクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CSword::m_aModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CSword::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CSword::CSword()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSword::~CSword()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CSword::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = NULL;
	//もしパスのポインタがNULLの場合
	if (pPass == NULL)
	{
		//パスを取得
		pPass = MODEL_PASS;
	}
	//もしパスのポインタがNULLじゃない場合
	if (pPass != NULL)
	{
		//モデル読み込み
		D3DXLoadMeshFromX(pPass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aModelData.pBuffMat,
			NULL,
			&m_aModelData.nNumMat,
			&m_aModelData.pMesh);
		//もしモデルのマテリアル情報がNULLじゃない場合
		if (m_aModelData.pBuffMat != NULL)
		{
			//マテリアルのポインタを取得
			m_pMaterial = (D3DXMATERIAL *)m_aModelData.pBuffMat->GetBufferPointer();
			//モデルデータ数分回す
			for (int nCountMat = 0; nCountMat < (int)m_aModelData.nNumMat; nCountMat++)
			{
				//もしファイルネームがNULLじゃない場合
				if (m_pMaterial[nCountMat].pTextureFilename != NULL)
				{
					//テクスチャを読み込む
					D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_aModelData.pTexture[nCountMat]);
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CSword::ModelUnload(void)
{
	//もしモデルデータのワールド変換行列がNULLじゃな場合
	if (m_aModelData.mtxWorld != NULL)
	{
		//もしモデルデータのマテリアル情報がNULLじゃな場合
		if (m_aModelData.pBuffMat != NULL)
		{
			//モデルデータのマテリアル情報を破棄
			m_aModelData.pBuffMat->Release();
		}
		//もしモデルデータのメッシュ情報がNULLじゃな場合
		if (m_aModelData.pMesh != NULL)
		{
			//モデルデータのメッシュ情報を破棄
			m_aModelData.pMesh->Release();
		}
		//マテリアルの最大数分回す
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//もしモデルデータのテクスチャのポインタがNULLじゃな場合
			if (m_aModelData.pTexture[nCountTexture] != NULL)
			{
				//モデルデータのテクスチャのポインタを破棄
				m_aModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CSword * CSword::Create()
{
	//剣のポインタ
	CSword * pSword = NULL;
	//剣のポインタがNULLの場合
	if (pSword == NULL)
	{
		//剣のメモリ確保
		pSword = new CSword;
	}
	//剣のポインタがNULLではない場合
	if (pSword != NULL)
	{
		//剣の初期化処理関数呼び出し
		pSword->Init();
	}
	//剣のポインタを返す
	return pSword;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CSword::Init(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CManager::GetGameMode()->GetPlayer();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//親モデルの設定
		SetParentModel(pPlayer->GetModel(6));
	}
		//モデルデータの設定
		SetModelData(m_aModelData);
		//データロード処理関数呼び出し
		DataLoad();
		//武器の初期化処理関数呼び出し
		CWeapon::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CSword::Uninit(void)
{
	//武器の終了処理関数呼び出し
	CWeapon::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CSword::Update(void)
{
	//武器の更新処理関数呼び出し
	CWeapon::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CSword::Draw(void)
{
	//武器の描画処理関数呼び出し
	CWeapon::Draw();
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CSword::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;				//位置
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;						//サイズ
	D3DXVECTOR3 CollisionSize = INITIAL_D3DXVECTOR3;		//衝突判定用サイズ
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;				//回転
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
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
