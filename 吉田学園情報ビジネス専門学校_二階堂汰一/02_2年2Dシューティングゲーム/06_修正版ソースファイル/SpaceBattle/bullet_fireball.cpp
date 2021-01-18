//=============================================================================
//
// �΋� [bullet_fireball.cpp]
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
#include "bullet.h"
#include "bullet_fireball.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")
#define COLOR (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define LIFE (75)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFireball::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletFireball::CBulletFireball(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletFireball::~CBulletFireball()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletFireball::TextureLoad(void)
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
void CBulletFireball::TextureUnload(void)
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
CBulletFireball * CBulletFireball::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed, D3DXVECTOR3 Size)
{
	CBulletFireball * pFireBall;
	pFireBall = new CBulletFireball;
	pFireBall->Init();
	pFireBall->SetPosition(Position);
	pFireBall->SetSize(Size);
	pFireBall->SetMove(Speed);
	return pFireBall;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletFireball::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�G�̒e�̏����������֐��Ăяo��
	CBulletEnemy::Init();
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
void CBulletFireball::Uninit(void)
{
	//�G�̒e�̏I�������֐��Ăяo��
	CBulletEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletFireball::Update(void)
{
	//�ړ��ʂ̎擾
	D3DXVECTOR3 Move = GetMove();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
	//�ړ��ʂ�ݒ肷��
	SetMove(Move);
	//�G�̒e�̍X�V�����֐��Ăяo��
	CBulletEnemy::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBulletFireball::Draw(void)
{
	//�G�̒e�̕`�揈���֐��Ăяo��
	CBulletEnemy::Draw();
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletFireball::Death(void)
{
	//�����G�t�F�N�g�̐���
	//
	//�����T�E���h�̍Đ�
	//
	//�I�������֐��Ăяo��
	Uninit();
	return;
}
