//=============================================================================
//
// タイトル [title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "title.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "tutorial.h"

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;;
//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(nPriority)
{
	m_pScene = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
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
CTutorial::~CTutorial()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CTutorial::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TUTORIAL,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CTutorial::Unload(void)
{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//=============================================================================
// 生成関数
//=============================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CTutorial * pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init(pos, SizeHeight, SizeWidth);
	//pBg->SetPosition(pos);
	return pTutorial;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_TUTORIAL);
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	//背景
	m_pScene= new CScene2d;
	m_pScene->Init(pos, SizeHeight, SizeWidth);

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);

	m_pScene->SetVertexPosition(m_vpos);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_pScene->SetColor(m_col);
	m_pScene->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	m_pScene->BindTexture(m_pTexture);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CTutorial::Uninit(void)
{
		if (m_pScene != NULL)
		{
			m_pScene->Uninit();
			m_pScene = NULL;
		}
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CTutorial::Update(void)
{
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (pInputKeyboard->GetKeyboardPress(DIK_RETURN) || pInputJoystick->GetJoystickTrigger(JS_A))
	{
		pSound->StopSound();
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CTutorial::Draw(void)
{
}
