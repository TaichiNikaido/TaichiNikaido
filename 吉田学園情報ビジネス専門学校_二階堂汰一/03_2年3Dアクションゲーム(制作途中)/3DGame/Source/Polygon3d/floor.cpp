//=============================================================================
//
// 床 [floor.cpp]
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
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "floor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/FloorData.txt")	//プレイヤーデータのスクリプトのパス
#define TEXTURE_PASS ("Data/Texture/ground.png")	//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFloor::m_pTexture = nullptr;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CFloor::CFloor()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFloor::~CFloor()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CFloor::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	//デバイスへのポインタ
		TEXTURE_PASS,					//ファイルの名前
		&m_pTexture);					//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CFloor::TextureUnload(void)
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CFloor * CFloor::Create()
{
	//床のポインタ
	CFloor * pFloor = nullptr;
	//床のポインタがnullptrの場合
	if (pFloor == nullptr)
	{
		//床のメモリ確保
		pFloor = new CFloor;
		//床のポインタがnullptrではない場合
		if (pFloor != nullptr)
		{
			//床の初期化処理関数呼び出し
			pFloor->Init();
		}
	}
	//床のポインタを返す
	return pFloor;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CFloor::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ポリゴン3Dの初期化処理関数呼び出し
	CPolygon3d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//データ読み込み関数呼び出し
	DataLoad();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CFloor::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFloor::Update(void)
{
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CFloor::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CFloor::DataLoad(void)
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f,0.0f,0.0f);		//位置
	D3DXVECTOR3 Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//サイズ
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	char aReadText[MAX_TEXT];								//読み込んだテキスト
	char aCurrentText[MAX_TEXT];							//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];						//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = nullptr;
	//もしファイルのポインタがnullptrの場合
	if (pFile == nullptr)
	{
		//ファイルの読み込み
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//ファイルを開くことができたら
	if (pFile != nullptr)
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
							//位置情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//位置を設定する
							SetPosition(Position);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズ情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//サイズを設定する
							SetSize(Size);
						}
						//現在のテキストがROTだったら
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//回転情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//回転を設定する
							SetRotation(D3DXVECTOR3(D3DXToRadian(Rotation.x),D3DXToRadian(Rotation.y),D3DXToRadian(Rotation.z)));
						}
					}	
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
