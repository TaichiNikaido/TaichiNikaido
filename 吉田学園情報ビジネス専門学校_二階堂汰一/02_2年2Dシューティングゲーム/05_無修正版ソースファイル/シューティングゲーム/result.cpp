//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 二階堂汰一
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "result.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include <stdio.h>
#include <stdlib.h>

LPDIRECT3DTEXTURE9 CResult::m_apTexture[MAX_RESULT_TEXTURE] = {};
CResult::PLAYER_DATA CResult::m_PlayerData = {0,0,0,0,0};
//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	memset(m_col, 0, sizeof(m_col));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CResult::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESULT1,								// ファイルの名前
		&m_apTexture[0]);								// 読み込むメモリー

														// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESULT1,								// ファイルの名前
		&m_apTexture[1]);								// 読み込むメモリー

														// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESULT1,								// ファイルの名前
		&m_apTexture[2]);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CResult::Unload(void)
{
	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CResult * pResult;
	pResult = new CResult;
	pResult->Init(pos, SizeHeight, SizeWidth);
	return pResult;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_RESULT);

	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;

	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeHeight, SizeWidth);
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255,255,255,255);
		}
		m_apScene[nCount]->SetColor(m_col);
	}
	TextLoad();
}

//=============================================================================
// 終了関数
//=============================================================================
void CResult::Uninit(void)
{
	//for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	//{
	//	if (m_apScene[nCount] != NULL)
	//	{
	//		m_apScene[nCount]->Uninit();
	//		m_apScene[nCount] = NULL;
	//	}
	//}
	CScene::Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CResult::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	//m_fMove += 0.001f;
	//m_fFastMove += 0.01f;
	//m_fSlowMove += 0.001f;

	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
	{
		m_apScene[nCount]->Update();
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f,1.0f);
	}
	m_apScene[0]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//m_apScene[1]->SetTex(m_fTextureX, m_fTextureY - m_fFastMove, 1.0f);
	//m_apScene[2]->SetTex(m_fTextureX, m_fTextureY - m_fSlowMove, 1.0f);

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//もしENTERかAボタンを押したとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		pSound->StopSound();
		//ランキングに移動
		CManager::StartFade(CManager::MODE_RANKING);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CResult::Draw(void)
{
}

void CResult::TextLoad(void)
{
	FILE *pFile;
	int nNumPlayer = 0;

	pFile = fopen("data/TEXT/PlayerData.txt", "r"); //ファイルの読み込み

	if (pFile != NULL)
	{
		//fscanf(pFile, "%d", &nNumPlayer); //プレイヤーの人数

			fscanf(pFile, "%s", &m_PlayerData.aName);//名前入力
			fscanf(pFile, "%d", &m_PlayerData.nDeath);	//死んだ回数
			fscanf(pFile, "%d", &m_PlayerData.nContinue);//コンティニューした回数
			fscanf(pFile, "%d",& m_PlayerData.nBomb);//使用したボムの個数
			fscanf(pFile, "%d",& m_PlayerData.nScore);

		fclose(pFile); //ファイルを閉じる
	}
}
