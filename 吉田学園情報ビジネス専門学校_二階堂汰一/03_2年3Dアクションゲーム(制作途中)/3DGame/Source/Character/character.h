//=============================================================================
//
// �L�����N�^�[ [character.h]
// Author : ��K������
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene3d.h"
#include "Base/model.h"
#include "Base/motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CShadow;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharacter : public CScene3d
{
public:
	CCharacter();
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetModelScriptPass(const char * pModelScriptPass) { m_apModelScriptPass[0] = pModelScriptPass; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	CModel * GetModel(int nParts) { return m_apModel[nParts]; }
	CMotion * GetpMotion(void) { return m_pMotion; }
private:
	void ShadowCreate(void);
	const char * m_apModelScriptPass[MAX_PASS_LETTER];		//���f���̃X�N���v�g�p�X
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];				//���f���f�[�^
	CModel * m_apModel[MAX_PARTS];							//���f���̃|�C���^
	CMotion * m_pMotion;									//���[�V�����̃|�C���^
	CShadow * m_pShadow;									//�e�̃|�C���^
};
#endif
