//=============================================================================
//
// モーション [motion.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_POSITON (D3DXVECTOR3(0.0f,0.0f,0.0f))				//位置の初期値
#define INITIAL_POSITION_ORIGINAL (D3DXVECTOR3(0.0f,0.0f,0.0f))		//初期位置の初期値
#define INITIAL_POSITION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置の差分の初期値
#define INITIAL_DIRECTION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//向きの差分の初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//回転の初期値
#define INITIAL_ROTATION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//回転の差分の初期値
#define INITIAL_INDEX (0)											//モデル番号の初期値
#define INITIAL_PARENTS (0)											//モデルの親番号
#define INITIAL_NUMKEY (0)											//モーションキー数の初期値
#define INITIAL_FLAME (0)											//フレーム数の初期値
#define INITIAL_CURRENT_KEY (1)										//現在のキー数
#define INITIAL_ADD_CHANGE_FLAME (1)								//モーション変更時に加算するフレーム

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMotion::CMotion()
{
	m_MotionState = MOTION_IDLE;					//モーション状態
	m_MotionOldState = MOTION_IDLE;					//古いモーション状態
	m_nAddChangeFreme = INITIAL_ADD_CHANGE_FLAME;	//モーション変更時に加算するフレーム
	m_nFrame = INITIAL_FLAME;						//フレーム数
	m_nCurrentKey = INITIAL_CURRENT_KEY;			//現在のキー数
	m_bChange = false;								//変更したか
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_ModelParent[nCount].nIndex = INITIAL_INDEX;							//モデル番号
		m_ModelParent[nCount].nParents = INITIAL_PARENTS;						//モデルの親番号
		m_ModelParent[nCount].Position = INITIAL_POSITON;						//位置		
		m_ModelParent[nCount].PositionOrigin = INITIAL_POSITION_ORIGINAL;		//初期位置
		m_ModelParent[nCount].Rotation = INITIAL_ROTATION;						//回転
		m_NumPositionDifference[nCount] = INITIAL_POSITION_DIFFERENCE;			//位置の差分
		m_NumDirectionDifference[nCount] = INITIAL_DIRECTION_DIFFERENCE;		//向きの差分
		m_NumRotationDifference[nCount] = INITIAL_ROTATION_DIFFERENCE;			//回転の差分
	}
	//モーションの最大数分回す
	for (int nCountMotion = 0; nCountMotion < MOTION_MAX; nCountMotion++)
	{
		m_Motion[nCountMotion].bLoop = false;				//ループするか
		m_Motion[nCountMotion].nNumKey = INITIAL_NUMKEY;	//モーションキー数
		//モーションキーの最大数
		for (int nCountKey = 0; nCountKey < MOTIONKEY_SET_MAX; nCountKey++)
		{
			m_Motion[nCountMotion].KeyInformation[nCountKey].nFrame = INITIAL_FLAME;	//フレーム数
			//パーツの最大数分回す
			for (int nCountParts = 0; nCountParts < MAX_PARTS; nCountParts++)
			{
				m_Motion[nCountMotion].KeyInformation[nCountKey].Position[nCountParts] = INITIAL_POSITON;	//位置
				m_Motion[nCountMotion].KeyInformation[nCountKey].Rotation[nCountParts] = INITIAL_ROTATION;	//回転
			}
		}
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CMotion::~CMotion()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CMotion * CMotion::Create(void)
{
	//モーションのポインタ
	CMotion * pMotion = NULL;
	//もしモーションのポインタがNULLの場合
	if (pMotion == NULL)
	{
		//モーションのメモリ確保
		pMotion = new CMotion;
	}
	//モーションのポインタを返す
	return pMotion;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CMotion::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CMotion::Update(void)
{
	// モーションが1フレーム前のモーションと違ったら
	if (m_MotionOldState != m_MotionState)
	{
		m_nFrame = 0;
		m_nCurrentKey = 0;
	}
	for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
	{
		//フレーム開始時に、変更後の回転の値や位置の値などを設定
		if (m_nFrame == 0)
		{
			m_NumPositionDifference[nCntMotion] = ((m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].Position[nCntMotion] -
				(m_ModelParent[nCntMotion].Position - m_ModelParent[nCntMotion].PositionOrigin)) / float(m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame));

			m_NumDirectionDifference[nCntMotion] = m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].Rotation[nCntMotion] - m_ModelParent[nCntMotion].Rotation;

			m_NumRotationDifference[nCntMotion] = (m_NumDirectionDifference[nCntMotion] / float(m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame));
		}
		// 変更後の回転の値や位置の値を加算
		m_ModelParent[nCntMotion].Position += m_NumPositionDifference[nCntMotion];
		m_ModelParent[nCntMotion].Rotation += m_NumRotationDifference[nCntMotion];

		if (m_ModelParent[nCntMotion].Rotation.x >= D3DXToRadian(180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.x = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.x <= D3DXToRadian(-180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.x = D3DXToRadian(180.0f);
			m_bChange = true;
		}

		if (m_ModelParent[nCntMotion].Rotation.y >= D3DXToRadian(180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.y = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.y <= D3DXToRadian(-180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.y = D3DXToRadian(180.0f);
			m_bChange = true;
		}

		if (m_ModelParent[nCntMotion].Rotation.z >= D3DXToRadian(180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.z = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.z <= D3DXToRadian(-180.0f) && m_bChange == false)//一定の値を超えると回らなくなるので減算していく
		{
			m_ModelParent[nCntMotion].Rotation.z = D3DXToRadian(180.0f);
			m_bChange = true;
		}
	}
	// 現在のモーションの記録
	m_MotionOldState = m_MotionState;
	// ループするとき
	if (m_nFrame >= m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame && m_Motion[m_MotionState].bLoop == 1)
	{
		m_nFrame = 0;
		m_bChange = false;
		m_nCurrentKey++;
		// キーが記録されているキーより大きくなったら
		if (m_nCurrentKey >= m_Motion[m_MotionState].nNumKey)
		{
			m_nCurrentKey = 0;
		}
	}
	// ループしないとき
	else if (m_nFrame >= m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame && m_Motion[m_MotionState].bLoop == 0)
	{
		m_nFrame = 0;
		m_bChange = false;
		m_nCurrentKey++;

		// キーが記録されているキーより大きくなったら
		if (m_nCurrentKey >= m_Motion[m_MotionState].nNumKey)
		{
			for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
			{
				m_NumPositionDifference[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_NumRotationDifference[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_nCurrentKey = 0;
			m_MotionState = MOTION_IDLE;
		}
	}
	else
	{
		m_nFrame += m_nAddChangeFreme;
	}
}

//=============================================================================
// モーション読み込み関数
//=============================================================================
void CMotion::LoadMotion(const char * cText)
{
	int  nCntLoad = 0;				//読み込んだカウント
	int	 nCntKey = 0;				//キーの数のカウント
	int	 nCntMotion = 0;			//モーションの数のカウント
	char aReadText[MAX_TEXT];		//文字として読み取り用
	char aCurrentText[MAX_TEXT];	//文字の判別用
	char aDie[MAX_TEXT];			//使わない文字
	//ファイルのポインタ
	FILE * pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");
	}
	//もしファイルのポインタがNULLじゃない場合
	if (pFile != NULL)
	{
		//SCRIPTの文字が見つかるまで
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			//テキストからaReadText分文字を読み込む
			fgets(aReadText, sizeof(aReadText), pFile);
			//読み込んだ文字ををaCurrentTextに格納
			sscanf(aReadText, "%s", &aCurrentText);
		}
		//aCurrentTextがSCRIPTだったら
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			//END_SCRIPTの文字が見つかるまで
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				//テキストからaReadText分文字を読み込む
				fgets(aReadText, sizeof(aReadText), pFile);
				// 読み込んだ文字ををaCurrentTextに格納
				sscanf(aReadText, "%s", &aCurrentText);

				//aCurrentTextがMOTIONSETだったら
				if (strcmp(aCurrentText, "MOTIONSET") == 0)
				{
					//END_MOTIONSETの文字が見つかるまで
					while (strcmp(aCurrentText, "END_MOTIONSET") != 0)
					{
						//テキストからaReadText分文字を読み込む
						fgets(aReadText, sizeof(aReadText), pFile);
						//読み込んだ文字ををaCurrentTextに格納
						sscanf(aReadText, "%s", &aCurrentText);

						//aCurrentTextがMOTIONSETだったら
						if (strcmp(aCurrentText, "LOOP") == 0)
						{
							//m_nLoopにループをするか格納
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, (int *)&m_Motion[nCntMotion].bLoop);
						}

						//aCurrentTextがNUM_KEYだったら
						if (strcmp(aCurrentText, "NUM_KEY") == 0)
						{
							//m_nNumKeyにキーの数を格納
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_Motion[nCntMotion].nNumKey);
						}

						//aCurrentTextがKEYSETだったら
						if (strcmp(aCurrentText, "KEYSET") == 0)
						{
							//END_KEYSETの文字が見つかるまで
							while (strcmp(aCurrentText, "END_KEYSET") != 0)
							{
								//テキストからaReadText分文字を読み込む
								fgets(aReadText, sizeof(aReadText), pFile);
								//読み込んだ文字ををaCurrentTextに格納
								sscanf(aReadText, "%s", &aCurrentText);

								//aCurrentTextがFRAMEだったら
								if (strcmp(aCurrentText, "FRAME") == 0)
								{
									//m_nFrameにフレーム数を格納
									sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_Motion[nCntMotion].KeyInformation[nCntKey].nFrame);
								}
								//aCurrentTextがKEYだったら
								if (strcmp(aCurrentText, "KEY") == 0)
								{
									//END_KEYの文字が見つかるまで
									while (strcmp(aCurrentText, "END_KEY") != 0)
									{
										//テキストからaReadText分文字を読み込む
										fgets(aReadText, sizeof(aReadText), pFile);
										//読み込んだ文字ををaCurrentTextに格納
										sscanf(aReadText, "%s", &aCurrentText);

										//aCurrentTextがPOSだったら
										if (strcmp(aCurrentText, "POS") == 0)
										{
											//m_posに座標を格納
											sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].x,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].y,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].z);
										}
										//aCurrentTextがROTだったら
										if (strcmp(aCurrentText, "ROT") == 0)
										{
											//m_rotに回転を格納
											sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].x,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].y,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].z);
										}
									}
									//カウントの加算
									nCntLoad++;
								}
							}
							//読み込んだカウントの初期化
							nCntLoad = 0;
							//カウントの加算
							nCntKey++;
						}
					}
					//キーの数の初期化
					nCntKey = 0;
					//カウントの加算
					nCntMotion++;
				}
			}
			//ファイルを閉じる
			fclose(pFile);
		}
	}
}

