//=============================================================================
//
// UIのゲージ [ui_gauge.cpp]
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
#include "scene2d.h"
#include "ui_village_icon.h"
#include "stage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/UI/VillageIcon.png")		//テクスチャのパス
#define SCRIPT_PASS ("Data/Script/UI/Village_Icon/Data.txt")	//プレイヤーデータのスクリプトのパス
#define INITIAL_PATTERN_ANIME (0)								//パターンアニメ
#define INITIAL_ANIMATION_VALUE (0.0f)							//アニメーションの初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CVillageIcon::m_pTexture = NULL;	//テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
CVillageIcon::CVillageIcon()
{
	m_nPatternAnime = INITIAL_PATTERN_ANIME;		//パターンアニメ
	m_fAnimationValue = INITIAL_ANIMATION_VALUE;	//アニメーションの値
}

//=============================================================================
// デストラクタ
//=============================================================================
CVillageIcon::~CVillageIcon()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CVillageIcon::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_PASS,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CVillageIcon::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CVillageIcon * CVillageIcon::Create(void)
{
	//村のアイコンのポインタ
	CVillageIcon * pVillageIcon = NULL;
	//村のアイコンがNULLの場合
	if (pVillageIcon == NULL)
	{
		//村のアイコンのメモリ確保
		pVillageIcon = new CVillageIcon;
	}
	//村のアイコンがNULLではない場合
	if (pVillageIcon != NULL)
	{
		//村のアイコンの初期化処理関数呼び出し
		pVillageIcon->Init();
	}
	//村のアイコンのポインタを返す
	return pVillageIcon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CVillageIcon::Init(void)
{
	//データ読み込み関数呼び出し
	DataLoad();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 1.0f);
	//2Dシーン管理初期化処理関数呼び出し
	CScene2d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CVillageIcon::Uninit(void)
{
	//2Dシーン管理終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CVillageIcon::Update(void)
{
	//ステージの取得
	CStage * pStage = CGameMode::GetStage();
	//村全体のライフを取得する
	int nVillageLife = pStage->GetLife();
	//2Dシーン管理更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CVillageIcon::Draw(void)
{
	//2Dシーン管理描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CVillageIcon::DataLoad(void)
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
							//位置の情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//位置の設定
							SetPosition(Position);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズの情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//サイズを設定する
							SetSize(Size);
						}
						//現在のテキストがROTだったら
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//回転を設定する
							SetRotation(Rotation);
						}
						//現在のテキストがANIMATION_VALUEだったら
						if (strcmp(aCurrentText, "ANIMATION_VALUE") == 0)
						{
							//アニメーションの値情報の読み込み
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAnimationValue);
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
