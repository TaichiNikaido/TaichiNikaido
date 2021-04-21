//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/scene3d.h"
#include "player.h"
#include "Mode/mode_game.h"
#include "Effect/byte_effect.h"
#include "UI/ui.h"
#include "Base/animation.h"
#include "Effect/dust_particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/EnemyData.txt")										//スクリプトパス
#define TEXTURE_PASS ("Data//Texture//dinosaur-skin-texture-600w-256919422.png")		// テクスチャパス
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))									//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))										//サイズの初期値
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))							//衝突判定用サイズの初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))									//回転の初期値
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))										//移動量の初期値
#define MINIMUM_TIME (0)																//時間の初期値
#define INITIAL_MOVE_SPEED (0.0f)														//移動速度の初期値
#define BYTE_POS_1	(D3DXVECTOR3(-400,200.0f,PlayerPos.z))								//攻撃エフェクト位置
#define BYTE_POS_2	(D3DXVECTOR3(-600,200.0f,PlayerPos.z))								//攻撃エフェクト位置
#define BYTE_POS_3	(D3DXVECTOR3(-800,200.0f,PlayerPos.z))								//攻撃エフェクト位置
#define BYTE_SIZE	(D3DXVECTOR3(300.0f,500.0f,0.0f))									//攻撃エフェクトサイズ
#define WARNING_MARK_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2,150.0f,0.0f))					//位置
#define WARNING_MARK_SIZE	(D3DXVECTOR3(200.0f,200.0f,0.0f))							//サイズ
#define ATTACL_MOTIONCOUNT	(95)														//アタックモーション
#define ATTACK_COUNT		(120)														//攻撃カウント
#define ATTACK1_RANGE_MIN	(-400)														//攻撃1の最小値
#define ATTACK1_RANGE_MAX	(-580)														//攻撃1の最大値
#define ATTACK2_RANGE_MIN	(-580)														//攻撃2の最小値
#define ATTACK2_RANGE_MAX	(-780)														//攻撃2の最大値
#define ATTACK3_RANGE_MIN	(-780)														//攻撃3の最小値
#define ATTACK3_RANGE_MAX	(-980)														//攻撃3の最大値
#define STEP_SIZE			(200.0f)													//踏みつぶしのサイズ

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[PARTS_MAX] = {};
LPD3DXMESH CEnemy::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[PARTS_MAX] = {};
DWORD CEnemy::m_nNumMat[PARTS_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
	m_Size = INITIAL_SIZE;							//サイズ
	m_Move = INITIAL_MOVE;							//移動量
	m_ContinuePosition = INITIAL_POSITION;			//コンティニューするポジション
	m_nMeatEatTime = MINIMUM_TIME;					//肉を食べる時間
	m_nMeatEatTimeCount = MINIMUM_TIME;				//肉を食べる時間のカウント
	m_nAttackCoolTime = MINIMUM_TIME;				//攻撃のクールタイム
	m_nAttackCoolTimeCount = MINIMUM_TIME;			//攻撃のクールタイムのカウント
	m_fAutoRunSpeed = INITIAL_MOVE_SPEED;			//オートランの速度
	m_bEat = false;									//食事をしているか
	m_bAttack = false;								//攻撃をしたか
	m_bStop = false;								//停止するか
	m_bContinue = false;							//コンティニューするか
	m_bContinuePositionSave = false;				//コンティニューする位置を保存するか
	Attack_Type = ATTACK_TYPE_NONE;					//攻撃の種類
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}
//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プレイヤー1
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/00_Waist.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_WAIST], NULL, &m_nNumMat[PARTS_WAIST], &m_pMesh[PARTS_WAIST]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/01_Body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_BODY], NULL, &m_nNumMat[PARTS_BODY], &m_pMesh[PARTS_BODY]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/02_Head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_HEAD], NULL, &m_nNumMat[PARTS_HEAD], &m_pMesh[PARTS_HEAD]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/03_RightArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RARM], NULL, &m_nNumMat[PARTS_RARM], &m_pMesh[PARTS_RARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/04_LeftArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LARM], NULL, &m_nNumMat[PARTS_LARM], &m_pMesh[PARTS_LARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/05_RightLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RLEG], NULL, &m_nNumMat[PARTS_RLEG], &m_pMesh[PARTS_RLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/06_RightShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RSHOE], NULL, &m_nNumMat[PARTS_RSHOE], &m_pMesh[PARTS_RSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/07_LeftLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LLEG], NULL, &m_nNumMat[PARTS_LLEG], &m_pMesh[PARTS_LLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/08_LeftShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LSHOE], NULL, &m_nNumMat[PARTS_LSHOE], &m_pMesh[PARTS_LSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/09_MainTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_MAINTAIL], NULL, &m_nNumMat[PARTS_MAINTAIL], &m_pMesh[PARTS_MAINTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/10_SubTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_SUBTAIL], NULL, &m_nNumMat[PARTS_SUBTAIL], &m_pMesh[PARTS_SUBTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/11_EndTail.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_ENDTAIL], NULL, &m_nNumMat[PARTS_ENDTAIL], &m_pMesh[PARTS_ENDTAIL]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/enemy/12_Chin.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_CHIN], NULL, &m_nNumMat[PARTS_CHIN], &m_pMesh[PARTS_CHIN]);

	//LoadTexture();
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PASS, &m_apTexture[TEX_TYPE_1]);

	return S_OK;
}

