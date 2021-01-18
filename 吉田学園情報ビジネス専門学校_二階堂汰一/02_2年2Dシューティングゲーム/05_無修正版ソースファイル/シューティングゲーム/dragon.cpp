//=============================================================================
//
// ドラゴン処理 [dragon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "dragon.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"
#include "wormhole.h"
#include "warning.h"
#include "title.h"
#include "warning.h"

LPDIRECT3DTEXTURE9 CDragon::m_pScene = NULL;
bool CDragon::m_bSpawn = false;
bool CDragon::m_bDeath = false;
//=============================================================================
// コンストラクタ
//=============================================================================
CDragon::CDragon(int nPriority) :CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量
	m_nLife = 0;							//体力
	m_nCountBullet = 0;						//弾のカウント
	m_nCountAI = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fWidth = 0.0f;						//幅
	m_fHeight = 0.0f;						//高さ
	m_fTime = 0.0f;
	m_nHitCount = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_fAngle = 0.0f;						//角度
	m_fLength = 0.0f;						//長さ
	m_fScale = 0.0f;		//大きさ
	m_fAddScale = 0.0f;	//大きさの加算量
	m_bHit = false;
	m_bSpawn = false;
	m_bDeath = false;
	m_TargetDistance = D3DXVECTOR3(0.0f,0.0f,0.0f);//目標までの距離
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目標地点
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// テクスチャのロード関数
//=============================================================================
HRESULT CDragon::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_DRAGON,								// ファイルの名前
		&m_pScene);									// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// テクスチャのアンロード関数
//=============================================================================
void CDragon::Unload(void)
{
		//テクスチャの破棄
		if (m_pScene != NULL)
		{
			m_pScene->Release();
			m_pScene = NULL;
		}
}

