//=============================================================================
//
//	弾 [bullet.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "score.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "warning.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[TEXTURE_MAX] = {};
D3DCOLOR CBullet::m_aColor[COLOR_MAX] = //色パラメータ
{
	D3DCOLOR_RGBA(255,0,0,255),    //赤
	D3DCOLOR_RGBA(255,128,0,255),// オレンジ
	D3DCOLOR_RGBA(255,255,0,255),// 黄色
	D3DCOLOR_RGBA(0,255,0,255),//緑
	D3DCOLOR_RGBA(0,0,255,255),//青
	D3DCOLOR_RGBA(128,0,255,255),//紫
	D3DCOLOR_RGBA(255,0,255,255),//ピンク
	D3DCOLOR_RGBA(255,255,255,255)//白
};
bool CBullet::m_bFireBall = true;
bool CBullet::m_bCharage = true;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量	
	m_user = USER_NONE;						//使用者
	m_type = TYPE_NORMAL;	                //タイプ
	m_texture = BULLET_TEXTURE;				//テクスチャ
	m_nAttack = 0;							//攻撃力
	m_fWidth = 0.0f;						//幅
	m_fHeight = 0.0f;						//高さ
	m_pEffect = NULL;						//エフェクトのポインタ
	m_nCountBullet = 0;						//カウント
	m_nBreatheCount = 0;					//ブレスカウント
	m_nLife = 0;							//体力
	m_pCol = COLOR_ORANGE;					//色へのポインタ
	m_nCount = 0;							//カウント
	m_fDistance = 0.0f;						//距離
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_fSpeed = 0.0f;						//速さ
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_fAngle = 0.0f;						//角度
	m_fLength = 0.0f;						//長さ
	m_fScale = 0.0f;						//大きさ
	m_fAddScale = 0.0f;						//大きさの加算量
	m_bShotFireball = true;					//火球を撃ったかどうか
	m_bFireBall = true;						//火球の使用状態
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CBullet::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BULLET,								// ファイルの名前
		&m_apTexture[BULLET_TEXTURE]);				// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BEAM,								// ファイルの名前
		&m_apTexture[BEAM_TEXTURE]);					// 読み込むメモリー
														// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BIRA,								// ファイルの名前
		&m_apTexture[FLOWER_TEXTURE]);					// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FIRE,								// ファイルの名前
		&m_apTexture[FIRE_TEXTURE]);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
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
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,USER user,TYPE type, COLOR col, TEXTURE texture, int nAttack)
{
	CBullet * pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos,move, SizeWidth, SizeHeight,user,type,col,texture,nAttack);
	pBullet->SetPosition(pos);

	return pBullet;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,USER user, TYPE type, COLOR col, TEXTURE texture, int nAttack)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	m_pos = pos;	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_move = move;			//移動量
	m_user = user;			//使用者
	m_type = type;			//タイプ
	m_texture = texture;	//テクスチャ
	m_nAttack = nAttack;	//攻撃力
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight;	//高さ
	m_pCol = col;			//カラー
	m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(0, 0, 0, 0), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_NONE);
	m_nCountBullet = 0;		//カウント
	m_nBreatheCount = 0;	//ブレスカウント
	m_nLife = 175;			//体力
	//もし誘導弾だったら
	if (m_type == TYPE_GUID)
	{
		m_nLife = 110;
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//長さ
	m_fAngle = atan2f((SizeHeight / 2), (SizeWidth / 2));
	m_fScale = 1.0f;		//大きさ
	m_fAddScale = 0.01f;	//大きさの加算量
	m_bShotFireball = true;	//火球を撃ったかどうか
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目標の位置
	//オブジェタイプを弾にする。
	SetObjType(CScene::OBJTYPE_BULLET);
	//もしタイプが火球だったら
	if (m_type == TYPE_FIREBALL)
	{
		m_fScale = 0.1f;
		m_nLife = 75;
		SetObjType(CScene::OBJTYPE_FIREBALL);
		m_bCharage = true;
	}
	//もしタイプが火だったr
	if (m_type == TYPE_FIRE)
	{
		SetObjType(CScene::OBJTYPE_FIRE);
	}
	//目標までの距離
	m_fDistance = 0.0f;
	m_fSpeed = 5.0f;	//速さ
	//頂点座標の設定
	m_vpos[0].x = pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//頂点座標の設定
	m_vpos[1].x = pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//頂点座標の設定
	m_vpos[2].x = pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//頂点座標の設定
	m_vpos[3].x = pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;
	CPlayer * pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	//プレイヤーへの角度
	m_rot.z = atan2f(PlayerPos.y - pos.y , PlayerPos.x - pos.x);
	//頂点座標をセット
	SetVertexPosition(m_vpos);
	//もしテクスチャが花だったrくぁ
	if (m_texture == FLOWER_TEXTURE)
	{
		//テクスチャの設定
		SetTex(
			m_pCol * 0.1428f,
			0.0f,
			m_pCol * 0.1428f + 0.1428f,
			1.0f
		);
	}
      	else
	{
		//テクスチャのセット
		SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
	//頂点カラーの設定
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//色のセット
	SetColor(m_col); 
	//テクスチャの割り当て
	BindTexture(m_apTexture[m_texture]);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBullet::Update(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	CScene2d::Update();
	//位置を取得
	m_pos = GetPosition();
	//移動可能範囲制御処理関数呼び出し
	MovableRange();
	//衝突判定処理関数呼び出し
	Collision();
	if (m_type == TYPE_FIREBALL)
	{
		if (m_nCountBullet == 0)
		{
			CWarning::Create(D3DXVECTOR3(m_pos.x, m_TargetPos.y, 0.0f), D3DXVECTOR3(m_move.x, m_move.y, 0.0f), 1120 - 200, FIELD_HEIGHT / 4);
		}
	}
	//位置更新処理関数呼び出し
	UpdatePosition();
	//体力減算処理関数呼び出し
	SubLife();
	//エフェクト生成処理関数呼び出し
	EffectCreate();

	//弾のタイプが火球だった時
	if (m_type == TYPE_FIREBALL)
	{
		//もしドラゴンが生きてたら
		if (CDragon::GetDeath() == false)
		{
			//目標のスケール以下の時
			if (m_fScale < 2.0f)
			{
				if (m_nCountBullet % 10 == 0)
				{
					//拡大してく
					m_fScale += 0.1f;
				}
			}
			else
			{
				//火球の発射状態を偽にする
				m_bShotFireball = true;
			}
		}
		else
		{
			m_bFireBall = false;
			m_bCharage = false;
			Uninit();
			return;
		}
		m_nCountBullet++;
	}

	if (m_type == TYPE_FLOWER)
	{
		if (m_nCount == 100)
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
					if (objType == OBJTYPE_PLAYER)
					{
						//プレイヤーの位置を取得
						D3DXVECTOR3 player_pos;
						player_pos = pScene->GetPosition();
						////目標までの距離を算出//今回は生成時のプレイヤーに向けての方向指定のみ
						D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(player_pos.x - m_pos.x, player_pos.y - m_pos.y, 0.0f);
						m_rot.y = atan2f(m_TargetDistance.y, m_TargetDistance.x);
						m_move = D3DXVECTOR3(cosf(m_rot.y)*5.5f, sinf(m_rot.y)*5.5f, 0.0f);
					}

				}
			}
		}
		m_nCount++;
	}
	//進行方向に向きを合わせる
	m_rot.z = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
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
	if (m_texture == FLOWER_TEXTURE)
	{
		SetTex(
			m_pCol * 0.1428f,
			0.0f,
			m_pCol * 0.1428f + 0.1428f,
			1.0f
		);
	}
	else
	{
		//テクスチャのセット
		SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//頂点カラー
	}
	//色のセット
	SetColor(m_col);
	//現在位置をセット
	SetPosition(m_pos);
}