//=============================================================================
// ロードテクスチャ
//=============================================================================
HRESULT CEnemy::LoadTexture(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ分回す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture[nCount])))
				{
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt]= NULL;
		}
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CEnemy * CEnemy::Create(void)
{
	//敵のポインタ
	CEnemy * pEnemy = NULL;
	//敵のポインタがNULLの場合
	if (pEnemy == NULL)
	{
		//敵のメモリ確保
		pEnemy = new CEnemy;
		//敵のポインタがNULLではない場合
		if (pEnemy != NULL)
		{
			//敵の初期化処理関数呼び出し
			pEnemy->Init();
		}
	}
	//敵のポインタを返す
	return pEnemy;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//スクリプトデータ読み込み関数
	DataLoad();
	// パーツ数を設定
	SetPartNum(PARTS_MAX);
	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		BindMesh(CAnimation::TYPE_ENEMY, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);

		BindTexture(m_apTexture[TEX_TYPE_1], nCount);
	}
	// 座標・親子関係の読み込み
	LoadModelData("./Data/text/motion_enemy.txt");
	//キャラクターの初期化処理関数呼び出し
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit()
{
	//キャラクターの終了処理関数呼び出し
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update()
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//キャラクターの更新処理関数呼び出し
	CCharacter::Update();
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();
	D3DXVECTOR3 pos = GetPos();
	if (m_bStop == false)
	{
		//オートラン処理関数呼び出し
		AutoRun();
		CDust_Particle::SandDust_Create(pos);
		// 踏む処理
		Step();
	}
	//もしコンティニューしたら
	if (m_bContinue == true)
	{
		//コンティニュー処理関数呼び出し
		Continue();

	}
	//もし攻撃をしていない場合
	if (m_bAttack == false)
	{
		//攻撃のクールタイムを加算する
		m_nAttackCoolTimeCount++;
		
		//もしクールタイムが終わったら
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime)
		{
			// 危険マーク生成
			Warning_Create();
		}
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime + ATTACL_MOTIONCOUNT)
		{
			pAnimation->SetAnimation(MOTION_ATTACK);
		}
		if (m_nAttackCoolTimeCount == m_nAttackCoolTime + ATTACK_COUNT)
		{
			//もしプレイヤーのポインタがNULLじゃない場合
			if (pPlayer != NULL)
			{
				//もしプレイヤーの状態が死亡状態じゃない場合
				if (pPlayer->GetState() != CPlayer::STATE_DEATH)
				{
					// 攻撃処理
					Attack();
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//キャラクターの描画処理関数呼び出し
	CCharacter::Draw();
}

//=============================================================================
// オートラン処理関数
//=============================================================================
void CEnemy::AutoRun(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();
	//もし食事中だったら
	if (m_bEat == true)
	{
		//もしカウントが食事時間以下の場合
		if (m_nMeatEatTimeCount <= m_nMeatEatTime)
		{
			//移動量を0にする
			m_Move = INITIAL_MOVE;
			pAnimation->SetAnimation(MOTION_MEAL);
			//食事カウントを加算する
			m_nMeatEatTimeCount++;
		}
		else
		{
			//食事をやめる
			m_bEat = false;
			//食事カウントを0にする
			m_nMeatEatTimeCount = MINIMUM_TIME;
			pAnimation->SetAnimation(MOTION_DUSH);
			//移動させる
			m_Move.z = m_fAutoRunSpeed;
		}
	}
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//プレイヤーのポインタがNULLではない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPos();

		//もし位置が一定以上離れたら
		if (Position.z < PlayerPosition.z - 800.0f)
		{
			//位置を補正する
			Position.z = PlayerPosition.z - 800.0f;
		}
	}
	//位置更新
	Position += m_Move;
	//もしコンティニューする位置を保存するなら
	if (m_bContinuePositionSave == true)
	{
		//コンティニューする位置を保存する
		m_ContinuePosition = Position;
	}
	//位置を設定する
	SetPos(Position);
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemy::Attack(void)
{
	// プレイヤー取得
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// プレイヤー位置
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();
	//攻撃をする
	m_bAttack = true;
	//クールタイムを0にする
	m_nAttackCoolTimeCount = MINIMUM_TIME;
	// ATTACK_TYPE_1の場合
	if (Attack_Type == ATTACK_TYPE_1)
	{
		// プレイヤーに攻撃をする
		CByte_Effect::ByteEffect_Create(BYTE_POS_1, BYTE_SIZE);

		// プレイヤーの位置が範囲内の場合
		if (PlayerPos.x <= ATTACK1_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
		{
			// ヒット
			pPlayer->Hit();
		}
		// 攻撃をやめる
		m_bAttack = false;
	}
	// ATTACK_TYPE_2の場合
	if (Attack_Type == ATTACK_TYPE_2)
	{
		// プレイヤーに攻撃をする
		CByte_Effect::ByteEffect_Create(BYTE_POS_2, BYTE_SIZE);

		// プレイヤーの位置が範囲内の場合
		if (PlayerPos.x <= ATTACK2_RANGE_MIN && PlayerPos.x > ATTACK2_RANGE_MAX)
		{
			// ヒット
			pPlayer->Hit();
		}

		// 攻撃をやめる
		m_bAttack = false;
	}
	// ATTACK_TYPE_3の場合
	if (Attack_Type == ATTACK_TYPE_3)
	{
		// プレイヤーに攻撃をする
		CByte_Effect::ByteEffect_Create(BYTE_POS_3, BYTE_SIZE);

		// プレイヤーの位置が範囲内の場合
		if (PlayerPos.x <= ATTACK3_RANGE_MIN && PlayerPos.x > ATTACK3_RANGE_MAX)
		{
			// ヒット
			pPlayer->Hit();
		}

		// 攻撃をやめる
		m_bAttack = false;
	}
}

//=============================================================================
// 危険マーク生成処理関数
//=============================================================================
void CEnemy::Warning_Create(void)
{
	// プレイヤー取得
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// プレイヤー位置
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// 範囲内の場合
	if (PlayerPos.x <= ATTACK1_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
	{
		// 攻撃タイプ
		Attack_Type = ATTACK_TYPE_1;
	}
	// 範囲内の場合
	if (PlayerPos.x <= ATTACK2_RANGE_MIN && PlayerPos.x > ATTACK2_RANGE_MAX)
	{
		// 攻撃タイプ
		Attack_Type = ATTACK_TYPE_2;
	}
	// 範囲内の場合
	if (PlayerPos.x <= ATTACK3_RANGE_MIN && PlayerPos.x > ATTACK1_RANGE_MAX)
	{
		// 攻撃タイプ
		Attack_Type = ATTACK_TYPE_3;
	}
	// 危険マーク
	CUi::Create(WARNING_MARK_POS, WARNING_MARK_SIZE, CUi::UITYPE_WARNING);
}

//=============================================================================
// プレイヤーを踏む処理関数
//=============================================================================
void CEnemy::Step(void)
{
	// プレイヤー取得
	CPlayer *pPlayer = CGameMode::GetPlayer();
	// プレイヤー位置
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// プレイヤーの位置が敵の位置より低くなった場合
	if (PlayerPos.z <= pos.z - STEP_SIZE)
	{
		// ヒット
		pPlayer->Death();
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemy::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// コンティニュー処理関数
//=============================================================================
void CEnemy::Continue(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//コンティニューする位置に設定する
	Position = m_ContinuePosition;
	//位置を設定する
	SetPos(Position);
	//攻撃時間を初期化する
	m_nAttackCoolTimeCount = MINIMUM_TIME;
	//攻撃状態を止める
	m_bAttack = false;
	//コンティニューをやめる
	m_bContinue = false;
	//停止をやめる
	m_bStop = false;
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CEnemy::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_POSITION;	//位置
	D3DXVECTOR3 CollisionSize = INITIAL_SIZE;	//サイズ
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;	//回転
	char aReadText[MAX_TEXT];					//読み込んだテキスト
	char aCurrentText[MAX_TEXT];				//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];			//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルの読み込み
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//ファイルを開くことができたら
	if (pFile != NULL)
	{
		//SCRIPTの文字を見つける
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			//読み込んだテキストを格納する
			fgets(aReadText, sizeof(aReadText), pFile);
			//読み込んだテキストを現在のテキストに格納
			sscanf(aReadText, "%s", &aCurrentText);
		}
		//現在のテキストがSCRIPTだったら
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			//END_SCRIPTの文字が見つかるまで読む
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				//読み込んだテキストを格納する
				fgets(aReadText, sizeof(aReadText), pFile);
				//読み込んだテキストを現在のテキストに格納
				sscanf(aReadText, "%s", &aCurrentText);
				//現在のテキストがPARAMETER_SETだったら
				if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
				{
					//END_PARAMETER_SETの文字が見つかるまで読む
					while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
					{
						//読み込んだテキストを格納する
						fgets(aReadText, sizeof(aReadText), pFile);
						//読み込んだテキストを現在のテキストに格納
						sscanf(aReadText, "%s", &aCurrentText);
						//現在のテキストがPOSだったら
						if (strcmp(aCurrentText, "POS") == 0)
						{
							//位置情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//コンティニューする位置を設定する
							m_ContinuePosition = Position;
							//位置を設定する
							SetPos(Position);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//現在のテキストがCOLLISION_SIZEだったら
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//衝突判定用サイズの読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
						}
						//現在のテキストがROTだったら
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//回転の設定
							SetRot(D3DXToRadian(Rotation));
						}
						//現在のテキストがMeatEatTimeだったら
						if (strcmp(aCurrentText, "MeatEatTime") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMeatEatTime);
						}
						//現在のテキストがAttackCoolTimeだったら
						if (strcmp(aCurrentText, "AttackCoolTime") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nAttackCoolTime);
						}
						//現在のテキストがAutoRunSpeedだったら
						if (strcmp(aCurrentText, "AutoRunSpeed") == 0)
						{
							//サイズの設定
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAutoRunSpeed);
							//移動量の設定
							m_Move.z = m_fAutoRunSpeed;
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}