//=============================================================================
// モデル情報読み込み関数
//=============================================================================
void CMotion::LoadModelInformation(const char * cText)
{
	int  nCntLoad = 0;				//読み込んだカウント
	char aReadText[MAX_TEXT];		//文字として読み取り用
	char aCurrentText[MAX_TEXT];	//文字の判別用
	char aDie[MAX_TEXT];			//使わない文字
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルがNULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");
	}
	//もしファイルがNULLじゃない場合
	if (pFile != NULL)
	{
		// CHARACTERSETの文字が見つかるまで
		while (strcmp(aCurrentText, "CHARACTERSET") != 0)
		{
			// テキストからaReadText分文字を受け取る
			fgets(aReadText, sizeof(aReadText), pFile);
			// aReadTextをaCurrentTextに格納
			sscanf(aReadText, "%s", &aCurrentText);
		}

		// aCurrentTextがCHARACTERSETの時
		if (strcmp(aCurrentText, "CHARACTERSET") == 0)
		{
			// aCurrentTextがEND_CHARACTERSETになるまで
			while (strcmp(aCurrentText, "END_CHARACTERSET") != 0)
			{
				// テキストからaReadText分文字を受け取る
				fgets(aReadText, sizeof(aReadText), pFile);
				// aReadTextをaCurrentTextに格納
				sscanf(aReadText, "%s", &aCurrentText);

				// aCurrentTextが改行の時
				if (strcmp(aCurrentText, "\n") == 0)
				{
				}
				// aCurrentTextがPARTSSETの時
				else if (strcmp(aCurrentText, "PARTSSET") == 0)
				{
					// aCurrentTextがEND_PARTSSETになるまで
					while (strcmp(aCurrentText, "END_PARTSSET") != 0)
					{
						// テキストからaReadText分文字を受け取る
						fgets(aReadText, sizeof(aReadText), pFile);
						// aReadTextをaCurrentTextに格納
						sscanf(aReadText, "%s", &aCurrentText);

						// aCurrentTextがINDEXになるまで
						if (strcmp(aCurrentText, "INDEX") == 0)
						{
							// テキストのINDEXの値をm_nIndexに格納
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_ModelParent[nCntLoad].nIndex);
						}

						// aCurrentTextがPARENTになるまで
						if (strcmp(aCurrentText, "PARENT") == 0)
						{
							// テキストのPARENTの値をm_nParentsに格納
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_ModelParent[nCntLoad].nParents);
						}

						// aCurrentTextがPOSになるまで
						if (strcmp(aCurrentText, "POS") == 0)
						{
							// テキストのPOSの値をm_posOriginに格納
							sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
								&m_ModelParent[nCntLoad].PositionOrigin.x,
								&m_ModelParent[nCntLoad].PositionOrigin.y,
								&m_ModelParent[nCntLoad].PositionOrigin.z);

							// m_posOriginの値をm_posに代入
							m_ModelParent[nCntLoad].Position = m_ModelParent[nCntLoad].PositionOrigin;
						}

						// aCurrentTextがROTになるまで
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							// テキストのROTの値をm_rotに格納
							sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
								&m_ModelParent[nCntLoad].Rotation.x,
								&m_ModelParent[nCntLoad].Rotation.y,
								&m_ModelParent[nCntLoad].Rotation.z);
						}
					}
					// カウント加算
					nCntLoad++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}
