//=============================================================================
//
// ボス処理 [boss.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "boss.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CBoss::m_apTexture[PART_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBoss::CBoss(int nPriority) :CScene2d(nPriority)
{
	memset(m_apScene, 0, sizeof(m_apScene));
	memset(m_PartStatus, 0, sizeof(m_PartStatus));
	m_nLife = 0;
	m_nCountBullet = 0;					//弾のカウント
	m_pBullet = NULL;					//弾のポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CBoss::~CBoss()
{
}

//=============================================================================
// テクスチャのロード関数
//=============================================================================
HRESULT CBoss::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART00_TEXTURE,								// ファイルの名前
		&m_apTexture[CORE_02]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART01_TEXTURE,								// ファイルの名前
		&m_apTexture[CORE]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART02_TEXTURE,								// ファイルの名前
		&m_apTexture[CORE_01]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART03_TEXTURE,								// ファイルの名前
		&m_apTexture[BODY_RIGHT]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART04_TEXTURE,								// ファイルの名前
		&m_apTexture[BODY_LEFT]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART05_TEXTURE,								// ファイルの名前
		&m_apTexture[HAND_RIGHT]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART06_TEXTURE,								// ファイルの名前
		&m_apTexture[HAND_LEFT]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART07_TEXTURE,								// ファイルの名前
		&m_apTexture[FOREARM_RIGHT]);				// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART08_TEXTURE,								// ファイルの名前
		&m_apTexture[FOREARM_LEFT]);				// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART09_TEXTURE,								// ファイルの名前
		&m_apTexture[UPPERARM_RIGHT]);				// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART10_TEXTURE,								// ファイルの名前
		&m_apTexture[UPPERARM_LEFT]);				// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART11_TEXTURE,								// ファイルの名前
		&m_apTexture[HEAD]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART12_TEXTURE,								// ファイルの名前
		&m_apTexture[CHIN]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART13_TEXTURE,								// ファイルの名前
		&m_apTexture[EYE]);							// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		PART14_TEXTURE,								// ファイルの名前
		&m_apTexture[EYEFLAME]);					// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// テクスチャのアンロード関数
