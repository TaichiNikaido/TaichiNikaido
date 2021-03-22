//=============================================================================
//
// �r���{�[�h [billboard.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard()
{
	m_pTexture = NULL;								//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;								//���_�o�b�t�@�ւ̃|�C���^
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));		//�s��v�Z�p
	m_Position = INITIAL_D3DXVECTOR3;				//�ʒu
	m_Rotation = INITIAL_D3DXVECTOR3;				//��]
	m_Size = INITIAL_D3DXVECTOR3;					//�T�C�Y
	m_Move = INITIAL_D3DXVECTOR3;					//�ړ���
	m_Color = INITIAL_D3DXCOLOR;					//�F
	memset(m_aTexture, NULL, sizeof(m_aTexture));	//�e�N�X�`����UV���W
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`����UV���W�̐ݒ�
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBillboard::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pVtxBuff != NULL)
	{
		//���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		//���_�o�b�t�@�̃|�C���^��NULL�ɂ���
		m_pVtxBuff = NULL;
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBillboard::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`����UV���W�̐ݒ�
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	//�ʒu���X�V����
	m_Position += m_Move;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBillboard::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRotation, mtxTrans; //�s��v�Z�p�̃}�g���N�X
	D3DMATERIAL9 matDef;
	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ�j
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//�Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRotation);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRotation);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;
	// �������f
	D3DXMatrixRotationYawPitchRoll(&mtxRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Position.x,
		m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�}�e���A�����
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_Color.r;
	matDef.Ambient.g = m_Color.g;
	matDef.Ambient.b = m_Color.b;
	matDef.Ambient.a = m_Color.a;
	pDevice->SetMaterial(&matDef);
	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �e�N�X�`����UV���W�̐ݒ�֐�
//=============================================================================
void CBillboard::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	//���_������
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTexture[nCount] = aTex[nCount];
	}
}