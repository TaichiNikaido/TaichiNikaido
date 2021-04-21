//=============================================================================
//
// シーン管理 [scene.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE (2056)
#define DEFAULT_PRIORITY (4)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	CScene();
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static CScene * GetScene(int nCount){ return m_apScene[nCount]; }
protected:
	void Release(void);
private:
	static CScene * m_apScene[MAX_SCENE];	//シーンのポインタ
	static int m_nNumAll;					//総数
	int m_nID;								//現在のID
};
#endif