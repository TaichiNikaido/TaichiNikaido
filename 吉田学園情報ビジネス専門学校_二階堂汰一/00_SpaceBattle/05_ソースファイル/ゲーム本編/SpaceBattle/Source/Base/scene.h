//=============================================================================
//
// 描画処理 [scene.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE (2056)		//シーンの最大数
#define DEFAULT_PRIORITY (4)	//基準のプライオリティー

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJECT_TYPE_NONE = -1,
		OBJECT_TYPE_ENEMY,		//敵
		OBJECT_TYPE_FIRE_BALL,	//火球
		OBJECT_TYPE_MAX
	}OBJECT_TYPE;
	typedef enum
	{
		PRIORITY_NONE = -1,
		PRIORITY_BG,			//背景
		PRIORITY_BULLET,		//弾
		PRIORITY_ENEMY,			//敵
		PRIORITY_EXPLOSION,		//爆発
		PRIORITY_ITEM,			//アイテム
		PRIORITY_PLAYER,		//プレイヤー
		PRIORITY_UI,			//UI
		PRIORITY_FLAME,			//枠
		PRIORITY_LOGO,			//ロゴ
		PRIORITY_BUTTON,		//ボタン
		PRIORITY_MAX
	}PRIORITY;
	CScene(int nPriority = DEFAULT_PRIORITY);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int GetNumAll(void) { return m_nNumAll; }
	void SetObjectType(OBJECT_TYPE ObjectType) { m_ObjectType = ObjectType; }
	void SetbPause(bool bPause) { m_bPause = bPause; }
	OBJECT_TYPE GetObjectType(void) { return m_ObjectType; }
	static CScene * GetScene(int nPriority, int nCnt) { return m_apScene[nPriority][nCnt]; }
protected:
	void Release(void);
private:
	static CScene * m_apScene[PRIORITY_MAX][MAX_SCENE];		//シーンのポインタ
	static int m_nNumAll;									//シーンの総数
	int m_nPriority;										//プライオリティー
	int m_nID;												//現在のシーン
	OBJECT_TYPE m_ObjectType;								//オブジェクトの種類
	static bool m_bPause;									//ポーズの使用状態

};
#endif