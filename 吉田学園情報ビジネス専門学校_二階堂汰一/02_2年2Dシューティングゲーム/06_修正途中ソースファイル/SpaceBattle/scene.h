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
#define MAX_SCENE (2056)
#define PRIORITY_MAX (10)
#define DEFAULT_PRIORITY (4)
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
		OBJTYPE_BULLET,
		OBJTYPE_ITEM,
		OBJTYPE_BACKGROUND,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene(int nPriority = DEFAULT_PRIORITY);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int GetNumAll(void);
	void SetObjType(OBJTYPE pbjType);
	OBJTYPE GetObjType(void);
	static CScene * GetScene(int nPriority, int nCnt);
protected:
	void Release(void);
private:
	static CScene * m_apScene[PRIORITY_MAX][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;
	OBJTYPE m_objType;//オブジェクトの種類
	D3DXVECTOR3 m_Position;
	int m_nPriority;
};
#endif