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
#include "scene3d.h"
#include "model.h"
#include "motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

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
	CModel * GetModel(int nParts) { return m_pModel[nParts]; }
	CMotion * GetpMotion(void) { return m_pMotion; }
private:
	const char * m_apModelScriptPass[32];					//���f���̃X�N���v�g�p�X
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];				//���f���f�[�^
	CMotion * m_pMotion;									//���[�V�����̃|�C���^
	CModel * m_pModel[MAX_PARTS];							//���f���̃|�C���^
};
#endif