//=============================================================================
// 生成関数
//=============================================================================
CDragon * CDragon::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nLife)
{
	CDragon * pDragon;
	pDragon = new CDragon;
	pDragon->Init(pos, SizeWidth, SizeHeight, nLife);
	return pDragon;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CDragon::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nLife)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//オブジェタイプをドラゴンにする
	SetObjType(CScene::OBJTYPE_DRAGON);

	m_pos = pos;	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //ドラゴンの移動量
	m_nLife = nLife;						//体力
	m_nCountBullet = 0;						//弾のカウンタ
	m_nCountAI = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fWidth = SizeWidth;					//幅
	m_fHeight = SizeHeight;					//高さ
	m_fTime = 0.0f;
	m_nHitCount = 0;
	m_bHit = false;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向き
	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//長さ
	m_fAngle = atan2f((SizeWidth / 2), (SizeWidth / 2));
	m_fScale = 0.1f;
	m_fAddScale = 0.01f;	//大きさの加算量
	m_TargetDistance = D3DXVECTOR3(500, 0.0f, 0.0f);//目標までの距離
	m_TargetPos = D3DXVECTOR3(500, 0.0f, 0.0f);//目標地点
	m_bSpawn = false;
	m_bDeath = false;
	pSound->PlaySound(CSound::SOUND_LABEL_DRAGON);
	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの割り当て
	BindTexture(m_pScene);
	//色のセット
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CDragon::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CDragon::Update(void)
{
	CScene2d::Update();
	//位置を取得
	m_pos = GetPosition();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//参照するプライオリティの指定
	int nCountPriority = 4;

	if (m_fScale <= 1.0f)
	{
		m_fScale += m_fAddScale;
	}
	else
	{
		m_bSpawn = true;
	}


	if (m_bSpawn == true)
	{
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
			}
		}

		if (CBullet::GetbCharage() == true)
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//目標距離に近づいたら目標を再設定する
			if (m_pos.x >= m_TargetPos.x - 50 / 2 &&
				m_pos.x < m_TargetPos.x + 50 / 2 &&
				m_pos.y >= m_TargetPos.y - 50 / 2 &&
				m_pos.y < m_TargetPos.y + 50 / 2)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
			}
			////目標距離に近づいたら目標を再設定する
			//else if (m_pos.x > FIELD_WIDTH - 600 ||
			//	m_pos.x < FIELD_WIDTH_MIN + 600 ||
			//	m_pos.y > FIELD_HEIGHT ||
			//	m_pos.y < 0)
			//{
			//	//ランダムシード値
			//	int nRandSeed = rand() % (FIELD_WIDTH - 600) + (FIELD_WIDTH_MIN + 600);
			//	srand((unsigned int)nRandSeed);
			//	m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 600) + (FIELD_WIDTH_MIN + 600));//目標距離の決定
			//	m_TargetPos.y = (float)(rand() % 300 + 200);
			//}
			else
			{
				m_TargetDistance = D3DXVECTOR3(m_TargetPos.x - m_pos.x, m_TargetPos.y - m_pos.y, 0.0f);//目標までの距離を算出
				m_rot.y = atan2f(m_TargetDistance.y, m_TargetDistance.x);
				m_move = D3DXVECTOR3(cosf(m_rot.y)*2.5f, sinf(m_rot.y)*2.5f, 0.0f);
			}
			if (m_pos.x > FIELD_WIDTH - 200)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += -600.0f;
			}
			if (m_pos.x < FIELD_WIDTH_MIN + 200)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += 200.0f;
			}
		}
	
		//もし摘が下画面の外に行ったら
		if (m_pos.y >= FIELD_HEIGHT)
		{
			Uninit();
		}
		//プレイヤーが死んでないとき
		if (CPlayer::GetbDeath() == false)
		{
				if (m_nCountBullet % 400 == 0)
				{
					//火球の発射
					m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (DRAGON_SIZE_HEIGHT / 2), 0.0f), m_move, 35.0f, 35.0f, CBullet::USER_DRAGON, CBullet::TYPE_FIREBALL, CBullet::COLOR_ORANGE, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
				}

					//m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (DRAGON_SIZE_HEIGHT / 2), 0.0f), m_move, 35.0f, 35.0f, CBullet::USER_DRAGON, CBullet::TYPE_FIRE, CBullet::COLOR_PINK, CBullet::FIRE_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
			}
		//バレットのカウントを進める
		m_nCountBullet++;
	}

	//テクスチャアニメーション
	if (m_nCounterAnim >= 7)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim++;

		if (m_nPatternAnim > 6)
		{
			m_nPatternAnim = 0;
		}
	}

	//色の設定
	if (m_bHit == true)
	{
		m_nHitCount++;
		if (m_nHitCount == 5)
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			m_bHit = false;
			m_nHitCount = 0;
		}
	}

	//アニメーションのカウントを進める
	m_nCounterAnim++;

	//位置更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//頂点座標の設定
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//頂点座標の設定
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//頂点座標の設定
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//頂点座標の設定
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//現在位置のセット
	SetPosition(m_pos);
	//テクスチャセット
	SetTex(
		m_nPatternAnim * 0.1666f,
		0.0f,
		m_nPatternAnim * 0.1666f + 0.1666f,
		1.0f);
	//色のセット
	SetColor(m_col);
}

//=============================================================================
// 描画関数
//=============================================================================
void CDragon::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT関数
//=============================================================================
void CDragon::Hit(void)
{
	//スコアを取得
	CScore * pScore = CGame::GetScore();
	//スコア加算
	pScore->AddScore(100);
	//体力の減算
	SubLife(10);
	//HIT状態をtrueにする
	m_bHit = true;
	//色のセット
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//色のセット
	SetColor(m_col);
}

//=============================================================================
// 体力の減算関数
//=============================================================================
void CDragon::SubLife(int nValue)
{
	//スコア取得
	CScore * pScore = CGame::GetScore();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//体力の減算処理
	m_nLife -= nValue;

	//ドラゴンのライフがMIN_HP以下になったとき
	if (m_nLife <= DRAGON_MIN_HP)
	{
		//スコアの加算関数呼び出し
		pScore->AddScore(100000);
		//爆発の発生
		CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
		//爆発音の発生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		m_bDeath = true;
		m_bSpawn = false;
		pSound->StopSound();
		//名前入力に移動
		CManager::StartFade(CManager::MODE_RESULT);
		if (CTitle::GetbReplay() == true)
		{
			CManager::StartFade(CManager::MODE_TITLE);
			m_bSpawn = false;
			m_bDeath = false;
			CWormhole::SetSpawn(false);
		}
		//ドラゴンの削除
		Uninit();
		return;
	}
}

void CDragon::SetSpawn(bool bDeath)
{
	m_bSpawn = bDeath;
}

void CDragon::SetDeath(bool bDeath)
{
	m_bDeath = bDeath;
}