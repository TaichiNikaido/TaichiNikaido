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
	CCharacter(int nPriority = PRIORITY_CHARACTER);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetModelScriptPass(const char * pModelScriptPass) { m_apModelScriptPass[0] = pModelScriptPass; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	CModel * GetModel(int nParts) { return m_apModel[nParts]; }
	CMotion * GetpMotion(void) { return m_pMotion; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
private:
	void ShadowCreate(void);
	const char * m_apModelScriptPass[MAX_PASS_LETTER];		//���f���̃X�N���v�g�p�X
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];				//���f���f�[�^
	D3DXVECTOR3 m_PositionOld;								//�ߋ��̈ʒu
	D3DXVECTOR3 m_CollisionSize;							//�Փ˔���p�̃T�C�Y
	CModel * m_apModel[MAX_PARTS];							//���f���̃|�C���^
	CMotion * m_pMotion;									//���[�V�����̃|�C���^
	//CShadow * m_pShadow;									//�e�̃|�C���^
};
#endif
