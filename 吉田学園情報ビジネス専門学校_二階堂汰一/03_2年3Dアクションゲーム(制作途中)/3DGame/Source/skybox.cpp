//=============================================================================
//
// �X�J�C�{�b�N�X [skybox.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "skybox.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/skybox.png")
#define SIZE (D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))
#define SPHERE_H_COUNT (64)
#define SPHERE_V_COUNT (64) 
#define SPHERE_NUM_VERTEX ((SPHERE_H_COUNT + 1) * (SPHERE_V_COUNT + 1))
#define SPHERE_NUM_INDEX (((SPHERE_H_COUNT + 1) * 2) * SPHERE_V_COUNT + (SPHERE_V_COUNT - 1) * 2)
#define SPHERE_NUM_PRIMITIVE (SPHERE_H_COUNT * SPHERE_V_COUNT * 2) + ((SPHERE_V_COUNT-1) * 4)	

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CSkyBox::m_pTexture = nullptr;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSkyBox::CSkyBox()
{
	memset(m_mtxWorld,NULL,sizeof(m_mtxWorld));		//���[���h�}�g���N�X
	m_pVtxBuff = nullptr;							//���_�o�b�t�@�̃|�C���^
	m_pIdxBuff = nullptr;							//�C���f�b�N�X�o�b�t�@�|�C���^
	memset(m_aTexture,NULL,sizeof(m_aTexture));		//�e�N�X�`����UV���W
	m_Color = INITIAL_D3DXCOLOR;					//���_�J���[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSkyBox::~CSkyBox()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CSkyBox::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		//�f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,						//�t�@�C���̖��O
		&m_pTexture);						//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CSkyBox::TextureUnload(void)
{
	//�����e�N�X�`���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`���̃|�C���^��nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CSkyBox * CSkyBox::Create(void)
{
	//�X�J�C�{�b�N�X�̃|�C���^
	CSkyBox * pSkyBox = nullptr;
	//�X�J�C�{�b�N�X�̃|�C���^��nullptr�̏ꍇ
	if (pSkyBox == nullptr)
	{
		//�X�J�C�{�b�N�X�̃������m��
		pSkyBox = new CSkyBox;
		//�X�J�C�{�b�N�X�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pSkyBox != nullptr)
		{
			//�X�J�C�{�b�N�X�̏����������֐��Ăяo��
			pSkyBox->Init();
		}
	}
	//�X�J�C�{�b�N�X�̃|�C���^��Ԃ�
	return pSkyBox;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CSkyBox::Init(void)
{
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�@���̏����ݒ�
	D3DXVECTOR3 Normal = INITIAL_D3DXVECTOR3;
	//���_���
	VERTEX_3D * pVtx;
	//�C���f�b�N�X���
	WORD * pIdx;
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�C���f�b�N�X
	int nIndex = 0;
	//�e�N�X�`���̃C���f�b�N�X
	int nTextureIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		float fAngleY = 180.0f / SPHERE_V_COUNT * vIndex;
		nTextureIndex = 0;
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / SPHERE_H_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2)*sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2)*cosf(D3DXToRadian(fAngle)));
			//�@�����K��
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRotation());
			// �@���̐ݒ�
			pVtx[nIndex].nor = -GetRotation();
			// ���_�J���[�̐ݒ�
			pVtx[nIndex].col = m_Color;
			// �e�N�X�`�����W�̐ݒ�
			pVtx[nIndex].tex = D3DXVECTOR2((float)nTextureIndex, (float)vIndex);
			nIndex++;
			nTextureIndex++;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * SPHERE_NUM_INDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	// �C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (SPHERE_H_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CSkyBox::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@�̔j�������֐��Ăяo��
		m_pVtxBuff->Release();
		//���_�o�b�t�@��nullptr�ɂ���
		m_pVtxBuff = nullptr;
	}
	//�j�������֐�
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CSkyBox::Update(void)
{
	//���_����ݒ�
	VERTEX_3D *pVtx;
	WORD * pIdx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		float fAngleY = vIndex * 180.0f / SPHERE_V_COUNT;
		fAngleY += 90.0f;
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / SPHERE_H_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2) * sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2) * cosf(D3DXToRadian(fAngle)));
			//�@�����K��
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRotation());
			//�@���̐ݒ�
			pVtx[nIndex].nor = D3DXVECTOR3(D3DXToRadian(-fAngle) * hIndex, D3DXToRadian(-fAngleY) * vIndex, D3DXToRadian(-fAngle)  *hIndex);
			//���_�J���[�̐ݒ�
			pVtx[nIndex].col = m_Color;
			//�e�N�X�`�����W�̐ݒ�
			pVtx[nIndex].tex = D3DXVECTOR2((1.0f / SPHERE_H_COUNT) * (float)nTexIndex, (1.0f / SPHERE_V_COUNT) * (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (SPHERE_H_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CSkyBox::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	//���[���h�}�g���N�X������
	D3DXMatrixIdentity(&m_mtxWorld);
	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(GetRotation().y), D3DXToRadian(GetRotation().x), D3DXToRadian(GetRotation().z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���N�X
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�F�Z�b�g
	matDef.Ambient = m_Color;
	pDevice->SetMaterial(&matDef);
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���Z�b�g
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SPHERE_NUM_VERTEX, 0, SPHERE_NUM_PRIMITIVE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�ێ����Ă����}�e���A�������ɖ߂�
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
