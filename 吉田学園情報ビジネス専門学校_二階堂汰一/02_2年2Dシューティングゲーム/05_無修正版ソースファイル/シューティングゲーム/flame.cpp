//=============================================================================
//
// �g���� [flame.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "flame.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CFlame::m_pTexture = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFlame::CFlame(int nPriority) :CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);	//���_�J���[
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFlame::~CFlame()
{
}

//=============================================================================
// �e�N�X�`���̃��[�h�֐�
//=============================================================================
HRESULT CFlame::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FLAME1,								// �t�@�C���̖��O
		&m_pTexture);									// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h�֐�
//=============================================================================
void CFlame::Unload(void)
{
		//�e�N�X�`���̔j��
		if (m_pTexture!= NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//=============================================================================
// �����֐�
//=============================================================================
CFlame * CFlame::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CFlame * pFlame;
	pFlame = new CFlame;
	pFlame->Init(pos, SizeWidth, SizeHeight);
	return pFlame;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CFlame::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//�I�u�W�F�^�C�v��G�ɂ���
	SetObjType(CScene::OBJTYPE_NONE);
	m_pos = pos;	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	//�ʒu�̐ݒ�
	SetPosition(m_pos);
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-SizeWidth / 2), m_pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (SizeWidth / 2), m_pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-SizeWidth / 2), m_pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (SizeWidth / 2), m_pos.y + (SizeHeight / 2), 0.0f);
	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̐ݒ�
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//�F�̐ݒ�
	SetColor(m_col);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CFlame::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CFlame::Update(void)
{
	CScene2d::Update();
	//�ʒu���擾
	m_pos = GetPosition();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CFlame::Draw(void)
{
	CScene2d::Draw();
}