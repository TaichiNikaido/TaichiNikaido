//=============================================================================
//
// �e [shadow.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/Manager.h"
#include "Base/Renderer.h"
#include "Polygon3d/shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_SCALE (1.0f)	//�g�k�̏����l
#define INITIAL_ANGLE (0.0f)	//�p�x�̏����l
#define INITIAL_LENGTH (0.0f)	//�����̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow()
{
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));	//���[���h�}�g���N�X
	m_pVtxBuff = nullptr;							//���_�o�b�t�@�ւ̃|�C���^
	//�e�N�X�`�����W
	m_aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	m_Position = INITIAL_D3DXVECTOR3;				//�ʒu
	m_Rotation = INITIAL_D3DXVECTOR3;				//��]
	m_Size = INITIAL_D3DXVECTOR3;					//�T�C�Y
	m_Color = INITIAL_D3DXCOLOR;					//���_�J���[
	m_fScale = INITIAL_SCALE;						//�k��
	m_fAngle = INITIAL_ANGLE;						//�p�x
	m_fLength = INITIAL_LENGTH;						//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CShadow::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);
	//���_����ݒ�
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//���_���W�̐ݒ�
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
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
void CShadow::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��nullptr����Ȃ��ꍇ
	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@��j������
		m_pVtxBuff->Release();
		//���_�o�b�t�@�̃|�C���^��nullptr�ɂ���
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CShadow::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;
	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CShadow::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �e�N�X�`����UV���W�ݒ�֐�
//=============================================================================
void CShadow::SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTexture[nCount] = aTexture[nCount];
	}
}