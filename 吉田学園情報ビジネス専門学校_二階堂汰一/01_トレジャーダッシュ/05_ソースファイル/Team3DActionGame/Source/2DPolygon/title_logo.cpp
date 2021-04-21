//=============================================================================
//
// タイトルロゴの処理 [titlelogo.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//================================================
// インクルード
//================================================
#include "title_logo.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CTitlelogo::m_apTexture[TITLELOGO_TYPE] = {};

//================================================
//クリエイト処理
//================================================
CTitlelogo* CTitlelogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type)
{
	// オブジェクトを生成
	CTitlelogo* pLogo = new CTitlelogo;

	// 初期化処理
	pLogo->Init(pos, size, type);

	return pLogo;
}

//================================================
//ロード処理
//================================================
HRESULT CTitlelogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/title000.png", //ファイルの読み込み
		&m_apTexture[LOGOTIPE_TITLE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/Texture/GAME_START.png", //ファイルの読み込み
		&m_apTexture[LOGOTIPE_PRESS]);

	return S_OK;
}

//================================================
//ロードの終了
//================================================
void CTitlelogo::Unload(void)
{
	for (int nCount = 0; nCount < TITLELOGO_TYPE; nCount++)
	{
		//テクスチャの開放
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}

}

//================================================
//コンストラクタ
//================================================
CTitlelogo::CTitlelogo()
{
	m_nPattern = 0;								// パターン数
	m_nCounter = 0;								// カウンタ	

	m_pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 座標
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 移動量
	m_size = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// サイズ
	m_type = LOGOTYPE_NONE;						// タイプ
}

//================================================
//デストラクタ
//================================================
CTitlelogo::~CTitlelogo()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTitlelogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type)
{
	m_pos = pos;	//位置情報
	m_size = size;	//サイズ
	m_type = type;	//タイプ

	CScene2d::Init();	//CScene2dの初期化

						//位置設定
	CScene2d::SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));

	//サイズ設定
	CScene2d::SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));

	//カラー設定
	CScene2d::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャー
	D3DXVECTOR2 texture[4];
	texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	texture[1] = D3DXVECTOR2(1.0f, 0.0f);
	texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	texture[3] = D3DXVECTOR2(1.0f, 1.0f);

	// テクスチャーの設定
	CScene2d::SetTexture(texture);

	CScene2d::BindTexture(m_apTexture[type]);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CTitlelogo::Uninit(void)
{
	CScene2d::Uninit();
}

//================================================
//更新処理
//================================================
void CTitlelogo::Update(void)
{
	CScene2d::Update();

	//点滅させる処理
	Flashing();
}

//================================================
//描画処理
//================================================
void CTitlelogo::Draw(void)
{
	CScene2d::Draw();
}

//================================================
//点滅させる処理
//================================================
void CTitlelogo::Flashing(void)
{
	//色の取得
	D3DXCOLOR col = GetColor();

	if (m_type == LOGOTIPE_PRESS)
	{
		m_nCounter++;
		if (m_nCounter == TITLE_PLESS_COLLAR)
		{
			col.a = 0.0f;
		}
		else if (m_nCounter == TITLE_PLESS_ERASE)
		{
			col.a = 1.0f;

			m_nCounter = 0;
		}
	}

	//色の設定
	SetColor(col);
}
