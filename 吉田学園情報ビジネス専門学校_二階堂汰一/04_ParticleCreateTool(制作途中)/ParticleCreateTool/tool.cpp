//=============================================================================
//
// ツールモード [mode_tool.cpp]
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
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "tool.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>
#include "particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTool::CTool()
{
	m_Position = INITIAL_D3DXVECTOR3;						//位置
	m_Rotation = INITIAL_D3DXVECTOR3;						//回転
	m_Size = INITIAL_D3DXVECTOR3;							//サイズ
	m_Move = INITIAL_D3DXVECTOR3;							//移動量
	m_Color = INITIAL_D3DXCOLOR;							//色
	m_nLife = 0;											//体力
	m_nCreateInterval = 0;									//生成間隔
	m_nCreateTime = 0;										//生成時間
	m_fScale = 0.0f;										//拡縮
	m_fAngle = D3DXToRadian(0.0f);							//角度
	memset(m_aSaveTextName,NULL,sizeof(m_aSaveTextName));	//セーブテキストの名前
	memset(m_aLoadTextName, NULL, sizeof(m_aLoadTextName));	//ロードテキストの名前
	m_bWindow = true;										//ウィンドウを使用しているか
	m_bScale = false;										//拡縮を使用するか
	m_bLife = false;										//体力を使用するか
}

