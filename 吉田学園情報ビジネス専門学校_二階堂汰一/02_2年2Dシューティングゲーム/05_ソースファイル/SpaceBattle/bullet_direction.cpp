//=============================================================================
//
// �����e [bullet_direction.cpp]
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
#include "bullet_direction.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//�T�C�Y
#define COLOR (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))		//�F
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (1000)									//�̗�
#define EFFECT_LIFE (7)								//�G�t�F�N�g�̗̑�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletDirection::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletDirection::CBulletDirection()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletDirection::~CBulletDirection()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletDirection::TextureLoad(void)
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
// �e�N�X�`���j���֐�
//=============================================================================
void CBulletDirection::TextureUnload(void)
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
CBulletDirection * CBulletDirection::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	//�����e�̃|�C���^
	CBulletDirection * pBulletDirection = NULL;
	//���������e�̃|�C���^��NULL�̏ꍇ
	if (pBulletDirection == NULL)
	{
		//�����e�̃������m��
		pBulletDirection = new CBulletDirection;
	}
	//���������e�̃|�C���^��NULL����Ȃ��ꍇ
	if (pBulletDirection != NULL)
	{
		//�����������֐��Ăяo��
		pBulletDirection->Init();
		//�ʒu��ݒ肷��
		pBulletDirection->SetPosition(Position);
		//�ړ��ʂ�ݒ肷��
		pBulletDirection->SetMove(Speed);
	}
	//�����e�̃|�C���^��Ԃ�
	return pBulletDirection;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletDirection::Init(void)
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
void CBulletDirection::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CBulletEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletDirection::Update(void)
{
	//�G�̒e�X�V�����֐��Ăяo��
	CBulletEnemy::Update();
	//�G�t�F�N�g�̐���
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
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
void CBulletDirection::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CBulletEnemy::Draw();
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletDirection::Death(void)
{
	//�I�������֐��Ăяo��
	Uninit();
	return;
}
