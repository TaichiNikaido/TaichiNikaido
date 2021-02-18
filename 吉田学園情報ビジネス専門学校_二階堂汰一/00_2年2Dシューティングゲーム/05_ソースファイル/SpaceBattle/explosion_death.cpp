//=============================================================================
//
// ���S���̔��� [explosion_death.cpp]
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
#include "sound.h"
#include "explosion_death.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")	  //�e�N�X�`��
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))	  //�T�C�Y
#define MINIMUM_COUNTER__ANIME (0)				  //�A�j���[�V�����ŏ��J�E���^
#define MINIMUM_PATTERN_ANIME (0)				  //�A�j���[�V�����ŏ��p�^�[��
#define ANIMATION_VALUE (0.125f)				  //�A�j���[�V�����̒l
#define MAX_COUNTER_ANIME (4)					  //�A�j���[�V�����ő�J�E���^
#define MAX_PATTERN_ANIME (8)					  //�A�j���[�V�����ő�p�^�[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionDeath::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionDeath::CExplosionDeath()
{
	m_nCounterAnime = MINIMUM_COUNTER__ANIME;	//�A�j���J�E���^
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//�A�j���p�^�[��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosionDeath::~CExplosionDeath()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExplosionDeath::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CExplosionDeath::TextureUnload(void)
{
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CExplosionDeath * CExplosionDeath::Create(D3DXVECTOR3 Position)
{
	//���S���̔����̃|�C���^
	CExplosionDeath * pExplosionDeath = NULL;
	//�������S���̔����̃|�C���^��NULL�̏ꍇ
	if (pExplosionDeath == NULL)
	{
		//���S���̔����̃������m��
		pExplosionDeath = new CExplosionDeath;
	}
	//�������S���̔����̃|�C���^��NULL����Ȃ��ꍇ
	if (pExplosionDeath != NULL)
	{
		//�����������֐��Ăяo��
		pExplosionDeath->Init();
		//�ʒu��ݒ肷��
		pExplosionDeath->SetPosition(Position);
	}
	//���S���̔����̃|�C���^��Ԃ�
	return pExplosionDeath;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExplosionDeath::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�����̏����������֐��Ăяo��
	CExplosion::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExplosionDeath::Uninit(void)
{
	//�����̏I�������֐��Ăяo��
	CExplosion::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExplosionDeath::Update(void)
{
	//�����̍X�V�����֐��Ăяo��
	CExplosion::Update();
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_COUNTER_ANIME)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = MINIMUM_COUNTER__ANIME;
		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnime > MAX_PATTERN_ANIME)
		{
			//�I�������֐��Ăяo��
			Uninit();
			return;
		}
	}
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExplosionDeath::Draw(void)
{
	//�����̕`�揈���֐��Ăяo��
	CExplosion::Draw();
}