//=============================================================================
void CBoss::Unload(void)
{
	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		//テクスチャの破棄
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
CBoss * CBoss::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CBoss * pBoss;
	pBoss = new CBoss;
	pBoss->Init(pos, SizeHeight, SizeWidth);
	return pBoss;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	SetObjType(CScene::OBJTYPE_ENEMY);

	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		m_apScene[nCount] = new CScene2d(5);
		m_apScene[nCount]->Init(pos, SizeWidth, SizeHeight);

		for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
		{
			m_PartStatus[nCount].m_vpos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		}
		m_PartStatus[nCount].m_pos = pos;										//位置
		m_PartStatus[nCount].m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		m_PartStatus[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
		m_PartStatus[nCount].m_fWidth = 100.0f;									//幅
		m_PartStatus[nCount].m_fHeight = 100.0f;								//高さ
		m_PartStatus[nCount].m_fLength = sqrtf((float)(((m_PartStatus[nCount].m_fWidth / 2) * (m_PartStatus[nCount].m_fWidth / 2)) + ((m_PartStatus[nCount].m_fHeight / 2) * (m_PartStatus[nCount].m_fHeight / 2))));	//長さ
		m_PartStatus[nCount].m_fAngle = atan2f((m_PartStatus[nCount].m_fHeight / 2), (m_PartStatus[nCount].m_fWidth / 2));//角度
		m_PartStatus[nCount].m_fScale = 0.5f;									//拡大

		// 頂点座標を設定
		m_PartStatus[nCount].m_vpos[0].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].z = 0.0f;

		m_PartStatus[nCount].m_vpos[1].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].z = 0.0f;

		m_PartStatus[nCount].m_vpos[2].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].z = 0.0f;

		m_PartStatus[nCount].m_vpos[3].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].z = 0.0f;

		//位置のセット
		m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
		//頂点座標のセット
		m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
		//テクスチャをセット
		m_apScene[nCount]->SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
		//テクスチャの割り当て
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}
		m_PartStatus[HEAD].m_pos = D3DXVECTOR3(FIELD_WIDTH / 2 + 1 * m_PartStatus[HEAD].m_fScale, FIELD_HEIGHT / 4, 0.0f);
		m_PartStatus[HEAD].m_fWidth = 300.0f;	//幅
		m_PartStatus[HEAD].m_fHeight = 360.0f;	//高さ
		m_PartStatus[HEAD].m_fLength = sqrtf((float)(((m_PartStatus[HEAD].m_fWidth / 2) * (m_PartStatus[HEAD].m_fWidth / 2)) + ((m_PartStatus[HEAD].m_fHeight / 2) * (m_PartStatus[HEAD].m_fHeight / 2))));	//長さ
		m_PartStatus[HEAD].m_fAngle = atan2f((m_PartStatus[HEAD].m_fHeight / 2), (m_PartStatus[HEAD].m_fWidth / 2));//角度

		m_PartStatus[EYE].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + -10.0f * m_PartStatus[EYE].m_fScale, 0.0f);
		m_PartStatus[EYE].m_fWidth = 80.0f;		//幅
		m_PartStatus[EYE].m_fHeight = 80.0f;	//高さ
		m_PartStatus[EYE].m_fLength = sqrtf((float)(((m_PartStatus[EYE].m_fWidth / 2) * (m_PartStatus[EYE].m_fWidth / 2)) + ((m_PartStatus[EYE].m_fHeight / 2) * (m_PartStatus[EYE].m_fHeight / 2))));	//長さ
		m_PartStatus[EYE].m_fAngle = atan2f((m_PartStatus[EYE].m_fHeight / 2), (m_PartStatus[EYE].m_fWidth / 2));//角度

		m_PartStatus[EYEFLAME].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y - 20.0f * m_PartStatus[EYEFLAME].m_fScale, 0.0f);
		m_PartStatus[EYEFLAME].m_fWidth = 220.0f;	//幅
		m_PartStatus[EYEFLAME].m_fHeight = 190.0f;	//高さ
		m_PartStatus[EYEFLAME].m_fLength = sqrtf((float)(((m_PartStatus[EYEFLAME].m_fWidth / 2) * (m_PartStatus[EYEFLAME].m_fWidth / 2)) + ((m_PartStatus[EYEFLAME].m_fHeight / 2) * (m_PartStatus[EYEFLAME].m_fHeight / 2))));	//長さ
		m_PartStatus[EYEFLAME].m_fAngle = atan2f((m_PartStatus[EYEFLAME].m_fHeight / 2), (m_PartStatus[EYEFLAME].m_fWidth / 2));//角度

		m_PartStatus[CHIN].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + 150.0f * m_PartStatus[CHIN].m_fScale, 0.0f);
		m_PartStatus[CHIN].m_fWidth = 130.0f;	//幅
		m_PartStatus[CHIN].m_fHeight = 70.0f;	//高さ
		m_PartStatus[CHIN].m_fLength = sqrtf((float)(((m_PartStatus[CHIN].m_fWidth / 2) * (m_PartStatus[CHIN].m_fWidth / 2)) + ((m_PartStatus[CHIN].m_fHeight / 2) * (m_PartStatus[CHIN].m_fHeight / 2))));	//長さ
		m_PartStatus[CHIN].m_fAngle = atan2f((m_PartStatus[CHIN].m_fHeight / 2), (m_PartStatus[CHIN].m_fWidth / 2));//角度

		m_PartStatus[CORE_02].m_pos = D3DXVECTOR3(600.0f * m_PartStatus[CORE_02].m_fScale, m_PartStatus[HEAD].m_pos.y + 375.0f * m_PartStatus[CORE_02].m_fScale, 0.0f);
		m_PartStatus[CORE_02].m_fWidth = 400;	//幅
		m_PartStatus[CORE_02].m_fHeight = 480;	//高さ
		m_PartStatus[CORE_02].m_fLength = sqrtf((float)(((m_PartStatus[CORE_02].m_fWidth / 2) * (m_PartStatus[CORE_02].m_fWidth / 2)) + ((m_PartStatus[CORE_02].m_fHeight / 2) * (m_PartStatus[CORE_02].m_fHeight / 2))));	//長さ
		m_PartStatus[CORE_02].m_fAngle = atan2f((m_PartStatus[CORE_02].m_fHeight / 2), (m_PartStatus[CORE_02].m_fWidth / 2));//角度

		m_PartStatus[CORE].m_pos = D3DXVECTOR3(FIELD_WIDTH / 2 + 1 * m_PartStatus[CORE].m_fScale, m_PartStatus[HEAD].m_pos.y + 550.0f * m_PartStatus[CORE].m_fScale, 0.0f);
		m_PartStatus[CORE].m_fWidth = 120;	//幅
		m_PartStatus[CORE].m_fHeight = 120;	//高さ
		m_PartStatus[CORE].m_fLength = sqrtf((float)(((m_PartStatus[CORE].m_fWidth / 2) * (m_PartStatus[CORE].m_fWidth / 2)) + ((m_PartStatus[CORE].m_fHeight / 2) * (m_PartStatus[CORE].m_fHeight / 2))));	//長さ
		m_PartStatus[CORE].m_fAngle = atan2f((m_PartStatus[CORE].m_fHeight / 2), (m_PartStatus[CORE].m_fWidth / 2));//角度

		m_PartStatus[CORE_01].m_pos = D3DXVECTOR3(600.0f * m_PartStatus[CORE_01].m_fScale, m_PartStatus[HEAD].m_pos.y + 520.0f * m_PartStatus[CORE_01].m_fScale, 0.0f);
		m_PartStatus[CORE_01].m_fWidth = 260;	//幅
		m_PartStatus[CORE_01].m_fHeight = 600;	//高さ
		m_PartStatus[CORE_01].m_fLength = sqrtf((float)(((m_PartStatus[CORE_01].m_fWidth / 2) * (m_PartStatus[CORE_01].m_fWidth / 2)) + ((m_PartStatus[CORE_01].m_fHeight / 2) * (m_PartStatus[CORE_01].m_fHeight / 2))));	//長さ
		m_PartStatus[CORE_01].m_fAngle = atan2f((m_PartStatus[CORE_01].m_fHeight / 2), (m_PartStatus[CORE_01].m_fWidth / 2));//角度

		m_PartStatus[BODY_RIGHT].m_pos = D3DXVECTOR3(450.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[BODY_RIGHT].m_fScale, 0.0f);
		m_PartStatus[BODY_RIGHT].m_fWidth = 300;	//幅
		m_PartStatus[BODY_RIGHT].m_fHeight = 600;	//高さ
		m_PartStatus[BODY_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[BODY_RIGHT].m_fWidth / 2) * (m_PartStatus[BODY_RIGHT].m_fWidth / 2)) + ((m_PartStatus[BODY_RIGHT].m_fHeight / 2) * (m_PartStatus[BODY_RIGHT].m_fHeight / 2))));	//長さ
		m_PartStatus[BODY_RIGHT].m_fAngle = atan2f((m_PartStatus[BODY_RIGHT].m_fHeight / 2), (m_PartStatus[BODY_RIGHT].m_fWidth / 2));//角度

		m_PartStatus[BODY_LEFT].m_pos = D3DXVECTOR3(745 * m_PartStatus[BODY_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[BODY_LEFT].m_fScale, 0.0f);
		m_PartStatus[BODY_LEFT].m_fWidth = 300;	//幅
		m_PartStatus[BODY_LEFT].m_fHeight = 600;	//高さ
		m_PartStatus[BODY_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[BODY_LEFT].m_fWidth / 2) * (m_PartStatus[BODY_LEFT].m_fWidth / 2)) + ((m_PartStatus[BODY_LEFT].m_fHeight / 2) * (m_PartStatus[BODY_LEFT].m_fHeight / 2))));	//長さ
		m_PartStatus[BODY_LEFT].m_fAngle = atan2f((m_PartStatus[BODY_LEFT].m_fHeight / 2), (m_PartStatus[BODY_LEFT].m_fWidth / 2));//角度

		m_PartStatus[HAND_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x + -1250.0f * m_PartStatus[HAND_RIGHT].m_fScale, m_PartStatus[HEAD].m_pos.y + 250.0f * m_PartStatus[HAND_RIGHT].m_fScale, 0.0f);
		m_PartStatus[HAND_RIGHT].m_fWidth = 240;	//幅
		m_PartStatus[HAND_RIGHT].m_fHeight = 165;	//高さ
		m_PartStatus[HAND_RIGHT].m_rot.z = D3DXToRadian(180.0f);
		m_PartStatus[HAND_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[HAND_RIGHT].m_fWidth / 2) * (m_PartStatus[HAND_RIGHT].m_fWidth / 2)) + ((m_PartStatus[HAND_RIGHT].m_fHeight / 2) * (m_PartStatus[HAND_RIGHT].m_fHeight / 2))));	//長さ
		m_PartStatus[HAND_RIGHT].m_fAngle = atan2f((m_PartStatus[HAND_RIGHT].m_fHeight / 2), (m_PartStatus[HAND_RIGHT].m_fWidth / 2));//角度

		//m_PartStatus[HAND_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[HAND_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 250.0f * m_PartStatus[HAND_LEFT].m_fScale, 0.0f);
		//m_PartStatus[HAND_LEFT].m_fWidth = 240;	//幅
		//m_PartStatus[HAND_LEFT].m_fHeight = 165;	//高さ
		//m_PartStatus[HAND_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[HAND_LEFT].m_fWidth / 2) * (m_PartStatus[HAND_LEFT].m_fWidth / 2)) + ((m_PartStatus[HAND_LEFT].m_fHeight / 2) * (m_PartStatus[HAND_LEFT].m_fHeight / 2))));	//長さ
		//m_PartStatus[HAND_LEFT].m_fAngle = atan2f((m_PartStatus[HAND_LEFT].m_fHeight / 2), (m_PartStatus[HAND_LEFT].m_fWidth / 2));//角度

		m_PartStatus[FOREARM_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HAND_RIGHT].m_pos.x + 300.0f * m_PartStatus[FOREARM_RIGHT].m_fScale, m_PartStatus[HAND_RIGHT].m_pos.y + -20.0f * m_PartStatus[FOREARM_RIGHT].m_fScale, 0.0f);
		m_PartStatus[FOREARM_RIGHT].m_fWidth = 470;	//幅
		m_PartStatus[FOREARM_RIGHT].m_fHeight = 120;	//高さ
		m_PartStatus[FOREARM_RIGHT].m_rot.z = D3DXToRadian(180.0f);
		m_PartStatus[FOREARM_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[FOREARM_RIGHT].m_fWidth / 2) * (m_PartStatus[FOREARM_RIGHT].m_fWidth / 2)) + ((m_PartStatus[FOREARM_RIGHT].m_fHeight / 2) * (m_PartStatus[FOREARM_RIGHT].m_fHeight / 2))));	//長さ
		m_PartStatus[FOREARM_RIGHT].m_fAngle = atan2f((m_PartStatus[FOREARM_RIGHT].m_fHeight / 2), (m_PartStatus[FOREARM_RIGHT].m_fWidth / 2));//角度

		//m_PartStatus[FOREARM_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[FOREARM_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[FOREARM_LEFT].m_fScale, 0.0f);
		//m_PartStatus[FOREARM_LEFT].m_fWidth = 470;	//幅
		//m_PartStatus[FOREARM_LEFT].m_fHeight = 120;	//高さ
		//m_PartStatus[FOREARM_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[FOREARM_LEFT].m_fWidth / 2) * (m_PartStatus[FOREARM_LEFT].m_fWidth / 2)) + ((m_PartStatus[FOREARM_LEFT].m_fHeight / 2) * (m_PartStatus[FOREARM_LEFT].m_fHeight / 2))));	//長さ
		//m_PartStatus[FOREARM_LEFT].m_fAngle = atan2f((m_PartStatus[FOREARM_LEFT].m_fHeight / 2), (m_PartStatus[FOREARM_LEFT].m_fWidth / 2));//角度

		m_PartStatus[UPPERARM_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HAND_RIGHT].m_pos.x + 750.0f * m_PartStatus[UPPERARM_RIGHT].m_fScale, m_PartStatus[HAND_RIGHT].m_pos.y + -20.0f * m_PartStatus[UPPERARM_RIGHT].m_fScale, 0.0f);
		m_PartStatus[UPPERARM_RIGHT].m_fWidth = 440;	//幅
		m_PartStatus[UPPERARM_RIGHT].m_fHeight = 140;	//高さ
		m_PartStatus[UPPERARM_RIGHT].m_rot.z = D3DXToRadian(0.0f);
		m_PartStatus[UPPERARM_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2) * (m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2)) + ((m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2) * (m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2))));	//長さ
		m_PartStatus[UPPERARM_RIGHT].m_fAngle = atan2f((m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2), (m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2));//角度

		//m_PartStatus[UPPERARM_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[UPPERARM_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[UPPERARM_LEFT].m_fScale, 0.0f);
		//m_PartStatus[UPPERARM_LEFT].m_fWidth = 440;	//幅
		//m_PartStatus[UPPERARM_LEFT].m_fHeight = 140;	//高さ
		//m_PartStatus[UPPERARM_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[UPPERARM_LEFT].m_fWidth / 2) * (m_PartStatus[UPPERARM_LEFT].m_fWidth / 2)) + ((m_PartStatus[UPPERARM_LEFT].m_fHeight / 2) * (m_PartStatus[UPPERARM_LEFT].m_fHeight / 2))));	//長さ
		//m_PartStatus[UPPERARM_LEFT].m_fAngle = atan2f((m_PartStatus[UPPERARM_LEFT].m_fHeight / 2), (m_PartStatus[UPPERARM_LEFT].m_fWidth / 2));//角度

		for (int nCount = 0; nCount < PART_MAX; nCount++)
		{
			//位置のセット
			m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
			//頂点座標のセット
			m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
			//テクスチャをセット
			m_apScene[nCount]->SetTex(
				0.0f,
				0.0f,
				1.0f,
				1.0f);
			//テクスチャの割り当て
			m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
		}
	m_nLife = BOSS_LIFE;
	m_nCountBullet = 0;
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBoss::Uninit(void)
{
}

