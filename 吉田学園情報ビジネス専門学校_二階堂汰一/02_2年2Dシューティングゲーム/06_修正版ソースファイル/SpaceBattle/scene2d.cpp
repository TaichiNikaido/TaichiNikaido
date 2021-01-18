//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority)
{
	m_pTexture = NULL;										//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;										//���_�o�b�t�@�ւ̃|�C���^
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���W
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�T�C�Y
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�J���[
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	memset(m_aVtxPosition, NULL, sizeof(m_aVtxPosition));	//���_���W
	memset(m_aTexture, NULL, sizeof(m_aTexture));			//�e�N�X�`����UV���W
	m_fScale = 1.0f;										//�k��
	m_fAngle = 0.0f;										//�p�x
	m_fLength = 0.0f;										//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	// �e�N�X�`�����W�̐ݒ�
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
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CScene2d::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�����̐ݒ�
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//�p�x�̐ݒ�
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	// �e�N�X�`�����W�̐ݒ�
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
void CScene2d::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CScene2d::SetPosition(D3DXVECTOR3 Pos)
{
	//���W�̊��蓖��
	m_Position = Pos;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CScene2d::SetRotation(D3DXVECTOR3 Rot)
{
	//�����̊��蓖��
	m_Rotation = Rot;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 Size)
{
	//�T�C�Y�̊��蓖��
	m_Size = Size;
}

//=============================================================================
// �k�ڐݒ�֐�
//=============================================================================
void CScene2d::SetScale(float fScale)
{
	//�k�ڂ̊��蓖��
	m_fScale = fScale;
}

//=============================================================================
// ���_�J���[�ݒ�֐�
//=============================================================================
void CScene2d::SetColor(D3DXCOLOR Color)
{
	//�F�̐ݒ������
	m_Color = Color;
}

//=============================================================================
// ���_���W�ݒ�֐�
//=============================================================================
void CScene2d::SetVertexPosition(D3DXVECTOR3 VtxPos[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W���蓖��
		m_aVtxPosition[nCount] = VtxPos[nCount];
	}
}

//=============================================================================
// �e�N�X�`����UV���W�ݒ�֐�
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTexture[nCount] = aTex[nCount];
	}
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_pTexture = pTexture;
}
























////=============================================================================
////
//// �|���S������ [scene2d.cpp]
//// Author : ��K������
////
////=============================================================================
//
////*****************************************************************************
//// �w�b�_�t�@�C���̃C���N���[�h
////*****************************************************************************
//#include "main.h"
//#include "scene.h"
//#include "scene2d.h"
//#include "renderer.h"
//#include "manager.h"
//#include "keyboard.h"
//
////=============================================================================
//// �R���X�g���N�^
//
////=============================================================================
//CScene2d::CScene2d(int nPriority) :CScene(nPriority)
//{
//	m_pTexture = NULL;
//	m_pVtxBuff = NULL;
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_col[nCount] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
//	}
//	m_fSizeX = 0.0f;
//	m_fSizeY = 0.0f;
//	m_fTexAnim = 0.0f;
//}
//
////=============================================================================
////�f�X�g���N�^
////=============================================================================
//CScene2d::~CScene2d()
//{
//}
//
////=============================================================================
//// �������֐�
////=============================================================================
//HRESULT CScene2d::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// ���_����ݒ�
//	VERTEX_2D *pVtx;
//
//	// ���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
//
//	// �|���S���̈ʒu��ݒ�
//	//m_Position = D3DXVECTOR3((float)FIELD_WIDTH / 2, FIELD_HEIGHT / 2, 0.0f);
//
//	m_fSizeX = SizeWidth;
//	m_fSizeY = SizeHeight;
//	m_Position = pos;
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_col[nCount] = D3DXCOLOR(255, 255, 255, 255);
//	}
//	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//
//	pVtx[0].pos = m_vpos[0];
//	pVtx[1].pos = m_vpos[1];
//	pVtx[2].pos = m_vpos[2];
//	pVtx[3].pos = m_vpos[3];
//
//	// rhw�̐ݒ�
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	// ���_�J���[�̐ݒ�
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// �e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
//	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
//	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
//	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
//
//	m_pVtxBuff->Unlock();
//
//	CScene::SetPosition(pos);
//	return S_OK;
//}
//
////=============================================================================
//// �I���֐�
////=============================================================================
//void CScene2d::Uninit(void)
//{
//	// ���_�o�b�t�@�̔j��
//	if (m_pVtxBuff != NULL)
//	{
//		m_pVtxBuff->Release();
//		m_pVtxBuff = NULL;
//	}
//	Release();
//}
//
////=============================================================================
//// �X�V�֐�
////=============================================================================
//void CScene2d::Update(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// ���_����ݒ�
//	VERTEX_2D *pVtx;
//
//	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//D3DXVECTOR3 pos = GetPosition();
//
//	//pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);7
//
//	pVtx[0].pos = m_vpos[0];
//	pVtx[1].pos = m_vpos[1];
//	pVtx[2].pos = m_vpos[2];
//	pVtx[3].pos = m_vpos[3];
//
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	pVtx[0].col = m_col[0];
//	pVtx[1].col = m_col[1];
//	pVtx[2].col = m_col[2];
//	pVtx[3].col = m_col[3];
//
//	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
//	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
//	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
//	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
//
//	//SetPosition(pos);
//	// ���_�o�b�t�@���A�����b�N����
//	m_pVtxBuff->Unlock();
//	CScene::SetPosition(m_Position);
//}
//
////=============================================================================
//// �`��֐�
////=============================================================================
//void CScene2d::Draw(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
//
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, m_pTexture);
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
//}
//
//void CScene2d::SetPosition(D3DXVECTOR3 pos)
//{
//	m_Position = pos;
//}
//
//void CScene2d::SetVertexPosition(D3DXVECTOR3 vpos[NUM_VERTEX])
//{
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = vpos[nCount];
//	}
//}
//
//void CScene2d::SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2)
//{
//	m_fTexX = fTexX;
//	m_fTexY = fTexY;
//	m_fTexX2 = fTexX2;
//	m_fTexY2 = fTexY2;
//}
//
//void CScene2d::SetColor(D3DCOLOR col[NUM_VERTEX])
//{
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_col[nCount] = col[nCount];
//	}
//}
//
//D3DXVECTOR3 CScene2d::GetPosition(void)
//{
//	return m_Position;
//}
//
//CScene2d * CScene2d::Create(D3DXVECTOR3 pos)
//{
//	CScene2d * pScene2d;
//	pScene2d = new CScene2d;
//	pScene2d->SetPosition(pos);
//	pScene2d->Init(pos, 50.0f, 50.0f);
//	return pScene2d;
//}
//
//void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
//{
//	//�e�N�X�`���̊��蓖��
//	m_pTexture = pTexture;
//}
