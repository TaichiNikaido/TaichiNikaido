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
#define TEXTURE ("Data/Texture/Bullet/Bullet_flower.png")
#define LIFE (500)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFlower::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletFlower::CBulletFlower(int nPriority)
{
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
CBulletFlower * CBulletFlower::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	CBulletFlower * pBulletFlower;
	pBulletFlower = new CBulletFlower;
	pBulletFlower->Init();
	pBulletFlower->SetPosition(Position);
	pBulletFlower->SetMove(Speed);
	return pBulletFlower;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBulletFlower::Init(void)
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
	//SetColor(COLOR);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	////�e�N�X�`���̐ݒ�
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
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�ړ��ʂ��擾
	D3DXVECTOR3 Move = GetMove();
	//�^�[�Q�b�g�̈ʒu���擾
	D3DXVECTOR3 TartgetPosition = pPlayer->GetPosition();
	////�ڕW�܂ł̋������Z�o//����͐������̃v���C���[�Ɍ����Ă̕����w��̂�
	D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(TartgetPosition.x - GetPosition().x, TartgetPosition.y - GetPosition().y, 0.0f);
	float Rotation = atan2f(m_TargetDistance.y, m_TargetDistance.x);
	Move = D3DXVECTOR3(cosf(Rotation)*5.5f, sinf(Rotation)*5.5f, 0.0f);
	//�ړ��ʂ̐ݒ�
	SetMove(Move);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBulletFlower::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CBulletEnemy::Draw();
}