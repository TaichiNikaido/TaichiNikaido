//=============================================================================
//
// 敵処理 [enemy.cpp]
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
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CEnemy::m_apScene[TYPE_MAX] = {};
int CEnemy::m_nCountEnemy = 2;
int CEnemy::m_nBombEnemyLife = 200;
//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority):CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //敵の移動量
	m_nLife = 0;							//体力
	m_nCountBullet = 0;						//弾のカウント
	m_nBulletIndex = 0;
	m_fBulletAngle = 0.0f;
	m_fWidth = 0.0f;						//幅
	m_fHeight = 0.0f;						//高さ
	m_type = TYPE_NONE;						//敵の種類
	memset(m_Location, 0, sizeof(m_Location));
	m_fTime = 0.0f;
	m_fStop = 0.0f;
	m_nEnemyTimeCount = 0;
	m_nHitCount = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleRot = 0.0f;
	m_fScale = 0.0f;
	m_nStayCount = 0;
	m_bHit = false;
	m_bShot = false;
	m_bStay = true;
	m_nColor = 0;
	m_fRd = 0.0f;
	m_fRdScale = 0.1f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// テクスチャのロード関数
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EYE,								// ファイルの名前
		&m_apScene[TYPE_EYE]);						// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FLOWER,								// ファイルの名前
		&m_apScene[TYPE_FLOWER]);					// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SPIDER,								// ファイルの名前
		&m_apScene[TYPE_SPIDER]);					// 読み込むメモリー

													// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BOMBHEAD,								// ファイルの名前
		&m_apScene[TYPE_BOMBHEAD]);					// 読み込むメモリー

													// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BOMBBODY,								// ファイルの名前
		&m_apScene[TYPE_BOMBBODY]);					// 読み込むメモリー

													// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EYE2,								// ファイルの名前
		&m_apScene[TYPE_EYE2]);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャのアンロード関数
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Release();
			m_apScene[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type,int nLife)
{
	CEnemy * pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(pos, SizeWidth, SizeHeight, type,nLife);
	return pEnemy;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type,int nLife)
{
	CScene2d::Init(pos,SizeWidth,SizeHeight);

	if (type == TYPE_BOMBBODY || type == TYPE_BOMBHEAD)
	{
		//オブジェタイプを敵にする
		SetObjType(CScene::OBJTYPE_BOMBENEMY);
	}
	else
	{
		//オブジェタイプを敵にする
		SetObjType(CScene::OBJTYPE_ENEMY);
	}


	m_pos = pos;	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //敵の移動量
	if (type == TYPE_BOMBBODY || type == TYPE_BOMBHEAD)
	{
		m_move.x = 5.0f;
	}
	m_type = type;							//敵の種類
	m_nLife = nLife;						//体力
	m_nCountBullet = 0;						//弾のカウンタ
	m_nBulletIndex = 0;
	m_fBulletAngle = 0.0f;
	m_fWidth = SizeWidth;					//幅
	m_fHeight = SizeHeight;					//高さ
	m_fTime = 0.0f;
	m_nEnemyTimeCount = 0;
	m_nHitCount = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	// 対角線、角度の設定
	m_fLength = sqrtf((float)(((m_fWidth / 2) * (m_fWidth / 2)) + ((m_fHeight / 2) * (m_fHeight / 2))));
	m_fAngle = atan2f((m_fHeight / 2), (m_fWidth / 2));
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleRot = 0.0f;
	if (m_type == TYPE_BOMBHEAD||m_type == TYPE_BOMBBODY)
	{
		m_fAngleRot = D3DXToRadian(90.0f) ;
	}
	m_fScale = 1.0f;
	m_bHit = false;
	m_bShot = false;
	m_bStay = true;
	m_nStayCount = 0;
	m_nColor = 0;
	//ランダムシード値
	int nRandSeed = rand() % 100;
	srand((unsigned int)nRandSeed);
	//m_fStop = float(100 + (rand() * ((FIELD_HEIGHT / 2) - 100 + 1.0) / (1.0 + RAND_MAX)));//目標距離の決定
	m_fStop = float(rand() % (FIELD_HEIGHT / 2) + 100);

	switch (m_type)
	{
	case TYPE_FLOWER:
		m_fStop = float(rand() % (FIELD_HEIGHT / 6) + 100);
		break;
	case TYPE_SPIDER:
		m_fStop = float(rand() % (FIELD_HEIGHT / 6) + 100);
		break;
	}
	//頂点座標の設定
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;
	//頂点座標のセット
	SetVertexPosition(m_vpos);
	if (m_type == TYPE_FLOWER)
	{
		//テクスチャセット
		SetTex(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);
	}
	else if (m_type == TYPE_SPIDER)
	{
		//テクスチャセット
		SetTex(
			m_nPatternAnim * 0.5f,
			0.0f,
			m_nPatternAnim * 0.5f + 0.5f,
			1.0f);
	}
	else
	{
		//テクスチャのセット
		SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	}
	//テクスチャの割り当て
	BindTexture(m_apScene[m_type]);
	//色のセット
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CEnemy::Update(void)
{
	CScene2d::Update();
	//位置を取得
	m_pos = GetPosition();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	//もし弾が画面外に行ったら
	if (m_pos.y < 0 ||
		m_pos.y > FIELD_HEIGHT ||
		m_pos.x < FIELD_WIDTH_MIN ||
		m_pos.x > FIELD_WIDTH)
	{
		//敵の削除
		Uninit();
		return;
	}

	switch (m_type)
	{
	case TYPE_EYE:
		//プレイヤーを見つめる処理
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(4, nCountScene);
			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//もしオブジェタイプがプレイヤーの場合
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_bShot == false)
					{
						D3DXVECTOR3 playerpos = pScene->GetPosition();
						D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//プレイヤーまでの距離を計算
						m_fAngleRot = atan2f(m_TargetDistance.y, m_TargetDistance.x);//プレイヤの方に向けた角度を計算
						m_fAngleRot = m_fAngleRot * -1.0f;
					}
				}

			}
		}
		if (m_bStay == true)
		{
			//敵を指定の位置まで移動させる
			if (m_pos.y <= m_fStop)
			{
				//Y軸に移動量を代入
				m_move.y = 5.0f;
			}
			//もし敵が指定の場所で止まったら
			else
			{
				if (m_nBulletIndex < 4)
				{
					//最初プレイヤーを位置を取得して発射方向を決める
					if (m_nBulletIndex <= 0)
					{
						int nCountPriority = 4;
						for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
						{
							CScene * pScene = GetScene(nCountPriority, nCountScene);
							if (pScene != NULL)
							{
								//オブジェタイプの取得
								OBJTYPE objType;
								objType = pScene->GetObjType();
								//もしオブジェタイプがプレイヤーの場合
								if (objType == OBJTYPE_PLAYER)
								{
									D3DXVECTOR3 playerpos = pScene->GetPosition();
									D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//プレイヤーまでの距離を計算
									m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);//プレイヤの方に向けた角度を計算
									/*	m_fAngleRot = m_fBulletAngle * -1.0f;*/
								}
							}
						}
					}
					//プレイヤーが死んでないとき
					if (CPlayer::GetbDeath() == false)
					{
						//方向弾の発射
						if (m_nCountBullet % 10 == 0)
						{
							m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(cosf(m_fBulletAngle)*BULLET_SPEAD, sinf(m_fBulletAngle)*BULLET_SPEAD, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_NORMAL, CBullet::COLOR_GREEN, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
							m_bShot = true;
							m_nBulletIndex++;
						}
					}
				}
				else
				{
					//弾クールタイム
					if (m_nCountBullet % 150 == 0)
					{
						m_nBulletIndex = 0;
					}
					m_bShot = false;
				}
				//Y軸の移動量を0にする
				if (m_move.y >= 0.0f)
				{
					//慣性
					m_move.y += (0.0f - m_move.y)*RATE_MOVE;
				}
			}
			m_nStayCount++;
		}
		else
		{
				m_move.y = -7.0f;
				m_nStayCount = 0;
		}
		if (m_nStayCount == 500)
		{
			m_bStay = false;
		}

		//弾のカウントを加算
		m_nCountBullet++;
		//敵の滞在時間
		m_nEnemyTimeCount++;
		break;
		case TYPE_EYE2:
			//プレイヤーを見つめる処理
			for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
			{
				CScene * pScene = GetScene(4, nCountScene);
				if (pScene != NULL)
				{
					//オブジェタイプの取得
					OBJTYPE objType;
					objType = pScene->GetObjType();
					//もしオブジェタイプがプレイヤーの場合
					if (objType == OBJTYPE_PLAYER)
					{
						if (m_bShot == false)
						{
							D3DXVECTOR3 playerpos = pScene->GetPosition();
							D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//プレイヤーまでの距離を計算
							m_fAngleRot = atan2f(m_TargetDistance.y, m_TargetDistance.x);//プレイヤの方に向けた角度を計算
							m_fAngleRot = m_fAngleRot * -1.0f;
						}
					}

				}
			}
			if (m_bStay == true)
			{
				//敵を指定の位置まで移動させる
				if (m_pos.y <= m_fStop)
				{
					//Y軸に移動量を代入
					m_move.y = 5.0f;
				}
				//もし敵が指定の場所で止まったら
				else
				{
						//最初プレイヤーを位置を取得して発射方向を決める
						if (m_nBulletIndex <= 0)
						{
							int nCountPriority = 4;
							for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
							{
								CScene * pScene = GetScene(nCountPriority, nCountScene);
								if (pScene != NULL)
								{
									//オブジェタイプの取得
									OBJTYPE objType;
									objType = pScene->GetObjType();
									//もしオブジェタイプがプレイヤーの場合
									if (objType == OBJTYPE_PLAYER)
									{
										D3DXVECTOR3 playerpos = pScene->GetPosition();
										D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//プレイヤーまでの距離を計算
										m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);//プレイヤの方に向けた角度を計算
																										/*	m_fAngleRot = m_fBulletAngle * -1.0f;*/
									}
								}
							}
						}
						//プレイヤーが死んでないとき
						if (CPlayer::GetbDeath() == false)
						{
							//方向弾の発射
							if (m_nCountBullet % 100 == 0)
							{
								m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(cosf(m_fBulletAngle)*BULLET_SPEAD, sinf(m_fBulletAngle)*BULLET_SPEAD, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_GUID, CBullet::COLOR_GREEN, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
								m_bShot = true;
								m_nBulletIndex++;
							}
						}
					else
					{
						//弾クールタイム
						if (m_nCountBullet % 150 == 0)
						{
							m_nBulletIndex = 0;
						}
						m_bShot = false;
					}
					//Y軸の移動量を0にする
					if (m_move.y >= 0.0f)
					{
						//慣性
						m_move.y += (0.0f - m_move.y)*RATE_MOVE;
					}
				}
				m_nStayCount++;
			}
			else
			{
				m_move.y = -7.0f;
				m_nStayCount = 0;
			}
			if (m_nStayCount == 500)
			{
				m_bStay = false;
			}

			//弾のカウントを加算
			m_nCountBullet++;
			//敵の滞在時間
			m_nEnemyTimeCount++;
			break;
	case TYPE_FLOWER:
		if (m_bStay == true)
		{
			//もし停止場所以下の時
			if (m_pos.y <= m_fStop)
			{
				//Y軸に移動量を代入
				m_move.y = 5.0f;
			}
			//もし敵が指定の場所で止まったら
			else
			{
				//慣性
				m_move.y += (0.0f - m_move.y)*RATE_MOVE;

				//初弾を発射するまでの時間
				if (m_nCountBullet >= 50)
				{
					//プレイヤーが死んでないとき
					if (CPlayer::GetbDeath() == false)
					{
						if (m_nCountBullet % 20 == 0)
						{
							//ショット音の再生
							//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);

							if (m_nColor < 7)
							{
								for (int nCnt = 0; nCnt < 20; nCnt++)
								{
									CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, 0.0f), BULLET_SIZE * 4, BULLET_SIZE * 4, CBullet::USER_ENEMY, CBullet::TYPE_FLOWER, (CBullet::COLOR)m_nColor, CBullet::FLOWER_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
									//弾の生成
									//CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_FLOWER, m_nColor, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
								}
							}

							//色のカウントを加算
							m_nColor++;
						}

						if (m_nColor > 7)
						{
							if (m_nCountBullet % 100 == 0)
							{
								m_nColor = 0;
							}
						}
					}
				}
				//弾のカウントを加算
				m_nCountBullet++;
			}
			m_nStayCount++;
		}
		else
		{
			m_move.y = -7.0f;
			m_nStayCount = 0;
		}
		if (m_nStayCount == 400)
		{
			m_bStay = false;
		}

		break;
	case TYPE_SPIDER:
		//もし停止場所以下の時
		if (m_pos.y <= m_fStop)
		{
			//Y軸に移動量を代入
			m_move.y = 5.0f;
		}
		//もし敵が指定の場所で止まったら
		else
		{
			//慣性
			m_move.y += (0.0f - m_move.y)*RATE_MOVE;

			//初弾を発射するまでの時間
			if (m_nCountBullet >= 50)
			{
				//プレイヤーが死んでないとき
				if (CPlayer::GetbDeath() == false)
				{
					if (m_nCountBullet % 20 == 0)
					{
						for (int nCnt = 0; nCnt < 9; nCnt++)
						{
							CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_NORMAL, CBullet::COLOR_WHITE, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
						}
					}

					//誘導弾の発射
		/*			if (m_nCountBullet % 250 == 0)
					{
						m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + 10, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_GUID, CBullet::COLOR_RED, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
					}*/
				}
			}
			//弾のカウントを加算
			m_nCountBullet++;
		}
		break;
	case TYPE_BOMBHEAD:

		m_fRd += m_fRdScale;
		if (m_fRd >= 360)
		{
			m_fRd = 0;
		}

		m_move.y = float((5 * sin(m_fRd)));

		if (m_pos.x < FIELD_WIDTH_MIN + 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		if (m_pos.x > FIELD_WIDTH - 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		//進行方向に向きを合わせる
		m_fAngleRot = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
		break;
	case TYPE_BOMBBODY:

		m_fRd += m_fRdScale;
		if (m_fRd >= 360.0f)
		{
			m_fRd = 0;
		}

		m_move.y = float((5 * sin(m_fRd)));

		if (m_pos.x < FIELD_WIDTH_MIN + 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		if (m_pos.x > FIELD_WIDTH - 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		//進行方向に向きを合わせる
		m_fAngleRot = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
		break;
	default:
		break;
	}

	switch (m_type)
	{
	case TYPE_FLOWER:
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

		break;
	case TYPE_SPIDER:
		if (m_nCounterAnim >= 7)
		{
			m_nCounterAnim = 0;

			m_nPatternAnim++;

			if (m_nPatternAnim > 6)
			{
				m_nPatternAnim = 0;
			}
		}
		break;
	}

	//アニメーションのカウントを進める
	m_nCounterAnim++;

	//位置更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//もし摘が下画面の外に行ったら
	if (m_pos.y >= FIELD_HEIGHT)
	{
		Uninit();
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

	//頂点座標の設定
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//現在位置のセット
	SetPosition(m_pos);

	if (m_type == TYPE_FLOWER)
	{
		//テクスチャセット
		SetTex(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);
	}
	else if (m_type == TYPE_SPIDER)
	{
		//テクスチャセット
		SetTex(
			m_nPatternAnim * 0.5f,
			0.0f,
			m_nPatternAnim * 0.5f + 0.5f,
			1.0f);
	}
	else
	{
		//テクスチャのセット
		SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	}

	//色のセット
	SetColor(m_col);
	m_fTime++;
}

//=============================================================================
// 描画関数
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT関数
//=============================================================================
void CEnemy::Hit(void)
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
// 体力減算関数
//=============================================================================
void CEnemy::SubLife(int nValue)
{
	//スコア取得
	CScore * pScore = CGame::GetScore();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	if (m_type == TYPE_BOMBBODY || m_type == TYPE_BOMBHEAD)
	{
		m_nBombEnemyLife -= nValue;

		if (m_nBombEnemyLife < 0)
		{
			int nCountPriority = 4;
			for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
			{
				CScene * pScene = GetScene(nCountPriority, nCountScene);
				if (pScene != NULL)
				{
					//オブジェタイプの取得
					OBJTYPE objType;
					objType = pScene->GetObjType();
					//もしオブジェタイプがボム的の場合
					if (objType == OBJTYPE_BOMBENEMY)
					{
						D3DXVECTOR3 pos = pScene->GetPosition();
						//爆発の発生
						CExplosion::Create(pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);

						//敵の種類によってスコアの加算量を変える
						switch (m_type)
						{
						case TYPE_BOMBBODY:
							//スコアの加算関数呼び出し
							pScore->AddScore(1000);
							//爆発の発生
							CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
							//CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_SCORE);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
							break;
						case TYPE_BOMBHEAD:
							//スコアの加算関数呼び出し
							pScore->AddScore(10000);
							//爆発の発生
							CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
							CItem::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
							break;

						}

						pScene->Uninit();
					}

				}
			}
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			m_nBombEnemyLife = 200;
	/*		Uninit();
			return;*/
		}
	}
	else
	{
		//体力の減算処理
		m_nLife -= nValue;




		//敵のライフがENEMY_MIN_HP以下になったとき
		if (m_nLife <= ENEMY_MIN_HP)
		{
			//敵の種類によってスコアの加算量を変える
			switch (m_type)
			{
			case TYPE_EYE:
				//スコアの加算関数呼び出し
				pScore->AddScore(10000);
				//爆発の発生
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				//CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_SCORE);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_FLOWER:
				//スコアの加算関数呼び出し
				pScore->AddScore(50000);
				//回復アイテムのドロップ
				CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_OWN);
				//爆発の発生
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_SPIDER:
				//スコアの加算関数呼び出し
				pScore->AddScore(100000);
				//LVUPアイテムのドロップ
				CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);
				//爆発の発生
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_EYE2:
				//スコアの加算関数呼び出し
				pScore->AddScore(100000);
				//LVUPアイテムのドロップ
				//CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);
				//爆発の発生
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
				//case TYPE_HARD:
				//	//スコアの加算関数呼び出し
				//	pScore->AddScore(100000);
				//	//爆発の発生
				//	CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				//	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				//	break;
			}
			m_nCountEnemy--;

			if (m_nCountEnemy == 0)
			{
				m_nCountEnemy = 2;
				//リザルトに移動
				//CManager::StartFade(CManager::MODE_RESULT);
			}
			Uninit();
			return;
		}
	}
}
