//=============================================================================
//
// �w�i���� [background.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "background.h"
#include "renderer.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_fTextureX = 0.0f;	//�e�N�X�`����X
	m_fTextureY = 0.0f;	//�e�N�X�`����Y
	m_fFastMove = 0.0f;	//�����ړ���
	m_fSlowMove = 0.0f;	//�x���ړ���
	m_fMove = 0.0f;		//�ړ���
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CBg::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BG1,								// �t�@�C���̖��O
		&m_apTexture[0]);								// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BG2,								// �t�@�C���̖��O
		&m_apTexture[1]);								// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BG3,								// �t�@�C���̖��O
		&m_apTexture[2]);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CBg * pBg;
	pBg = new CBg;
	pBg->Init(pos,SizeWidth,SizeHeight);
	//pBg->SetPosition(pos);
	return pBg;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pos = pos;			//�ʒu
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight;	//����

	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeWidth, SizeHeight);
		//���_���W�̃Z�b�g
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		//�e�N�X�`�����Z�b�g
		m_apScene[nCount]->SetTex(
			m_fTextureX,
			1.0f,
			m_fTextureY - m_fMove, 
			1.0f);
		//�e�N�X�`���̊��蓖��
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBg::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBg::Update(void)
{
	//�ړ��ʂɉ��Z
	m_fMove += 0.0001f;
	//�����ړ��ʂɉ��Z
	m_fFastMove += 0.001f;
	//�x���ړ��ʂɉ��Z
	m_fSlowMove += 0.0001f;

	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount]->Update();
		//���_���W���Z�b�g
		m_apScene[nCount]->SetVertexPosition(m_vpos);
	}
	//�e�N�X�`�����Z�b�g
	m_apScene[0]->SetTex(
		m_fTextureX,
		m_fMove,
		1.0f,
		m_fMove - 1.0f);

	m_apScene[1]->SetTex(
		m_fTextureX,
		m_fSlowMove,
		1.0f,
		m_fSlowMove -1.0f);

	m_apScene[2]->SetTex(
		m_fTextureX,
		m_fFastMove,
		1.0f,
		m_fFastMove - 1.0f);

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBg::Draw(void)
{
}
