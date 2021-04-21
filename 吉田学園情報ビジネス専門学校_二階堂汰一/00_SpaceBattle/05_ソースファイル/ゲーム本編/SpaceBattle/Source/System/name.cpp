//=============================================================================
//
// 名前入力 [name.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "name.h"
#include "2DPolygon/letter.h"
#include "Player/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_COLUMNS (0)			//列の最小値
#define MINIMUM_ROWS (0)			//行の最小値
#define MINIMUM_INPUT_COUNT (0)		//入力間隔の最小値
#define SUB_LETTER (-1)				//文字の減算量
#define INPUT_INTERVAL (10)			//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CName::CName()
{
	m_nColumns = MINIMUM_COLUMNS;							//列
	m_nLetter = MINIMUM_ALPHABET;							//文字番号
	m_nNameCount = MINIMUM_NAME;							//名前の文字数カウンタ
	m_nInputCount = MINIMUM_INPUT_COUNT;					//入力間隔
	memset(m_aLetter, NULL, sizeof(m_aLetter));				//文字
	memset(m_aName, NULL, sizeof(m_aName));					//名前
	memset(m_apLetter, NULL, sizeof(m_apLetter));			//文字
	memset(m_apNameLetter, NULL, sizeof(m_apNameLetter));	//名前の文字
}

