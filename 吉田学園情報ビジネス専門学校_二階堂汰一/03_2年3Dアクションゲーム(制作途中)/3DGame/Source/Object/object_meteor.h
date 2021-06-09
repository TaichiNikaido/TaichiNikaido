//=============================================================================
//
// ���e�I [object_meteor.h]
// Author : ��K������
//
//=============================================================================
#ifndef _OBJECT_METEOR_H_
#define _OBJECT_METEOR_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRoundShadow;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeteor :public CObject
{
public:
	CMeteor();
	~CMeteor();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CMeteor * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static CModel::MODEL_DATA m_MeteorModelData;	//���f�����
	static D3DXMATERIAL * m_pMaterial;				//�}�e���A���̃|�C���^
	D3DXVECTOR3 m_Move;								//�ړ���
	D3DXVECTOR3 m_MeteorShadowSize;					//���e�I�̉e�̃T�C�Y
	D3DXCOLOR m_MeteorShadowColor;					//���e�I�̉e�̐F
	float m_fMeteorMaxHeight;						//覐΂̍ő卂��
	float m_fMeteorHeight;							//覐΂̌��݂̍���
	CRoundShadow * m_pRoundShadow;					//�ۉe�̃|�C���^
};
#endif