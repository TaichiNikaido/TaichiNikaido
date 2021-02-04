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
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "bullet.h"
#include "bullet_fireball.h"
#include "player.h"
#include "warning.h"
#include "explosion_fireball.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_fireball.png")
#define SIZE (D3DXVECTOR3(35.0f,35.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define SPEED (D3DXVECTOR3(0.0f,3.0f,0.0f))
#define ADD_SCALE (0.1f)
#define EFFECT_LIFE (7)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFireball::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletFireball::CBulletFireball(int nPriority) : CBulletEnemy(nPriority)
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
CBulletFireball * CBulletFireball::Create(D3DXVECTOR3 Position)
{
	CBulletFireball * pFireBall;
	pFireBall = new CBulletFireball;
	pFireBall->Init();
	pFireBall->SetPosition(Position);
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
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�F�̏����ݒ�
	SetColor(COLOR);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�댯�n�т̐���
	CGameMode::SetWarning(CWarning::Create());
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
	//�G�̒e�̍X�V�����֐��Ăяo��
	CBulletEnemy::Update();
	//�`���[�W�����֐��Ăяo��
	Charge();
	//���S�����֐��Ăяo��
	Death();
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
// �`���[�W�����֐�
//=============================================================================
void CBulletFireball::Charge(void)
{
	float fScale = GetScale();
	//�X�P�[�����ڕW��
	if (fScale < 4.0f)
	{
		//�g�債�Ă���
		fScale += ADD_SCALE;
		//�g�k��ݒ肷��
		SetScale(fScale);
	}
	else
	{
		//�ړ��ʂ�ݒ�
		SetMove(SPEED);
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletFireball::Death(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�댯�n�т��擾
	CWarning * pWarning = CGameMode::GetWarning();
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu���擾
		D3DXVECTOR3 TargetPosition = pPlayer->GetPosition();
		//�����ʒu��Y���W���ڕW��Y���W���z������
		if (Position.y >= TargetPosition.y)
		{
			//�����G�t�F�N�g�̐���
			CExplosionFireball::Create(Position);
			//�댯�n�т̏I�������֐��Ăяo��
			pWarning->Uninit();
			//�I�������֐��Ăяo��
			Uninit();
			return;
		}
	}
}
