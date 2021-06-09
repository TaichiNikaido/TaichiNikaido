//=============================================================================
//
// ドラゴン [enemy_draogn.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_DRAGON_H_
#define _ENEMY_DRAGON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDragon : public CEnemy
{
public:
	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_ROAR
	}MOTION;
	typedef enum
	{
		ATTACK_NONE = -1,
		ATTACK_BITING,
		ATTACK_2,
		ATTACK_3,
		ATTACK_MAX
	}ATTACK_PATTERN;
	CDragon();
	~CDragon();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CDragon * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void AI(void);
	bool Biting(void);
	bool Visibility(void);
	void Death(void);
	static CModel::MODEL_DATA m_aModelData[MAX_PARTS];	//モデルデータ
	bool m_bGameClearLogoCreate;						//ゲームクリアロゴを生成したか
	ATTACK_PATTERN m_AttackPattern;						//攻撃パターン
};
#endif
