//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "title.h"
#include "result.h"
#include "pause.h"
#include "dragon.h"
#include "wormhole.h"

LPDIRECT3DTEXTURE9 CPause::m_apTexture[TYPE_MAX] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CPause::CPause()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSizeX = 0;
	m_nSizeY = 0;
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
//デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CPause::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		NULL,								     // ファイルの名前
		&m_apTexture[TYPE_BG]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FLAME,								// ファイルの名前
		&m_apTexture[TYPE_FLAME]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BACK_TO_THE_GAME,								// ファイルの名前
		&m_apTexture[TYPE_BACK_TO_THE_GAME]);		// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESTART,								// ファイルの名前
		&m_apTexture[TYPE_RESTART]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BACK_TO_THE_TITLE,								// ファイルの名前
		&m_apTexture[TYPE_BACK_TO_THE_TITLE]);		// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CPause::Unload(void)
{
	// テクスチャの破棄
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//生成関数
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, int sizeX, int sizeY)
{
	CPause * pPause;
	//メモリ確保
	pPause = new CPause;
	//初期化
	pPause->Init(pos, sizeX, sizeY);
	return pPause;
}

//=============================================================================
//初期化関数
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, int sizeX, int sizeY)
{
	//初期化
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_pos = pos;
	m_nSizeX = sizeX;
	m_nSizeY = sizeY;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * TYPE_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//背景
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//フレーム
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//ゲームに戻るボタン
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//最初からボタン
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//タイトルに戻るボタン
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//pVtx += 4;

	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//終了関数
//=============================================================================
void CPause::Uninit(void)
{
	//終了
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//更新関数
//=============================================================================
void CPause::Update(void)
{
	//サウンド
	CSound * pSound = CManager::GetSound();
	if (CManager::GetbPause() == true)
	{
		//ジョイパッド
		CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
		LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
		DIJOYSTATE js;
		if (lpDIDevice != NULL)
		{
			lpDIDevice->Poll();
			lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
		}

		if (lpDIDevice != NULL &&js.lY == -1000)//上
		{
			m_IsTrigger.Up.nCount++;
		}
		if (lpDIDevice != NULL &&js.lY == 1000)//下
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

		if (lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(JS_A))//決定
		{
			////ショット音の再生
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			switch (m_nButtonPos)
			{
			case 2://ゲーム戻るボタン
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			case 3://最初からボタン
				CDragon::SetSpawn(false);
				CDragon::SetDeath(false);
				CWormhole::SetSpawn(false);
				CManager::StartFade(CManager::MODE_GAME);
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			case 4://タイトルにもどる
				pSound->StopSound();
				CDragon::SetSpawn(false);
				CDragon::SetDeath(false);
				CWormhole::SetSpawn(false);
				CManager::StartFade(CManager::MODE_TITLE);
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			default:
				break;
			}
		}

		for (int nCnt = 2; nCnt <= 4; nCnt++)
		{
			m_aButtonAlpha[nCnt] = 100;
		}
		switch (m_nButtonPos)
		{
		case 2://ゲーム戻るボタン
			m_aButtonAlpha[TYPE_BACK_TO_THE_GAME] = 255;
			break;
		case 3://最初からボタン
			m_aButtonAlpha[TYPE_RESTART] = 255;
			break;
		case 4://タイトルにもどる
			m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE] = 255;
			break;
		default:
			break;
		}

		//頂点情報を設定
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//背景
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//フレーム
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//ゲームに戻るボタン
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//最初からボタン
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//タイトルに戻るボタン
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();

		////キーボードのアップデート(これがないとTriggerが正常に機能しない)
		//pInputKeyboard->UpdateInput();
		//ジョイスティックのアップデート(これがないとTriggerが正常に機能しない)
		pInputJoystick->UpdateInput();
	}
}

//=============================================================================
//描画関数
//=============================================================================
void CPause::Draw(void)
{
	////描画
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//// 頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	//{
	//	// テクスチャの設定
	//	pDevice->SetTexture(0, m_apTexture[nCount]);
	//	// ポリゴンの描画
	//	pDevice->DrawPrimitive(
	//		D3DPT_TRIANGLESTRIP,
	//		(NUM_VERTEX * nCount),
	//		NUM_POLYGON);
	//}
}