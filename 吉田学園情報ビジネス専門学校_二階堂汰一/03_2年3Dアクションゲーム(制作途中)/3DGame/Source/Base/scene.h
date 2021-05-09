//=============================================================================
//
// �`�揈�� [scene.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE (2056)		//�V�[���̍ő吔
#define DEFAULT_PRIORITY (4)	//��̃v���C�I���e�B�[

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJECT_TYPE_NONE = -1,
		OBJECT_TYPE_CHARACTER,
		OBJECT_TYPE_MAX
	}OBJECT_TYPE;	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		PRIORITY_NONE = -1,
		PRIORITY_BASE,
		PRIORITY_CHARACTER,
		PRIORITY_WEAPON,
		PRIORITY_UI,
		PRIORITY_BUTTON,
		PRIORITY_2DPOLYGON,
		PRIORITY_MAX
	}PRIORITY;
	CScene(int nPriority = PRIORITY_CHARACTER);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int GetNumAll(void) { return m_nNumAll; }
	static void SetbPause(bool bPause) { m_bPause = bPause; }
	void SetObjectType(OBJECT_TYPE ObjectType) { m_ObjectType = ObjectType; }
	OBJECT_TYPE GetObjectType(void) { return m_ObjectType; }
	static CScene * GetScene(int nPriority, int nCnt) { return m_apScene[nPriority][nCnt]; }
protected:
	void Release(void);
private:
	static CScene * m_apScene[PRIORITY_MAX][MAX_SCENE];		//�V�[���̃|�C���^
	static int m_nNumAll;									//�V�[���̑���
	int m_nPriority;										//�v���C�I���e�B�[
	int m_nID;												//���݂̃V�[��
	static bool m_bPause;									//�|�[�Y�̎g�p���
	OBJECT_TYPE m_ObjectType;								//�I�u�W�F�N�g�̎��
};
#endif