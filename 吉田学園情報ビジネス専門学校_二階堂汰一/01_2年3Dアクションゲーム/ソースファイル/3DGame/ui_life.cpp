//=============================================================================
//
// ライフのUI [ui_life.cpp]
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
#include "ui_life.h"
#include "gauge.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))		//サイズの初期値
#define INITIAL_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	//色の初期値
#define MINIMUM_LIFE (0)								//体力の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CLifeUI::CLifeUI()
{
	m_Position = INITIAL_POSITION;						//位置
	m_Size = INITIAL_SIZE;								//サイズ
	m_Color = INITIAL_COLOR;							//色
	m_nMaxLife = MINIMUM_LIFE;							//体力の最大値
	m_nLife = MINIMUM_LIFE;								//体力
	memset(m_apDataPass,NULL,sizeof(m_apDataPass));		//データスクリプトのパス
	m_pGauge = NULL;									//ゲージのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CLifeUI::~CLifeUI()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CLifeUI::Init(void)
{
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージに値の最大値を設定
		m_pGauge->SetMaxValue(m_nMaxLife);
		//ゲージに値を設定
		m_pGauge->SetValue(m_nLife);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CLifeUI::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CLifeUI::Update(void)
{
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージに値の最大値を設定
		m_pGauge->SetMaxValue(m_nMaxLife);
		//ゲージに値を設定
		m_pGauge->SetValue(m_nLife);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CLifeUI::Draw(void)
{
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CLifeUI::DataLoad(void)
{
	char aReadText[MAX_TEXT];			//読み込んだテキスト
	char aCurrentText[MAX_TEXT];		//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];	//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルの読み込み
		pFile = fopen(m_apDataPass[0], "r");
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
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//現在のテキストがCOLORだったら
						if (strcmp(aCurrentText, "COLOR") == 0)
						{
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Color.r, &m_Color.g, &m_Color.b, &m_Color.a);
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