//=============================================================================
// 更新関数
//=============================================================================
void CBoss::Update(void)
{
	int nCountPriority = 4;

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(nCountPriority, nCountScene);

		if (pScene != NULL)
		{
			//プレイヤーの位置を取得
			D3DXVECTOR3 player_pos;
			player_pos = pScene->GetPosition();
			//オブジェタイプの取得
			OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_PLAYER)
			{
				m_PartStatus[HEAD].m_pos.x = player_pos.x;
			}

			//頭の回転
		/*	m_PartStatus[HEAD].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[HEAD].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[HEAD].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[EYE].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[EYE].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[EYE].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[EYEFLAME].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[EYEFLAME].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[EYEFLAME].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[CHIN].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[CHIN].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[CHIN].m_rot.z += D3DX_PI * 2.0f;
			}*/

			m_PartStatus[EYE].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + -10.0f * m_PartStatus[EYE].m_fScale, 0.0f);
			m_PartStatus[EYEFLAME].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y - 20.0f * m_PartStatus[EYEFLAME].m_fScale, 0.0f);
			m_PartStatus[CHIN].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + 150.0f * m_PartStatus[CHIN].m_fScale, 0.0f);

			m_PartStatus[CORE_01].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x, m_PartStatus[CORE].m_pos.y + -40.0f * m_PartStatus[CORE_01].m_fScale, 0.0f);
			m_PartStatus[CORE_02].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x, m_PartStatus[CORE].m_pos.y + -150.0f * m_PartStatus[CORE_02].m_fScale, 0.0f);
			m_PartStatus[BODY_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x - 145.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[CORE].m_pos.y + -170.0f * m_PartStatus[BODY_RIGHT].m_fScale, 0.0f);
			m_PartStatus[BODY_LEFT].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x + 145.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[CORE].m_pos.y + -170.0f * m_PartStatus[BODY_LEFT].m_fScale, 0.0f);

			m_PartStatus[HAND_RIGHT].m_rot.z = 60.0f;
			m_PartStatus[FOREARM_RIGHT].m_rot.z = 60.0f;  //120 + 235
			m_PartStatus[FOREARM_RIGHT].m_pos.y = 180.0f; //540
			m_PartStatus[UPPERARM_RIGHT].m_rot.z = 60.0f;
			//m_PartStatus[FOREARM_RIGHT].m_pos.y + 60.0f;
		}
	}

	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		m_apScene[nCount]->Update();

		// 頂点座標を設定
		m_PartStatus[nCount].m_vpos[0].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].z = 0.0f;

		m_PartStatus[nCount].m_vpos[1].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].z = 0.0f;

		m_PartStatus[nCount].m_vpos[2].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].z = 0.0f;

		m_PartStatus[nCount].m_vpos[3].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].z = 0.0f;

		//位置更新
		m_PartStatus[nCount].m_pos += m_PartStatus[nCount].m_move;
		//位置のセット
		m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
		//頂点座標のセット
		m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
		//テクスチャをセット
		m_apScene[nCount]->SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CBoss::Draw(void)
{
}

//=============================================================================
// 体力の減算関数
//=============================================================================
void CBoss::SubLife(int nValue)
{
}