//=============================================================================
// 描画関数
//=============================================================================
void CBullet::Draw(void)
{
	if(m_type == TYPE_FIRE)
	{
		CRenderer * pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		CScene2d::Draw();
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{
		CScene2d::Draw();
	}
	
}

//=============================================================================
// 衝突判定処理関数
//=============================================================================
void CBullet::Collision(void)
{
	//参照するプライオリティを設定
	int nCountPriority = 4;

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(nCountPriority, nCountScene);

		if (pScene != NULL)
		{
			//オブジェタイプの取得
			OBJTYPE objType;
			objType = pScene->GetObjType();
			//敵の位置を取得
			D3DXVECTOR3 enemy_pos;
			enemy_pos = pScene->GetPosition();
			//プレイヤーの位置を取得
			D3DXVECTOR3 player_pos;
			player_pos = pScene->GetPosition();
			//ドラゴンの位置を取得
			D3DXVECTOR3 dragon_pos;
			dragon_pos = pScene->GetPosition();

			//弾の種類によって処理を分ける
			switch (m_user)
			{
				//もし使用者がプレイヤーの場合
			case USER_PLAYER:
				//もしオブジェタイプが敵だったら
				if (objType == OBJTYPE_ENEMY || objType == OBJTYPE_BOMBENEMY)
				{
					if (m_pos.x + BULLET_SIZE / 2 > enemy_pos.x - (EYE_SIZE / 2) &&
						m_pos.x - BULLET_SIZE / 2 < enemy_pos.x + (EYE_SIZE / 2) &&
						m_pos.y + BULLET_SIZE / 2 > enemy_pos.y - (EYE_SIZE / 2) &&
						m_pos.y - BULLET_SIZE / 2 < enemy_pos.y + (EYE_SIZE / 2))
					{
						//エネミーのHIT関数呼び出し
						CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
						if (pScene != NULL)
						{
							pEnemy->Hit();
						}
						//弾の削除
						Uninit();
						return;
					}
				}
				//もしオブジェタイプがドラゴンだったら
				if (objType == OBJTYPE_DRAGON)
				{
					if (CDragon::GetSpawn() == true)
					{
						if (m_pos.x + BULLET_SIZE / 2 > dragon_pos.x - 200 &&
							m_pos.x - BULLET_SIZE / 2 < dragon_pos.x + 200 &&
							m_pos.y + BULLET_SIZE / 2 > dragon_pos.y + 100 &&
							m_pos.y - BULLET_SIZE / 2 < dragon_pos.y + 200)
						{
							//ドラゴンHIT関数呼び出し
							CDragon * pDragon = dynamic_cast<CDragon*> (pScene);
							if (pScene != NULL)
							{
								pDragon->Hit();
							}
							//弾の削除
							Uninit();
							return;
						}
					}
				}
				break;
				//弾の使用者が敵の場合
			case USER_ENEMY:
				//もしオブジェタイプがプレイヤーの場合
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.x + BULLET_SIZE / 2 > player_pos.x - (PLAYER_SIZE - 55) &&
						m_pos.x - BULLET_SIZE / 2 < player_pos.x + (PLAYER_SIZE - 55) &&
						m_pos.y + BULLET_SIZE / 2 > player_pos.y - (PLAYER_SIZE - 55) &&
						m_pos.y - BULLET_SIZE / 2 < player_pos.y + (PLAYER_SIZE - 55))
					{
						//プレイヤーのHIT関数呼び出し
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						if (pPlayer != NULL)
						{
							pPlayer->Hit();
						}

						Uninit();
						return;
					}
				}
				break;
				//弾の使用者がドラゴンの場合
			case USER_DRAGON:
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.x + BULLET_SIZE / 2 > player_pos.x - (PLAYER_SIZE - 45) &&
						m_pos.x - BULLET_SIZE / 2 < player_pos.x + (PLAYER_SIZE - 45) &&
						m_pos.y + BULLET_SIZE / 2 > player_pos.y - (PLAYER_SIZE - 45) &&
						m_pos.y - BULLET_SIZE / 2 < player_pos.y + (PLAYER_SIZE - 45))
					{
						//プレイヤーのHIT関数呼び出し
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						pPlayer->Hit();
						//弾の削除
						Uninit();
						return;
					}

				}
				break;
			default:
				break;
				return;
			}

			//弾の種類による処理分け
			switch (m_type)
			{
				//もし弾の種類が誘導弾の場合
			case TYPE_GUID:
				//オブジェタイプがプレイヤーの場合
				if (objType == OBJTYPE_PLAYER)
				{
					//目標との距離を求める
					m_fDistance = float(sqrt((player_pos.x - m_pos.x) * (player_pos.x - m_pos.x) + (player_pos.y - m_pos.y) * (player_pos.y - m_pos.y)));

					if (m_fDistance)
					{
						m_move.x = ((player_pos.x - m_pos.x) / m_fDistance * m_fSpeed);
						m_move.y = ((player_pos.y - m_pos.y) / m_fDistance * m_fSpeed);
					}
					else
					{
						m_move.x = 0;
						m_move.y = m_fSpeed;
					}
				}
				break;
				//もし弾の種類が火球の時
			case TYPE_FIREBALL:
				//移動量の追加
				m_move.x = 0.0f;
				m_move.y = 5.0f;

				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.y >= player_pos.y)
					{
						//爆発の発生
						CExplosion::Create(m_pos, 1120 - 200, FIELD_HEIGHT / 4, CExplosion::TYPE_FIERBALL);
						m_bFireBall = false;
						m_bCharage = false;
						Uninit();
						return;
					}
					m_TargetPos = pScene->GetPosition();
				}

				//もしオブジェタイプがドラゴンの時
				if (objType == OBJTYPE_DRAGON)
				{
					//火球のX座標とドラゴンのX座標を合わせる
					m_pos.x = dragon_pos.x;
					//もしブレス発射状態がtrueだったら
					if (m_bShotFireball == true)
					{
						//弾のY座標に移動量を追加
						m_pos.y += m_move.y;
						//もしブレス発射状態がfalseにする
						m_bShotFireball = false;
					}
					else
					{
						m_pos.y = dragon_pos.y + (DRAGON_SIZE_HEIGHT / 2);
					}
				}
				break;
			case TYPE_FIRE:
				if (objType == OBJTYPE_DRAGON)
				{
					m_pos.x = dragon_pos.x;

					m_move.y = 10.0f;
				}
				break;
			}
		}
	}
}

