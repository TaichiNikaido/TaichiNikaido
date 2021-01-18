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

LPDIRECT3DTEXTURE9 CTitle::m_apTexture[TYPE_MAX] = {};
bool CTitle::m_bReplay = false;
//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255,100);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_bReplay = false;
	m_nButtonPos = 2;
	memset(m_aButtonAlpha, 0, sizeof(m_aButtonAlpha));
	m_IsTrigger.Down.bTrigger = false;//押されてるかどうか
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//押されてるかどうか
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CTitle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE1,								// ファイルの名前
		&m_apTexture[TYPE_BG]);								// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE2,								// ファイルの名前
		&m_apTexture[TYPE_LOGO]);								// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE3,								// ファイルの名前
		&m_apTexture[TYPE_START]);								// 読み込むメモリー
																// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE4,								// ファイルの名前
		&m_apTexture[TYPE_RPLAY]);								// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE5,								// ファイルの名前
		&m_apTexture[TYPE_EXIT]);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
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
CTitle * CTitle::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CTitle * pTitle;
	pTitle = new CTitle;
	pTitle->Init(pos, SizeHeight, SizeWidth);
	//pBg->SetPosition(pos);
	return pTitle;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_TITLE);
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	//背景
		m_apScene[TYPE_BG] = new CScene2d;
		m_apScene[TYPE_BG]->Init(pos, SizeHeight, SizeWidth);

		// 頂点座標を設定
		m_vpos[0] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);

		m_apScene[TYPE_BG]->SetVertexPosition(m_vpos);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_BG]->SetColor(m_col);
		m_apScene[TYPE_BG]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene[TYPE_BG]->BindTexture(m_apTexture[TYPE_BG]);
	//ロゴ
		m_apScene[TYPE_LOGO] = new CScene2d;
		m_apScene[TYPE_LOGO]->Init(pos, SizeHeight, SizeWidth);

		// 頂点座標を設定
		m_vpos[0] = D3DXVECTOR3(1200.0f + (-LOGO_SIZE_WIDTH / 2), 300.0f + (-LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(1200.0f + (LOGO_SIZE_WIDTH / 2), 300.0f + (-LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(1200.0f + (-LOGO_SIZE_WIDTH / 2), 300.0f + (LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(1200.0f + (LOGO_SIZE_WIDTH / 2), 300.0f + (LOGO_SIZE_HEIGHT / 2), 0.0f);

		m_apScene[TYPE_LOGO]->SetVertexPosition(m_vpos);
		m_apScene[TYPE_LOGO]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_LOGO]->SetColor(m_col);
		m_apScene[TYPE_LOGO]->BindTexture(m_apTexture[TYPE_LOGO]);

	//ボタン
	for (int nCount = TYPE_START; nCount < TYPE_MAX; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeHeight, SizeWidth);

		// 頂点座標を設定
		m_vpos[0] = D3DXVECTOR3(1400.0f + (-TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (-TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(1400.0f + (TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (-TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(1400.0f + (-TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(1400.0f + (TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (TBUTTON_SIZE_HEIGHT / 2), 0.0f);

		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}


	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Uninit();
			m_apScene[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CTitle::Update(void)
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

	if (lpDIDevice != NULL &&js.lY == -1000 || pInputKeyboard->GetKeyboardPress(DIK_W))//上
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000 || pInputKeyboard->GetKeyboardPress(DIK_S))//下
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER_PAUSE - 5;
	}

	//もし下矢印が押されらたら
	if (m_IsTrigger.Down.bTrigger == true)
	{

		m_IsTrigger.Down.bTrigger = false;
		if (m_nButtonPos < 4)
		{
			////ショット音の再生
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nButtonPos++;
		}
	}

	//もし上矢印が押されら
	if (m_IsTrigger.Up.bTrigger == true)
	{

		m_IsTrigger.Up.bTrigger = false;
		if (m_nButtonPos > 2)
		{
			////ショット音の再生
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nButtonPos--;
		}
	}

	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		////ショット音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
		switch (m_nButtonPos)
		{
		case 2://スタート
			   //名前入力に移動
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			CManager::StartFade(CManager::MODE_NAME);
			pSound->StopSound();
			m_nButtonPos = 2;
			break;
		case 3://リプレイボタン
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			pSound->StopSound();
			m_bReplay = true;
			//名前入力に移動
			CManager::StartFade(CManager::MODE_GAME);
			m_nButtonPos = 2;
			break;
		case 4://終了
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			exit(0);
			return;
			m_nButtonPos = 2;
			break;
		default:
			break;
		}
	}

	for (int nCnt = 2; nCnt < TYPE_MAX; nCnt++)
	{
		m_aButtonAlpha[nCnt] = 100;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		m_apScene[nCnt]->SetColor(m_col);
	}
	switch (m_nButtonPos)
	{
	case 2://ゲーム初め
		m_aButtonAlpha[TYPE_START] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_START]->SetColor(m_col);
		break;
	case 3://リプレイ
		m_aButtonAlpha[TYPE_RPLAY] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_RPLAY]->SetColor(m_col);
		break;
	case 4://タイトルにもどる
		m_aButtonAlpha[TYPE_EXIT] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_EXIT]->SetColor(m_col);
		break;
	default:
		break;
	}
	//m_fMove += 0.001f;
	//m_fFastMove += 0.01f;
	//m_fSlowMove += 0.001f;

	//for (int nCount = 0; nCount < MAX_TITLE_TEXTURE; nCount++)
	//{
	//	m_apScene[nCount]->Update();
	//	m_apScene[nCount]->SetVertexPosition(m_vpos);
	//	m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//}
	//m_apScene[0]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	////m_apScene[1]->SetTex(m_fTextureX, m_fTextureY - m_fFastMove, 1.0f);
	////m_apScene[2]->SetTex(m_fTextureX, m_fTextureY - m_fSlowMove, 1.0f);

	//// 頂点座標を設定
	//m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	//m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	//m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//もしENTERかAボタンを押したとき
	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	//{
	//	//名前入力に移動
	//	pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
	//	CManager::StartFade(CManager::MODE_NAME);
	//	pSound->StopSound();
	//}

	//if (pInputKeyboard->GetKeyboardTrigger(DIK_R))
	//{
	//	pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
	//	pSound->StopSound();
	//	m_bReplay = true;
	//	//名前入力に移動
	//	CManager::StartFade(CManager::MODE_GAME);
	//}
}

//=============================================================================
// 描画関数
//=============================================================================
void CTitle::Draw(void)
{
}
