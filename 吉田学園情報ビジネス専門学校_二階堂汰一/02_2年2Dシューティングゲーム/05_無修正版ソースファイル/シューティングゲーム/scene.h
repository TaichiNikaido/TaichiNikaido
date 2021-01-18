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
#define MAX_SCENE 2056
#define PRIORITY_MAX 10
#define PRIORITY_DEFAULT 3
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = -1,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_DRAGON,
		OBJTYPE_BULLET,
		OBJTYPE_FIREBALL,
		OBJTYPE_FIRE,
		OBJTYPE_BOMB,
		OBJTYPE_ITEM,
		OBJTYPE_WORMHOLE,
		OBJTYPE_BOMBENEMY,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int GetNumAll(void);
	void SetObjType(OBJTYPE pbjType);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

	OBJTYPE GetObjType(void);
	static CScene * GetScene(int nPriority,int nCnt);
protected:
	void Release(void);
private:
	static CScene * m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;
	OBJTYPE m_objType;//オブジェクトの種類
	D3DXVECTOR3 m_pos;
	int m_nPriority;
};
#endif