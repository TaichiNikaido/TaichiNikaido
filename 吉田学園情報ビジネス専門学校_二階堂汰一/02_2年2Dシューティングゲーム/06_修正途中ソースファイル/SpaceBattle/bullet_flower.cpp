//=============================================================================
//
// �Ԓe [bullet_flower.cpp]
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
#include "mode_game.h"
#include "bullet_flower.h"
#include "bullet.h"
#include "player.h"
#include "bullet_flower.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_flower.png")
#define SIZE (D3DXVECTOR3(40.0f,40.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define LIFE (1500)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFlower::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletFlower::CBulletFlower(int nPriority) : CBulletEnemy(nPriority)
{
	m_ColorNumber = COLOR_NUMBER_NONE;	//�F�̔ԍ�
	m_nTime = 0;						//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletFlower::~CBulletFlower()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBulletFlower::TextureLoad(void)
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
void CBulletFlower::TextureUnload(void)
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
CBulletFlower * CBulletFlower::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed, COLOR_NUMBER nColor)
{
	CBulletFlower * pBulletFlower;
	pBulletFlower = new CBulletFlower;
	pBulletFlower->SetPosition(Position);
	pBulletFlower->SetMove(Speed);
	pBulletFlower->m_ColorNumber = nColor;
	pBulletFlower->Init();
	return pBulletFlower;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletFlower::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 1.0f);
	//�G�̒e�̏����������֐��Ăяo��
	CBulletEnemy::Init();
	//�T�C�Y�̐ݒ�
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
void CBulletFlower::Uninit(void)
{
	//�G�̒e�̏I�������֐��Ăяo��
	CBulletEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBulletFlower::Update(void)
{
	CBulletEnemy::Update();
	//�ړ������֐��Ăяo��
	Move();
	//�F�I�������֐��Ăяo��
	ColorSelect();
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
void CBulletFlower::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CBulletEnemy::Draw();
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CBulletFlower::Move(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�������擾
	D3DXVECTOR3 Rotaion = GetRotation();
	//�ړ��ʂ��擾
	D3DXVECTOR3 Move = GetMove();
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		if (m_nTime == 80)
		{
			//�v���C���[�̈ʒu���擾
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//�v���C���[�܂ł̋��������߂�
			D3DXVECTOR3 TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
			Rotaion.y = float(atan2(TargetDistance.y, TargetDistance.x));
			Move = D3DXVECTOR3(cosf(Rotaion.y) * 5.5f, sinf(Rotaion.y) * 5.5f, 0.0f);
		}
		//�^�C����i�߂�
		m_nTime++;
	}
	//�i�s�����Ɍ��������킹��
	Rotaion.z = atan2f((Position.x + Move.x) - Position.x, (Position.y + Move.y) - Position.y);
	//���������킹��
	SetRotation(Rotaion);
	//�ړ��ʂ�ݒ�
	SetMove(Move);
}

//=============================================================================
// �F�I�������֐�
//=============================================================================
void CBulletFlower::ColorSelect(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CBulletFlower::Death(void)
{
	//�I�������֐��Ăяo��
	Uninit();
	return;
}
