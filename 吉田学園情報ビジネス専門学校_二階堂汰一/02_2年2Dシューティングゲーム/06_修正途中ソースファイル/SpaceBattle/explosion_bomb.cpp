//=============================================================================
//
// ���e�̔��� [explosion_bomb.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "explosion_bomb.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")
#define SIZE (D3DXVECTOR3(500.0f,500.0f,0.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionBomb::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionBomb::CExplosionBomb(int nPriority)
{
	m_nCounterAnime = 0;					//�A�j���J�E���^
	m_nPatternAnime = 0;					//�A�j���p�^�[��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosionBomb::~CExplosionBomb()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExplosionBomb::TextureLoad(void)
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
// �e�N�X�`���j��
//=============================================================================
void CExplosionBomb::TextureUnload(void)
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
CExplosionBomb * CExplosionBomb::Create(D3DXVECTOR3 Position)
{
	CExplosionBomb * pExolosionBomb;
	pExolosionBomb = new CExplosionBomb;
	pExolosionBomb->Init();
	pExolosionBomb->SetPosition(Position);
	return pExolosionBomb;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExplosionBomb::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.125f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.125f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 1.0f);
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
void CExplosionBomb::Uninit(void)
{
	//�����̏I�������֐��Ăяo��
	CExplosion::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExplosionBomb::Update(void)
{
	//�����̍X�V�����֐��Ăяo��
	CExplosion::Update();
	//�A�j���[�V���������֐��Ăяo��
	Animation();

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExplosionBomb::Draw(void)
{
	//�����̕`�揈���֐��Ăяo��
	CExplosion::Draw();
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CExplosionBomb::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > 4)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnime > 8)
		{
			//�I��
			Uninit();
			return;
		}
	}
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.125f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.125f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �Փ˔��菈��
//=============================================================================
void CExplosionBomb::Collisio(void)
{
}
