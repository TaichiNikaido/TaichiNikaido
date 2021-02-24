//=============================================================================
//
// ���e [bullet_bomb.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "bullet_bomb.h"
#include "explosion_bomb.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_bomb.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))			//�T�C�Y
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			//�F
#define MINIMUM_LIFE (0)								//�̗͂̍ŏ��l
#define LIFE (50)										//�̗�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletBomb::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletBomb::CBulletBomb()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletBomb::~CBulletBomb()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletBomb::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X���擾
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
void CBulletBomb::TextureUnload(void)
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
CBulletBomb * CBulletBomb::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	//���e�̃|�C���^
	CBulletBomb * pBulletBomb = NULL;
	//�������e�̃|�C���^��NULL�̏ꍇ
	if (pBulletBomb == NULL)
	{
		//���e�̃������m��
		pBulletBomb = new CBulletBomb;
		//�������e�̃|�C���^��NULL����Ȃ��ꍇ
		if (pBulletBomb != NULL)
		{
			//�����������֐��Ăяo��
			pBulletBomb->Init();
			//�ʒu��ݒ肷��
			pBulletBomb->SetPosition(Position);
			//�ړ��ʂ�ݒ肷��
			pBulletBomb->SetMove(Speed);
		}
	}
	//���e�̃|�C���^��Ԃ�
	return pBulletBomb;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletBomb::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�e�̏������֐��Ăяo��
	CBullet::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�F�̏����ݒ�
	SetColor(COLOR);
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
void CBulletBomb::Uninit(void)
{
	//�e�̏I�������֐��Ăяo��
	CBullet::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletBomb::Update(void)
{
	//�ړ��ʂ̎擾
	D3DXVECTOR3 Move = GetMove();
	//�ړ��ʂ�ݒ肷��
	SetMove(Move);
	//�e�̍X�V�����֐��Ăяo��
	CBullet::Update();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
	{
		//���S�����֐��Ăяo��
		Death();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBulletBomb::Draw(void)
{
	//�e�̕`�揈���֐��Ăяo��
	CBullet::Draw();
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletBomb::Death(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����̐���
	CExplosionBomb::Create(GetPosition());
	//�����T�E���h��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�������̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}
	//�I�������֐��Ăяo��
	Uninit();
	return;
}