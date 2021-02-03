//=============================================================================
//
// �h���S�� [enemy_dragon.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_dragon.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/dragon.png")
#define SIZE (D3DXVECTOR3(600.0f,600.0f,0.0f))
#define LIFE (300)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyDragon::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyDragon::CEnemyDragon(int nPriority)
{
	m_nPatternAnime = 0;	//�p�^�[���A�j��
	m_nCounterAnime = 0;	//�J�E���^�[�A�j��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyDragon::~CEnemyDragon()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyDragon::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CEnemyDragon::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CEnemyDragon * CEnemyDragon::Create(D3DXVECTOR3 Position)
{
	CEnemyDragon * pEnemyDragon;
	pEnemyDragon = new CEnemyDragon;
	pEnemyDragon->Init();
	pEnemyDragon->SetPosition(Position);
	return pEnemyDragon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyDragon::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyDragon::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyDragon::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
	//�A�j���[�V���������֐��Ăяo��
	Animation();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemyDragon::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemyDragon::Attack(void)
{
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyDragon::Death(void)
{
	//�I�������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CEnemyDragon::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > 24)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;

		if (m_nPatternAnime > 4)
		{
			m_nPatternAnime = 0;
		}
	}

	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnime++;
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}