//=============================================================================
// デストラクタ
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CName * CName::Create()
{
	//名前入力のポインタ
	CName * pName = nullptr;
	//名前入力のポインタがnullptrの場合
	if (pName == nullptr)
	{
		//名前入力のメモリ確保
		pName = new CName;
		//名前入力のポインタがnullptrではない場合
		if (pName != nullptr)
		{
			//名前入力の初期化処理関数呼び出し
			pName->Init();
		}
	}
	//名前入力のボタンのポインタを返す
	return pName;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CName::Init()
{
	//文字読み込み関数
	LetterLoad();
	//初期全生成処理関数呼び出し
	InitAllCreate();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CName::Uninit(void)
{
	//アルファベットの最大数分回す
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//文字の終了処理関数呼び出し
		m_apLetter[nCount]->Uninit();
	}
	//名前の最大数分回す
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//名前の文字の終了処理関数呼び出し
		m_apNameLetter[nCount]->Uninit();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CName::Update(void)
{
	//入力処理関数呼び出し
	Input();
	//アルファベットの最大数分回す
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//現在選択されていない文字の色を変更
		m_apLetter[nCount]->NotSelectColor();
	}
	//行ごとの処理
	switch (m_nColumns)
	{
	case COLUMNS_1:
		//選択時の色に変更する
		m_apLetter[m_nLetter]->SelectColor();
		break;
	case COLUMNS_2:
		//選択時の色に変更する
		m_apLetter[10 + m_nLetter]->SelectColor();
		break;
	case COLUMNS_3:
		//選択時の色に変更する
		m_apLetter[19 + m_nLetter]->SelectColor();
		break;
	default:
		break;
	}
	//アルファベットの最大数分回す
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//文字の更新処理関数呼び出し
		m_apLetter[nCount]->Update();
	}
	//名前の最大数分回す
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//名前の文字の更新処理関数呼び出し
		m_apNameLetter[nCount]->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CName::Draw(void)
{
	//アルファベットの最大数分回す
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//文字の描画処理関数呼び出し
		m_apLetter[nCount]->Draw();
	}
	//名前の最大文字数分回す
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//名前の文字の描画処理関数呼び出し
		m_apNameLetter[nCount]->Draw();
	}
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CName::Input(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//上矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//もし現在の列が最小値より上の場合
		if (m_nColumns > MINIMUM_COLUMNS)
		{
			//列を減算する
			m_nColumns--;
		}
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//現在の列が最大数より下だったら
		if (m_nColumns < COLUMNS_3)
		{
			//現在の列を加算する
			m_nColumns++;
		}
		//列ごとの処理
		switch (m_nColumns)
		{
		case COLUMNS_1:
			//もし現在の文字番号がPより上の場合
			if (m_nLetter > P)
			{
				//現在の文字番号をPにする
				m_nLetter = P;
			}
			break;
		case COLUMNS_2:
			//もし現在の文字番号がLより上の場合
			if (m_nLetter > L)
			{
				//現在の文字番号をLにする
				m_nLetter = L;
			}
			break;
		case COLUMNS_3:
			//もし現在の文字番号がMより上の場合
			if (m_nLetter > M)
			{
				//現在の文字番号をMにする
				m_nLetter = M;
			}
			break;
		default:
			break;
		}
	}
	//もし左キーが入力されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		//もし現在の文字番号が0より上の場合
		if (m_nLetter > MINIMUM_ALPHABET)
		{
			//文字番号を減算する
			m_nLetter--;
		}
	}
	//もし右キーが入力されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		//列ごとの処理
		switch (m_nColumns)
		{
		case COLUMNS_1:
			//もし現在の文字番号がPより下の場合
			if (m_nLetter < P)
			{
				//文字番号を加算する
				m_nLetter++;
			}
			break;
		case COLUMNS_2:
			//もし現在の文字番号がLより下の場合
			if (m_nLetter < L)
			{
				//文字番号を加算する
				m_nLetter++;
			}
			break;
		case COLUMNS_3:
			//もし現在の文字番号がMより下の場合
			if (m_nLetter < M)
			{
				//文字番号を加算する
				m_nLetter++;
			}
			break;
		default:
			break;
		}
	}
	//スティックが上入力された場合
	if (lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//もし現在の列が最小値より上の場合
			if (m_nColumns > MINIMUM_COLUMNS)
			{
				//列を減算する
				m_nColumns--;
			}
		}
	}
	//スティックが下入力された場合
	if (lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//現在の列が最大数より下だったら
			if (m_nColumns < COLUMNS_3)
			{
				//現在の列を加算する
				m_nColumns++;
			}
			//列ごとの処理
			switch (m_nColumns)
			{
			case COLUMNS_1:
				//もし現在の文字番号がPより上の場合
				if (m_nLetter > P)
				{
					//現在の文字番号をPにする
					m_nLetter = P;
				}
				break;
			case COLUMNS_2:
				//もし現在の文字番号がLより上の場合
				if (m_nLetter > L)
				{
					//現在の文字番号をLにする
					m_nLetter = L;
				}
				break;
			case COLUMNS_3:
				//もし現在の文字番号がMより上の場合
				if (m_nLetter > M)
				{
					//現在の文字番号をMにする
					m_nLetter = M;
				}
				break;
			default:
				break;
			}
		}
	}
	//スティックが左入力された場合
	if (lpDIDevice != NULL &&js.lX == -1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//もし現在の文字番号が0より上の場合
			if (m_nLetter > MINIMUM_ALPHABET)
			{
				//文字番号を減算する
				m_nLetter--;
			}
		}
	}
	//スティックが右入力された場合
	if (lpDIDevice != NULL &&js.lX == 1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//列ごとの処理
			switch (m_nColumns)
			{
			case COLUMNS_1:
				//もし現在の文字番号がPより下の場合
				if (m_nLetter < P)
				{
					//文字番号を加算する
					m_nLetter++;
				}
				break;
			case COLUMNS_2:
				//もし現在の文字番号がLより下の場合
				if (m_nLetter < L)
				{
					//文字番号を加算する
					m_nLetter++;
				}
				break;
			case COLUMNS_3:
				//もし現在の文字番号がMより下の場合
				if (m_nLetter < M)
				{
					//文字番号を加算する
					m_nLetter++;
				}
				break;
			default:
				break;
			}
		}
	}
	//もしENTERキー又はAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//もし名前の文字数カウンタが最大数-1より下の場合(最後の文字データをNULLにするため)
		if (m_nNameCount < MAX_NAME - 1)
		{
			int nIndex = 0;
			//名前の文字を格納する
			m_aName[m_nNameCount] = m_aLetter[m_nColumns][m_nLetter];
			//列ごとの処理
			switch (m_nColumns)
			{
			case COLUMNS_1:
				nIndex = m_nLetter;
				break;
			case COLUMNS_2:
				nIndex = 10 + m_nLetter;
				break;
			case COLUMNS_3:
				nIndex = 10 + 9 + m_nLetter;
				break;
			}
			//名前の文字を設定する
			m_apNameLetter[m_nNameCount]->SetLetter(nIndex);
			//名前の文字数カウンタを加算する
			m_nNameCount++;
		}
	}
	//もしBACK_SPACEキー又はBボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_BACK) || pJoystick->GetJoystickTrigger(JS_B))
	{
		//もし名前の文字カウンタが0より上の場合
		if (m_nNameCount > MINIMUM_NAME)
		{
			//名前の文字カウンタを減算する
			m_nNameCount--;
			//名前の文字を設定する
			m_apNameLetter[m_nNameCount]->SetLetter(SUB_LETTER);
			//現在の名前の文字を減算する
			m_aName[m_nNameCount] = NULL;
		}
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//もし名前の文字情報がある場合
		if (m_aName[0] == NULL)
		{
			m_aName[0] = 'U';
			m_aName[1] = 'N';
			m_aName[2] = 'K';
			m_aName[3] = 'N';
			m_aName[4] = 'O';
			m_aName[5] = 'W';
			m_aName[6] = 'N';
			m_aName[7] = NULL;
		}
		for (int nCount = 0; nCount < m_nNameCount; nCount++)
		{
			//プレイヤーに名前を設定する
			CPlayer::SetPlayerName(nCount, m_aName[nCount]);
		}
		//もしサウンドのポインタがNULLではない場合
		if (pSound != NULL)
		{
			//サウンドの停止
			pSound->StopSound();
		}
		//ゲームモードに遷移する
		CManager::StartFade(CManager::MODE_TUTORIAL);
	}
}

