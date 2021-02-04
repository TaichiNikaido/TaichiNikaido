//=============================================================================
//
// �z�[�~���O�e [bullet_horming.cpp]
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
#include "player.h"
#include "bullet_homing.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define LIFE (150)
#define SPEED (5.0f)
#define EFFECT_LIFE (7)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletHoming::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletHoming::CBulletHoming(int nPriority) : CBulletEnemy(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletHoming::~CBulletHoming()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletHoming::TextureLoad(void)
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
void CBulletHoming::TextureUnload(void)
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
CBulletHoming * CBulletHoming::Create(D3DXVECTOR3 Position)
{
	CBulletHoming * pBulletHoming;
	pBulletHoming = new CBulletHoming;
	pBulletHoming->Init();
	pBulletHoming->SetPosition(Position);
	return pBulletHoming;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletHoming::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CBulletEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�F�̏����ݒ�
	SetColor(COLOR);
	//�̗͂̐ݒ�
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
void CBulletHoming::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CBulletEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletHoming::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CBulletEnemy::Update();
	//�ǔ������֐��Ăяo��
	Homing();
	//�G�t�F�N�g�̐���
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
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
void CBulletHoming::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CBulletEnemy::Draw();
}

//=============================================================================
// �ǔ������֐�
//=============================================================================
void CBulletHoming::Homing(void)
{
	//�v���C���[�擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu���擾
		D3DXVECTOR3 TargetPosition = pPlayer->GetPosition();
		//�ʒu���擾
		D3DXVECTOR3 Position = GetPosition();
		//�ړ��ʂ��擾
		D3DXVECTOR3 Move = GetMove();
		//�ڕW�Ƃ̋���
		float m_fDistance = float(sqrt((TargetPosition.x - Position.x) * (TargetPosition.x - Position.x) + (TargetPosition.y - Position.y) * (TargetPosition.y - Position.y)));
		if (m_fDistance)
		{
			Move.x = ((TargetPosition.x - GetPosition().x) / m_fDistance * SPEED);
			Move.y = ((TargetPosition.y - GetPosition().y) / m_fDistance * SPEED);
		}
		else
		{
			Move.x = 0;
			Move.y = SPEED;
		}
		//�ړ��ʂ�ݒ肷��
		SetMove(Move);
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletHoming::Death(void)
{
	//�I�������֐��Ăяo��
	Uninit();
	return;
}
