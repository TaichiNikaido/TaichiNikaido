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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define COLOR (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define LIFE (50)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletBomb::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletBomb::CBulletBomb(int nPriority)
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
void CBulletBomb::TextureUnload(void)
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
CBulletBomb * CBulletBomb::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	CBulletBomb * pBulletBomb;
	pBulletBomb = new CBulletBomb;
	pBulletBomb->Init();
	pBulletBomb->SetPosition(Position);
	pBulletBomb->SetMove(Speed);
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
	if (GetLife() <= 0)
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
	//�����������֐��Ăяo��
	Uninit();
	return;
}