//=============================================================================
// 移動可能範囲制御処理関数関数
//=============================================================================
void CBullet::MovableRange(void)
{
	//もし弾が画面外に行ったら
	if (m_pos.y < 0 ||
		m_pos.y > FIELD_HEIGHT ||
		m_pos.x < FIELD_WIDTH_MIN ||
		m_pos.x > FIELD_WIDTH)
	{
		//弾の削除
		Uninit();
		return;
	}
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CBullet::SubLife(void)
{
	//弾のタイプが誘導弾だった時
	if (m_type == TYPE_GUID)
	{
		//ライフの減算
		m_nLife--;
		//もしライフが0以下になったとき
		if (m_nLife <= 0)
		{
			//弾の削除
			Uninit();
			return;
		}
	}
	if (m_type == TYPE_FIRE)
	{
		m_nLife--;
		if (m_nLife <= 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// 位置更新処理関数
//=============================================================================
void CBullet::UpdatePosition(void)
{
	//弾のタイプが狙い撃ち弾の時
	if (m_type == TYPE_AIM)
	{
		//位置更新
		m_pos.x += m_move.x * cosf(m_fAngle);
		m_pos.y += m_move.y * sinf(m_fAngle);
	}
	else
	{
		//位置更新
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
	}
}

//=============================================================================
// エフェクト生成処理関数
//=============================================================================
void CBullet::EffectCreate(void)
{
	//弾のタイプが通常弾の時
	if (m_type == TYPE_NORMAL)
	{
		//エフェクトの生成
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE / 2, CEffect::TYPE_PLAYER);
	}
	//弾のタイプが誘導弾だった時
	if (m_type == TYPE_GUID)
	{
		m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(255, 0, 0, 255), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	//弾のタイプがn_way弾だった時
	if (m_type == TYPE_N_WAY)
	{
		//エフェクトの生成
		m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(0, 0, 255, 255), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	//弾のタイプが狙い撃ち弾の時
	if (m_type == TYPE_AIM)
	{
		//エフェクトの生成
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	if (m_type == TYPE_BREATHE)
	{
		//エフェクトの生成
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_PLAYER);
	}
	//弾のタイプが火球だった時
	if (m_type == TYPE_FIREBALL)
	{
		//エフェクトの生成
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], (m_fWidth + 10.0f) * m_fScale, (m_fWidth + 10.0f) * m_fScale, 20, CEffect::TYPE_DRAGON);
	}
}
