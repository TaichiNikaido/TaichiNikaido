//=============================================================================
//
// ���f���Ǘ����� [model.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTS (32)			//�ő�p�[�c��
#define MAX_MATERIAL (64)		//�ő�}�e���A����

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;						//�}�e���A�����ւ̃|�C���^
		DWORD nNumMat;								//�}�e���A�����̐�
		LPD3DXMESH pMesh;							//���b�V�����ւ̃|�C���^
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];	//�e�N�X�`���ւ̃|�C���^
		D3DXMATRIX mtxWorld;						//���[���h�ϊ��s��
		CModel *pParent;							//�e�̃��f���ւ̃|�C���^
		int nIndexModelParent;						//�e���f���̃C���f�b�N�X
	}MODEL_DATA;
	CModel();
	~CModel();
	static char * LoadModelText(const char *cText);
	static CModel* Create(MODEL_DATA modeldata);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParentModel(CModel * pParentModel);
	void SetModel(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Size);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void BindModel(MODEL_DATA ModelData) { m_aModelData = ModelData; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture,int nCount);
	MODEL_DATA GetModelData(void) { return m_aModelData; }
private:
	MODEL_DATA m_aModelData;		//���f���f�[�^
	D3DXVECTOR3 m_WorldPosition;	//���[���h���W
	D3DXVECTOR3 m_Position;			//�ʒu
	D3DXVECTOR3 m_Rotation;			//��]
	D3DXVECTOR3 m_Size;				//�T�C�Y
};
#endif