//=============================================================================
// 文字読み込み関数
//=============================================================================
void CName::LetterLoad(void)
{
	//文字を格納
	m_aLetter[0][0] = 'Q';
	m_aLetter[0][1] = 'W';
	m_aLetter[0][2] = 'E';
	m_aLetter[0][3] = 'R';
	m_aLetter[0][4] = 'T';
	m_aLetter[0][5] = 'Y';
	m_aLetter[0][6] = 'U';
	m_aLetter[0][7] = 'I';
	m_aLetter[0][8] = 'O';
	m_aLetter[0][9] = 'P';
	m_aLetter[1][0] = 'A';
	m_aLetter[1][1] = 'S';
	m_aLetter[1][2] = 'D';
	m_aLetter[1][3] = 'F';
	m_aLetter[1][4] = 'G';
	m_aLetter[1][5] = 'H';
	m_aLetter[1][6] = 'J';
	m_aLetter[1][7] = 'K';
	m_aLetter[1][8] = 'L';
	m_aLetter[2][0] = 'Z';
	m_aLetter[2][1] = 'X';
	m_aLetter[2][2] = 'C';
	m_aLetter[2][3] = 'V';
	m_aLetter[2][4] = 'B';
	m_aLetter[2][5] = 'N';
	m_aLetter[2][6] = 'M';
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CName::InitAllCreate(void)
{
	int nIndex = 0;			//行番号
	int nCreateCount = 0;	//生成数
							//一行目のアルファベットの最大数数分回す
	for (int nCount = 0; nCount < 10; nCount++)
	{
		//文字の画像生成
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(400.0f + 120.0f * nCount, 600.0f + 125.0f * nIndex, 0.0f));
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//生成数を加算する
		nCreateCount++;
	}
	//行番号を加算する
	nIndex++;
	//二行目のアルファベットの最大数分回す
	for (int nCount = 10; nCount < 19; nCount++)
	{
		//文字の画像生成
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(460.0f + 120.0f * (nCount - 10), 600.0f + 125.0f * nIndex, 0.0f));
		//文字を設定する
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//生成数を加算する
		nCreateCount++;
	}
	//行番号を加算する
	nIndex++;
	//三行目のアルファベットの最大数分回す
	for (int nCount = 19; nCount < 26; nCount++)
	{
		//文字の画像生成
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(580.0f + 120.0f * (nCount - 19), 600.0f + 125.0f * nIndex, 0.0f));
		//文字を設定する
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//生成数を加算する
		nCreateCount++;
	}
	//名前の最大数分回す
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//文字の画像生成
		m_apNameLetter[nCount] = CLetter::Create(D3DXVECTOR3(520.0f + 120.0f * nCount, 400.0f, 0.0f));
		//文字を設定する
		m_apNameLetter[nCount]->SetLetter(-1);
	}
}