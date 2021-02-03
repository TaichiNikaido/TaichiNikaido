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
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/UI/word.png")
#define COUNT_TRIGGER 4
#define ALPHABET_COL D3DCOLOR_RGBA(0, 170, 255, 255)//文字カラー

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
//テクスチャの初期化
LPDIRECT3DTEXTURE9 CName::m_apTexture[MAX_NAME_TEXTURE] = {};
//文字格納用変数の初期化
CName::Letter CName::m_aLetter[MAX_ROW][MAX_COLUMN] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CName::CName()
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	memset(m_aName, NULL, sizeof(m_aName));
	m_bOK = false;
	m_nNameCount = 0;
	m_IsTrigger.Down.bTrigger = false;//推されてるかどうか
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//推されてるかどうか
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_nColumn = 0;
	m_nRow = 0;
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
HRESULT CName::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE,
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CName::TextureUnload(void)
{
	for (int nCount = 0; nCount < MAX_NAME_TEXTURE; nCount++)
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
	CName * pNamePad;
	pNamePad = new CName;
	if (pNamePad != NULL)
	{
		pNamePad->Init(pos, SizeHeight, SizeWidth);
	}
	return pNamePad;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CName::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	m_pos = pos;

	memset(m_aName, NULL, sizeof(m_aName));	//名前格納用変数の初期化
	m_bOK = false;
	m_nNameCount = 0;						//名前の文字数カウンタ

	//------------------------------------------
	//キーボードの設定
	//------------------------------------------
	int nAlphabetCount = 0;//アルファベット順番

	for (int nCountRow = 0; nCountRow < MAX_ROW; nCountRow++)
	{
		for (int nCountCol = 0; nCountCol < MAX_COLUMN; nCountCol++)
		{
			m_apScene[nAlphabetCount] = new CScene2d;
			//頂点座標のセット
			m_apScene[nAlphabetCount]->SetPosition(D3DXVECTOR3(pos.x + (WORD_BUTTON_INTERVEL * TEXT_SCALE * nCountCol), pos.y + (WORD_BUTTON_INTERVEL *TEXT_SCALE * nCountRow), 0.0f));
			//色のセット
			m_apScene[nAlphabetCount]->SetColor(ALPHABET_COL);
			//サイズのセット
			m_apScene[nAlphabetCount]->SetSize(D3DXVECTOR3(TEXT_SIZE, TEXT_SIZE, 0.0f));
			//テクスチャのUV座標の設定
			D3DXVECTOR2 aTexture[NUM_VERTEX];
			aTexture[0] = D3DXVECTOR2(nAlphabetCount * 0.037037f, 0.0f);
			aTexture[1] = D3DXVECTOR2(nAlphabetCount * 0.037037f + 0.037037f, 0.0f);
			aTexture[2] = D3DXVECTOR2(nAlphabetCount * 0.037037f, 1.0f);
			aTexture[3] = D3DXVECTOR2(nAlphabetCount * 0.037037f + 0.037037f, 1.0f);
			//テクスチャ座標のセット
			m_apScene[nAlphabetCount]->SetTexture(aTexture);

			m_apScene[nAlphabetCount]->Init();
			//テクスチャの割り当て
			m_apScene[nAlphabetCount]->BindTexture(m_apTexture[0]);

			nAlphabetCount++;
		}
	}

	//------------------------------------------
	//入力文字表示部分設定
	//------------------------------------------
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = new CScene2d;
		//頂点座標のセット
		m_apSceneText[nCount]->SetPosition(D3DXVECTOR3(300.0f + (WORD_BUTTON_INTERVEL * TEXT_SCALE * nCount), pos.y + -200.0f, 0.0f));
		//色のセット
		m_apSceneText[nCount]->SetColor(ALPHABET_COL);
		//サイズのセット
		m_apSceneText[nCount]->SetSize(D3DXVECTOR3(TEXT_SIZE, TEXT_SIZE, 0.0f));
		//テクスチャのUV座標の設定
		D3DXVECTOR2 aTexture[NUM_VERTEX];
		aTexture[0] = D3DXVECTOR2(0.00001f, 0.0f);
		aTexture[1] = D3DXVECTOR2(0.0f, 0.0f);
		aTexture[2] = D3DXVECTOR2(0.00001f, 1.0f);
		aTexture[3] = D3DXVECTOR2(0.0f, 1.0f);
		//テクスチャ座標のセット
		m_apSceneText[nCount]->SetTexture(aTexture);

		m_apSceneText[nCount]->Init();
		//テクスチャの割り当て
		m_apSceneText[nCount]->BindTexture(m_apTexture[0]);
	}

	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight;	//高さ

	//文字配列に文字格納
	int nCountColumn = 0;//列
	int nCountRow = 0;//行
	int nLetterIndex = 0;//配列順番
	for (char cAlphabet = 'A'; cAlphabet <= 'Z'; cAlphabet++, nCountColumn++)//アルファベット順に格納
	{
		m_aLetter[nCountRow][nCountColumn].aLetter = cAlphabet;//文字格納
		m_aLetter[nCountRow][nCountColumn].LetterIndex = nLetterIndex;//順番格納
		if (nCountColumn == 9)
		{
			nCountColumn = 0;
			nCountRow++;
		}
		nLetterIndex++;
	}
	m_aLetter[MAX_ROW - 1][MAX_COLUMN - 1].LetterIndex = MAX_WORD - 1;//終了コマンド

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CName::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Uninit();
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount]->Uninit();
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CName::Update(void)
{
	//サウンド
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();

	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
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

	//もし下矢印が押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN) || m_IsTrigger.Down.bTrigger == true)
	{
		//現在行を一行下げる
		m_nRow++;

		//行を超えると上に戻る	
		if (m_nRow >= MAX_ROW)
		{
			m_nRow = 0;
		}
		//移動音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Down.bTrigger = false;
	}

	//もし上矢印が押されら
	if (pKeyboard->GetKeyboardTrigger(DIK_UP) || m_IsTrigger.Up.bTrigger == true)
	{
		//現在行を一行あげる
		m_nRow--;

		//行を超えると下に戻る	
		if (m_nRow < 0)
		{
			m_nRow = MAX_ROW - 1;
		}

		//移動音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Up.bTrigger = false;
	}

	//もし右矢印が押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT) || m_IsTrigger.Right.bTrigger == true)
	{
		//現在列を右にずらす
		m_nColumn++;

		//列を超えると左端に戻る
		if (m_nColumn >= MAX_COLUMN)
		{
			m_nColumn = 0;
		}

		//移動音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Right.bTrigger = false;
	}

	//もし左矢印が押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT) || m_IsTrigger.Left.bTrigger == true)
	{
		//現在列を左にずらす
		m_nColumn--;

		//列を超えると右端に戻る
		if (m_nColumn < 0)
		{
			m_nColumn = MAX_COLUMN - 1;
		}

		//移動音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Left.bTrigger = false;
	}

	//もしENTERかAボタンを押したとき
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//決定音の再生
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);

		//入力終了だったら
		if (m_aLetter[m_nRow][m_nColumn].LetterIndex == MAX_WORD - 1)
		{
			//名前を決定状態にする
			m_bOK = true;
		}
		else
		{
			//もし名前の記録が可能状態だったら
			if (m_nNameCount < 8)
			{
				//入力された文字を名前格納用変数に一文字ずつ格納する
				m_aName[m_nNameCount] = m_aLetter[m_nRow][m_nColumn].aLetter;

				//テクスチャのUV座標の設定
				D3DXVECTOR2 aTexture[NUM_VERTEX];
				aTexture[0] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f, 0.0f);
				aTexture[1] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f + 0.037037f, 0.0f);
				aTexture[2] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f, 1.0f);
				aTexture[3] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f + 0.037037f, 1.0f);
				//テクスチャ座標のセット
				m_apSceneText[m_nNameCount]->SetTexture(aTexture);

				//名前の文字数を加算する
				if (m_nNameCount < 8)
				{
					m_nNameCount++;
				}
			}
		}
	}

	//もし名前に文字が入っているとき
	if (m_aName != NULL)
	{
		//もしBACKSPACEかBボタンを押したとき
		if (pKeyboard->GetKeyboardTrigger(DIK_BACK) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_B))
		{
			//ショット音の再生
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			//入力された文字を名前格納用変数から一文字ずつ破棄する
			m_aName[m_nNameCount] = NULL;

			if (m_nNameCount < 8)
			{
				//テクスチャのUV座標の設定
				D3DXVECTOR2 aTexture[NUM_VERTEX];
				aTexture[0] = D3DXVECTOR2(0.00001f, 0.0f);
				aTexture[1] = D3DXVECTOR2(0.0f, 0.0f);
				aTexture[2] = D3DXVECTOR2(0.00001f, 1.0f);
				aTexture[3] = D3DXVECTOR2(0.0f, 1.0f);
				//テクスチャ座標のセット(何も入ってない状態)
				m_apSceneText[m_nNameCount]->SetTexture(aTexture);
			}

			//名前の文字数を減算する
			if (m_nNameCount > 0)
			{
				m_nNameCount--;
			}
		}
	}

	//もし名前の決定したとき
	if (m_bOK == true)
	{
		//名前格納用変数がNULLじゃないとき
		if (m_aName[0] != NULL)
		{
			//名前をプレイヤーに渡す
			for (int nCount = 0; nCount < m_nNameCount; nCount++)
			{
				//CManager::SetPlayerName(nCount, m_aName[nCount]);
			}
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

			for (int nCount = 0; nCount < m_nNameCount; nCount++)
			{
				//プレイヤーに名前をセット
				//CManager::SetPlayerName(nCount, m_aName[nCount]);
			}
		}

		//ゲームに移動
		CManager::StartFade(CManager::MODE_GAME);
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Update();
		//色のセット
		m_apScene[nCount]->SetColor(D3DCOLOR_RGBA(0, 170, 255, 255));

	}

	//色のセット
	m_apScene[m_aLetter[m_nRow][m_nColumn].LetterIndex]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}


//=============================================================================
// 描画関数
//=============================================================================
void CName::Draw(void)
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Draw();
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount]->Draw();
	}
}