//=============================================================================
// デストラクタ
//=============================================================================
CTool::~CTool()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTool::Init(void)
{
	m_nCreateInterval = 1;				//生成間隔
	m_nCreateTime = 10;					//生成時間
	m_fAngle = 360.0f;	//角度
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTool::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTool::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (m_bWindow)
	{
		ImGui::Begin("Data");
		ImGui::DragFloat3("Position", (float*)&m_Position,1.0f);
		ImGui::DragFloat3("Rotation", (float*)&m_Rotation, 1.0f);
		ImGui::DragFloat3("Size", (float*)&m_Size, 1.0f);
		ImGui::DragFloat3("Move", (float*)&m_Move, 1.0f);
		ImGui::ColorEdit4("Color", (float*)&m_Color);
		ImGui::DragInt("CreateInterval", (int*)&m_nCreateInterval,1,1,10);
		ImGui::DragFloat("Angle", (float*)&m_fAngle, 1.0f, 1.0f, 360.0f);
		ImGui::Checkbox("UseScale", (bool*)&m_bScale);
		if (m_bScale == true)
		{
			ImGui::DragFloat("ScaleValue", (float*)&m_fScale, 0.01f);
		}
		ImGui::Checkbox("UseLife", (bool*)&m_bLife);
		if (m_bLife == true)
		{
			ImGui::DragInt("Life", (int*)&m_nLife, 1, 1, 100);
		}
		ImGui::InputTextWithHint("SaveText", "Save_Text_Name", m_aSaveTextName,sizeof(m_aSaveTextName));
		if (ImGui::Button("Save"))
		{
			TextSave();
		}
		ImGui::InputTextWithHint("LoadText", "Load_Text_Name", m_aLoadTextName, sizeof(m_aLoadTextName));
		if (ImGui::Button("Load"))
		{
			TextLoad();
		}
		ImGui::End();
	}
	ImGui::EndFrame();

	if (m_nCreateTime % m_nCreateInterval == 0)
	{
		CParticle::Create();
	}
	m_nCreateTime++;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTool::Draw(void)
{
}

//=============================================================================
// テキストセーブ処理関数
//=============================================================================
void CTool::TextSave(void)
{
	//ファイルのポインタ
	FILE * pFile = NULL;
	char aSaveText[MAX_TEXT];	//書き込んだテキスト
	memset(aSaveText, NULL, sizeof(aSaveText));
	//書き込み
	sprintf(aSaveText, "%s.txt", m_aSaveTextName);
	// NULLの場合
	if (pFile == NULL)
	{
		// ファイルの書き出し
		pFile = fopen(aSaveText, "w");
		// ファイルが空じゃないか
		if (pFile != NULL)
		{
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# 『』 [%s.txt]\n", m_aSaveTextName);
			fprintf(pFile, "#  Author :\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT #この行は絶対に消さないこと!\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "#================================================\n");
			fprintf(pFile, "# パラメータの設定\n");
			fprintf(pFile, "#================================================\n");
			fprintf(pFile, "PARAMETER_SET\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "Position = %.1f %.1f %.1f\n", m_Position.x, m_Position.y, m_Position.z);
			fprintf(pFile, "Rotation = %.1f %.1f %.1f\n", m_Rotation.x, m_Rotation.y, m_Rotation.z);
			fprintf(pFile, "Size = %.1f %.1f %.1f\n", m_Size.x, m_Size.y, m_Size.z);
			fprintf(pFile, "Move = %.1f %.1f %.1f\n", m_Move.x, m_Move.y, m_Move.z);
			fprintf(pFile, "Color = %.1f %.1f %.1f %.1f\n", m_Color.r, m_Color.g, m_Color.b, m_Color.a);
			fprintf(pFile, "Life = %d\n", m_nLife);
			fprintf(pFile, "CreateInterval = %d\n", m_nCreateInterval);
			fprintf(pFile, "\n");
			fprintf(pFile, "END_PARAMETER_SET\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT #この行は絶対に消さないこと!\n");
			// ファイルを閉じる
			fclose(pFile);

		}
	}
}

//=============================================================================
// テキストロード処理関数
//=============================================================================
void CTool::TextLoad(void)
{
	//char aReadText[MAX_TEXT];			//読み込んだテキスト
	//char aCurrentText[MAX_TEXT];		//現在のテキスト
	//char aUnnecessaryText[MAX_TEXT];	//不必要なテキスト
	//memset(aReadText, NULL, sizeof(aReadText));
	//memset(aCurrentText, NULL, sizeof(aCurrentText));
	//memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	////ファイルのポインタ
	//FILE *pFile = NULL;
	////もしファイルのポインタがNULLの場合
	//if (pFile == NULL)
	//{
	//	//ファイルの読み込み
	//	pFile = fopen(m_aLoadTextName, "r");
	//}
	////ファイルを開くことができたら
	//if (pFile != NULL)
	//{
	//	//SCRIPTの文字を見つける
	//	while (strcmp(aCurrentText, "SCRIPT") != 0)
	//	{
	//		//読み込んだテキストを格納する
	//		fgets(aReadText, sizeof(aReadText), pFile);
	//		//読み込んだテキストを現在のテキストに格納
	//		sscanf(aReadText, "%s", &aCurrentText);
	//	}
	//	//現在のテキストがSCRIPTだったら
	//	if (strcmp(aCurrentText, "SCRIPT") == 0)
	//	{
	//		//END_SCRIPTの文字が見つかるまで読む
	//		while (strcmp(aCurrentText, "END_SCRIPT") != 0)
	//		{
	//			//読み込んだテキストを格納する
	//			fgets(aReadText, sizeof(aReadText), pFile);
	//			//読み込んだテキストを現在のテキストに格納
	//			sscanf(aReadText, "%s", &aCurrentText);
	//			//現在のテキストがPARAMETER_SETだったら
	//			if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
	//			{
	//				//END_PARAMETER_SETの文字が見つかるまで読む
	//				while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
	//				{
	//					//読み込んだテキストを格納する
	//					fgets(aReadText, sizeof(aReadText), pFile);
	//					//読み込んだテキストを現在のテキストに格納
	//					sscanf(aReadText, "%s", &aCurrentText);
	//					//現在のテキストがPositionだったら
	//					if (strcmp(aCurrentText, "Position") == 0)
	//					{
	//						//位置の設定
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
	//					}
	//					//現在のテキストがSizeだったら
	//					if (strcmp(aCurrentText, "Size") == 0)
	//					{
	//						//サイズの設定
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
	//					}
	//					//現在のテキストがCollisionSizeだったら
	//					if (strcmp(aCurrentText, "CollisionSize") == 0)
	//					{
	//						//サイズの設定
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
	//					}
	//					//現在のテキストがROTだったら
	//					if (strcmp(aCurrentText, "Rotation") == 0)
	//					{
	//						//回転情報の読み込み
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	//					}
	//					//現在のテキストがMoveだったら
	//					if (strcmp(aCurrentText, "Move") == 0)
	//					{
	//						//サイズの設定
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
	//					}
	//					//現在のテキストがLifeだったら
	//					if (strcmp(aCurrentText, "Life") == 0)
	//					{
	//						//体力の設定
	//						sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
	//					}
	//					//現在のテキストがWalkSpeedだったら
	//					if (strcmp(aCurrentText, "WalkSpeed") == 0)
	//					{
	//						//歩行速度の設定の設定
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fWalkSpeed);
	//					}
	//					//現在のテキストがDashSpeedだったら
	//					if (strcmp(aCurrentText, "DashSpeed") == 0)
	//					{
	//						//ダッシュ速度の設定
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fDashSpeed);
	//					}
	//					//現在のテキストがCameraDistanceだったら
	//					if (strcmp(aCurrentText, "CameraDistance") == 0)
	//					{
	//						//カメラとの距離の設定
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fCameraDistance);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	//ファイルを閉じる
	//	fclose(pFile);
	//}
}
