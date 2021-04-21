//=============================================================================
//
// �V�[���Ǘ� [scene.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE (2056)
#define DEFAULT_PRIORITY (4)

//*****************************************************************************
// �N���X��`
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
	static CScene * m_apScene[MAX_SCENE];	//�V�[���̃|�C���^
	static int m_nNumAll;					//����
	int m_nID;								//���݂�ID
};
#endif