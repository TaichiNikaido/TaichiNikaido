//=============================================================================
//
// �v���C���[�̒e [bullet_player.cpp]
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
#include "bullet_player.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define LIFE (175)
#define EFFECT_LIFE (7)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletPlayer::CBulletPlayer(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletPlayer::~CBulletPlayer()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletPlayer::TextureLoad(void)
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
void CBulletPlayer::TextureUnload(void)
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
CBulletPlayer * CBulletPlayer::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Speed)
{
	CBulletPlayer * pBulletPlayer;
	pBulletPlayer = new CBulletPlayer;
	pBulletPlayer->Init();
	pBulletPlayer->SetPosition(Position);
	pBulletPlayer->SetMove(Speed);
	return pBulletPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletPlayer::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f,0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f,0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f,1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f,1.0f);
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�e�̏������֐��Ăяo��
	CBullet::Init();
	//�V���b�g���̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
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
void CBulletPlayer::Uninit(void)
{
	//�e�̏I�������֐��Ăяo��
	CBullet::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletPlayer::Update(void)
{
	//�ړ��ʂ̎擾
	D3DXVECTOR3 Move = GetMove();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//�����������֐��Ăяo��
		Uninit();
		return;
	}
	//�G�t�F�N�g�̐���
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
	//�ړ��ʂ�ݒ肷��
	SetMove(Move);
	//�Փ˔��菈���֐��Ăяo��
	Collision();
	//�e�̍X�V�����֐��Ăяo��
	CBullet::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBulletPlayer::Draw(void)
{
	//�e�̕`�揈���֐��Ăяo��
	CBullet::Draw();
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletPlayer::Death(void)
{
	//�����������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// �Փ˔��菈���֐�
//=============================================================================
void CBulletPlayer::Collision(void)
{
	//�G�̎擾
	CEnemy * pEnemy = CGameMode::GetEnemy();
	if (pEnemy != NULL)
	{
		//�G�Ƃ̏Փ�
		if (GetPosition().x + GetSize().x / 2 > pEnemy->GetPosition().x - (pEnemy->GetSize().x / 2) &&
			GetPosition().x - GetSize().x / 2 < pEnemy->GetPosition().x + (pEnemy->GetSize().x / 2) &&
			GetPosition().y + GetSize().y / 2 > pEnemy->GetPosition().y - (pEnemy->GetSize().y / 2) &&
			GetPosition().y - GetSize().y / 2 < pEnemy->GetPosition().y + (pEnemy->GetSize().y / 2))
		{
			//�G�̃q�b�g�����֐��Ăяo��
			pEnemy->Hit();
			//���S�����֐��Ăяo��
			Death();
		}
	}
}
