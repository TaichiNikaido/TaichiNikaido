//=============================================================================
//
// 名前の入力処理[name.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "name.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "name.h"
#include "sound.h"

#define COUNT_TRIGGER 20

//テクスチャの初期化
LPDIRECT3DTEXTURE9 CName::m_apTexture[MAX_NAME_TEXTURE] = {};
//文字格納用変数の初期化
CName::Letter CName::m_aLetter[MAX_COLUMN][COLUMN_MAXNUMBER] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CName::CName(int nPriority) : CScene(nPriority)
{
	
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apSceneBG[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	memset(m_aName, NULL, sizeof(m_aName));
	m_bName = false;
	m_bCanselName = false;
	m_bColumnDown = false;
	m_bColumnUp = false;
	m_bLetterRight = false;
	m_bLetterLeft = false;
	m_bOK = false;
	m_nColumnCount = 0;
	m_nLetterCount = 0;
	m_nNameCount = 0;
	m_IsTrigger.Down.bTrigger = false;//推されてるかどうか
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//推されてるかどうか
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_TriggerCount = 0;//押し中のカウンタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CName::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAME,								// ファイルの名前
		&m_apTexture[0]);								// 読み込むメモリー
														// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAMEBG,								// ファイルの名前
		&m_apTexture[1]);								// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CName::Unload(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
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
CName * CName::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CName * pName;
	pName = new CName;
	pName->Init(pos, SizeHeight, SizeWidth);
	return pName;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CName::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_NAME);

	m_pos = pos;

	//背景
	m_apSceneBG[0] = new CScene2d;
	m_apSceneBG[0]->Init(pos, TEXT_SIZE, TEXT_SIZE);
	m_apSceneBG[0]->BindTexture(m_apTexture[1]);

	// 頂点座標を設定
	m_vPos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (-SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[2] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (-SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[3] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2), 0.0f);
	//頂点座標のセット
	m_apSceneBG[0]->SetVertexPosition(m_vPos);

	//テクスチャ座標のセット
	m_apSceneBG[0]->SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);
	//テクスチャ座標のセット
	m_apSceneBG[0]->SetColor(m_col);
	for (int nCount = 0; nCount < 26; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, TEXT_SIZE, TEXT_SIZE);
		m_apScene[nCount]->BindTexture(m_apTexture[0]);

		if (nCount < 10)
		{
			// 頂点座標を設定
			m_vPos[0] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + (TEXT_SIZE / 2), 0.0f);
		}
		if (nCount >= 10 && nCount < 19)
		{
			// 頂点座標を設定
			m_vPos[0] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (-TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (-TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
		}
		if (nCount >= 19 && nCount < 26)
		{
			// 頂点座標を設定
			m_vPos[0] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (-TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (-TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
		}
		//頂点座標のセット
		m_apScene[nCount]->SetVertexPosition(m_vPos);

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(200, 100, 0, 255);
		}
		//色のセット
		m_apScene[nCount]->SetColor (m_col);

		//テクスチャ座標のセット
		m_apScene[nCount]->SetTex(
			0.03846f * nCount,
			0.0f,
			0.03846f * nCount + 0.03846f,
			1.0f);
	}

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = new CScene2d;
		m_apSceneText[nCount]->Init(pos, TEXT_SIZE, TEXT_SIZE);
		m_apSceneText[nCount]->BindTexture(m_apTexture[0]);

		// 頂点座標を設定
		m_vPos[0] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + -150.0f + (-TEXT_SIZE / 2), 0.0f);
		m_vPos[1] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + -150.0f + (-TEXT_SIZE / 2), 0.0f);
		m_vPos[2] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + -150.0f + (TEXT_SIZE / 2), 0.0f);
		m_vPos[3] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + -150.0f + (TEXT_SIZE / 2), 0.0f);

		//頂点座標のセット
		m_apSceneText[nCount]->SetVertexPosition(m_vPos);

		//色のセット
		m_apSceneText[nCount]->SetColor(m_col);

		//テクスチャ座標のセット(何も入ってない状態)
		m_apSceneText[nCount]->SetTex(
			0.0f,
			0.00001f,
			1.0f,
			0.0f);
	}

	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight;	//高さ

	//文字の2次元配列に文字を格納
	m_aLetter[0][0].aLetter = 'Q';
	m_aLetter[0][1].aLetter = 'W';
	m_aLetter[0][2].aLetter = 'E';
	m_aLetter[0][3].aLetter = 'R';
	m_aLetter[0][4].aLetter = 'T';
	m_aLetter[0][5].aLetter = 'Y';
	m_aLetter[0][6].aLetter = 'U';
	m_aLetter[0][7].aLetter = 'I';
	m_aLetter[0][8].aLetter = 'O';
	m_aLetter[0][9].aLetter = 'P';
	m_aLetter[1][0].aLetter = 'A';
	m_aLetter[1][1].aLetter = 'S';
	m_aLetter[1][2].aLetter = 'D';
	m_aLetter[1][3].aLetter = 'F';
	m_aLetter[1][4].aLetter = 'G';
	m_aLetter[1][5].aLetter = 'H';
	m_aLetter[1][6].aLetter = 'J';
	m_aLetter[1][7].aLetter = 'K';
	m_aLetter[1][8].aLetter = 'L';
	m_aLetter[2][0].aLetter = 'Z';
	m_aLetter[2][1].aLetter = 'X';
	m_aLetter[2][2].aLetter = 'C';
	m_aLetter[2][3].aLetter = 'V';
	m_aLetter[2][4].aLetter = 'B';
	m_aLetter[2][5].aLetter = 'N';
	m_aLetter[2][6].aLetter = 'M';

	//文字の2次元配列に文字を格納
	m_aLetter[0][0].LetterIndex = 0;
	m_aLetter[0][1].LetterIndex = 1;
	m_aLetter[0][2].LetterIndex = 2;
	m_aLetter[0][3].LetterIndex = 3;
	m_aLetter[0][4].LetterIndex = 4;
	m_aLetter[0][5].LetterIndex = 5;
	m_aLetter[0][6].LetterIndex = 6;
	m_aLetter[0][7].LetterIndex = 7;
	m_aLetter[0][8].LetterIndex = 8;
	m_aLetter[0][9].LetterIndex = 9;
	m_aLetter[1][0].LetterIndex = 10;
	m_aLetter[1][1].LetterIndex = 11;
	m_aLetter[1][2].LetterIndex = 12;
	m_aLetter[1][3].LetterIndex = 13;
	m_aLetter[1][4].LetterIndex = 14;
	m_aLetter[1][5].LetterIndex = 15;
	m_aLetter[1][6].LetterIndex = 16;
	m_aLetter[1][7].LetterIndex = 17;
	m_aLetter[1][8].LetterIndex = 18;
	m_aLetter[2][0].LetterIndex = 19;
	m_aLetter[2][1].LetterIndex = 20;
	m_aLetter[2][2].LetterIndex = 21;
	m_aLetter[2][3].LetterIndex = 22;
	m_aLetter[2][4].LetterIndex = 23;
	m_aLetter[2][5].LetterIndex = 24;
	m_aLetter[2][6].LetterIndex = 25;

	memset(m_aName, 0, sizeof(m_aName));	//名前格納用変数の初期化
	m_bName = false;						//名前の記録状態
	m_bCanselName = false;
	m_bColumnDown = false;					//下矢印判定
	m_bColumnUp = false;					//上矢印判定
	m_bLetterRight = false;					//右矢印判定
	m_bLetterLeft = false;					//左矢印
	m_bOK = false;
	m_nColumnCount = 0;						//行数カウンタ
	m_nLetterCount = 0;						//文字数カウンタ
	m_nNameCount = 0;						//名前の文字数カウンタ

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//プレイヤーに名前をセット
		CPlayer::SetPlayerName(nCount, NULL);
	}

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CName::Uninit(void)
{
	for (int nCount = 0; nCount < 26; nCount++)
	{
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Uninit();
			m_apScene[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		if (m_apSceneText[nCount] != NULL)
		{
			m_apSceneText[nCount]->Uninit();
			m_apSceneText[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < 1; nCount++)
	{
		if (m_apSceneBG[nCount] != NULL)
		{
			m_apSceneBG[nCount]->Uninit();
			m_apSceneBG[nCount] = NULL;
		}
	}
	CName::Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CName::Update(void)
{
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();

	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);

	}

	if (lpDIDevice != NULL &&js.lX == -1000)//左
	{
		m_IsTrigger.Left.nCount++;
	}
	if (lpDIDevice != NULL &&js.lX == 1000)//右
	{
		m_IsTrigger.Right.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == -1000)//上
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000)//下
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Left.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Left.bTrigger = true;
		m_IsTrigger.Left.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Right.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Right.bTrigger = true;
		m_IsTrigger.Right.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER - 5;
	}
	//もし下矢印が押されらたら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) || m_IsTrigger.Down.bTrigger == true)
	{
		//下矢印を真にする
		m_bColumnDown = true;

		//もし下矢印が真のとき
		if (m_bColumnDown == true)
		{
			//現在の行数が3行目より下だったら
			if (m_nColumnCount < 2)
			{
				//行の加算
				m_nColumnCount++;
				//下矢印を偽にする
				m_bColumnDown = false;
			}
			//もし2行目の時
			if (m_nColumnCount == 1)
			{
				//もし選択中の文字が8番目より上だったら
				if (m_nLetterCount > 8)
				{
					//選択中の文字を8番目にする
					m_nLetterCount = 8;
				}
			}
			//もし3行目の時
			if (m_nColumnCount == 2)
			{
				//もし選択中の文字が6番目より上だったら
				if (m_nLetterCount > 6)
				{
					//選択中の文字を6番目にする
					m_nLetterCount = 6;
				}
			}
		}
		m_IsTrigger.Down.bTrigger = false;
	}

	//もし上矢印が押されら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) || m_IsTrigger.Up.bTrigger == true)
	{
		//上矢印を真にする
		m_bColumnUp = true;

		//もし上矢印が真だったら
		if (m_bColumnUp == true)
		{
			//もし現在の行数が1行目より上だったら
			if (m_nColumnCount > 0)
			{
				//行の減算
				m_nColumnCount--;
				//上矢印を偽にする
				m_bColumnUp = false;
			}
		}
		m_IsTrigger.Up.bTrigger = false;
	}

	//もし右矢印が押されたら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) || m_IsTrigger.Right.bTrigger == true)
	{
		//右矢印を真にする
		m_bLetterRight = true;

		////もし右矢印が真だったら
		if (m_bLetterRight == true)
		{
			//もし現在の行数が1行目だったら
			if (m_nColumnCount == 0)
			{
				//もし現在の文字の位置が9番目より下だったら
				if (m_nLetterCount < 9)
				{
					//文字の位置の加算
					m_nLetterCount++;
					//右矢印を偽にする
					m_bLetterRight = false;
				}
			}
			//もし現在の行数が2行目だったら
			if (m_nColumnCount == 1)
			{
				//もし現在の文字の位置が8番目より下だったら
				if (m_nLetterCount < 8)
				{
					//文字の位置の加算
					m_nLetterCount++;
					//右矢印を偽にする
					m_bLetterRight = false;
				}
			}
			//もし現在の行数が3行目だったら
			if (m_nColumnCount == 2)
			{
				//もし現在の文字の位置が7番目より下だったら
				if (m_nLetterCount < 6)
				{
					//文字の位置の加算
					m_nLetterCount++;
					//右矢印を偽にする
					m_bLetterRight = false;
				}
			}
		}
		m_IsTrigger.Right.bTrigger = false;
	}

	//もし左矢印が押されたら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) || m_IsTrigger.Left.bTrigger == true)
	{
		//左矢印を真にする
		m_bLetterLeft = true;

		//もし左矢印が真のとき
		if (m_bLetterLeft == true)
		{
			//もし現在の行数が1行目だったら
			if (m_nColumnCount == 0)
			{
				//もし現在の行数が1行目より上だったら
				/*	if (m_nColumnCount > 0)
				{*/
				//もし現在の文字の位置が0より上だったら
				if (m_nLetterCount > 0)
				{
					//文字の位置を減算
					m_nLetterCount--;
					//左矢印を偽にする
					m_bLetterLeft = false;
				}
				//}
			}
			//もし現在の行数が2行目だったら
			if (m_nColumnCount == 1)
			{
				//もし現在の行数が1行目より上だったら
				if (m_nColumnCount > 0)
				{
					//もし現在の文字の位置が0より上だったら
					if (m_nLetterCount > 0)
					{
						//文字の位置を減算
						m_nLetterCount--;
						//左矢印を偽にする
						m_bLetterLeft = false;
					}
				}
			}
			//もし現在の行数が3行目だったら
			if (m_nColumnCount == 2)
			{
				//もし現在の行数が1行目より上だったら
				if (m_nColumnCount > 0)
				{
					//もし現在の文字の位置が0より上だったら
					if (m_nLetterCount > 0)
					{
						//文字の位置を減算
						m_nLetterCount--;
						//左矢印を偽にする
						m_bLetterLeft = false;
					}
				}
			}
		}
		m_IsTrigger.Left.bTrigger = false;
	}

	if (m_bOK == false)
	{
		//もしENTERかAボタンを押したとき
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
		{
			//名前の記録を可能状態にする
			m_bName = true;

			//もし名前の記録が可能状態だったら
			if (m_bName == true && m_nNameCount < 8)
			{
				//入力された文字を名前格納用変数に一文字ずつ格納する
				m_aName[m_nNameCount] = m_aLetter[m_nColumnCount][m_nLetterCount].aLetter;

				//名前の文字数を加算する
				if (m_nNameCount < 8)
				{
					//テクスチャ座標のセット
					m_apSceneText[m_nNameCount]->SetTex(
						0.03846f * m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex,
						0.0f,
						0.03846f * m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex + 0.03846f,
						1.0f);
					m_nNameCount++;
				}

				//名前の記録を不可能状態にする
				m_bName = false;
			}
		}
	}

	//もし名前に文字が入っているとき
	if (m_aName[0] != NULL)
	{
		//もしBACKSPACEかBボタンを押したとき
		if (pInputKeyboard->GetKeyboardTrigger(DIK_BACK) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
		{
			//名前の取り消しを可能状態にする
			m_bCanselName = true;
			//もし名前の取り消しが可能状態だったら
			if (m_bCanselName == true)
			{
				//入力された文字を名前格納用変数から一文字ずつ破棄する
				m_aName[m_nNameCount] = NULL;

				if (m_nNameCount < 8)
				{
					//テクスチャ座標のセット(何も入ってない状態)
					m_apSceneText[m_nNameCount]->SetTex(
						0.00001f,
						0.0f,
						0.0f,
						0.0f);
				}

				//名前の文字数を減算する
				if (m_nNameCount > 0)
				{
					m_nNameCount--;
				}

			}
			//名前の取り消しを不可能状態にする
			m_bName = false;
		}
	}

	if (m_bOK == false)
	{
		//もしSPACEKEYかJOYSTICKのSTARTが押されたとき
		if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11))
		{
			//名前格納用変数がNULLじゃないとき
			if (m_aName[0] != NULL)
			{
				//名前を決定状態にする
				m_bOK = true;
			}
			else
			{
				m_aName[0] = 'U';
				m_aName[1] = 'N';
				m_aName[2] = 'K';
				m_aName[3] = 'N';
				m_aName[4] = 'O';
				m_aName[5] = 'W';
				m_aName[6] = 'N';
				m_aName[7] = NULL;
				m_nNameCount = 7;
				//名前を決定状態にする
				m_bOK = true;

				for (int nCount = 0; nCount < m_nNameCount; nCount++)
				{
					//プレイヤーに名前をセット
  					CPlayer::SetPlayerName(nCount, m_aName[nCount]);
				}
				pSound->StopSound();
				//ゲームに移動
				CManager::StartFade(CManager::MODE_TUTORIAL);
			}
		}
	}

	//もし名前の決定したとき
	if (m_bOK == true)
	{
		//名前をプレイヤーに渡す
		for (int nCount = 0; nCount < m_nNameCount ; nCount++)
		{
			CPlayer::SetPlayerName(nCount, m_aName[nCount]);
		}
		pSound->StopSound();
		//ゲームに移動
		CManager::StartFade(CManager::MODE_TUTORIAL);
	}

	for (int nCount = 0; nCount < 26; nCount++)
	{
		m_apScene[nCount]->Update();

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 100, 0, 255);
		}
		//色のセット
		m_apScene[nCount]->SetColor(m_col);

	}

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//色のセット
	m_apScene[m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex]->SetColor(m_col);
	//キーボードのアップデート(これがないとTriggerが正常に機能しない)
	pInputKeyboard->UpdateInput();
	//ジョイスティックのアップデート(これがないとTriggerが正常に機能しない)
	pInputJoystick->UpdateInput();
}

//=============================================================================
// 描画関数
//=============================================================================
void CName::Draw(void)
{
}