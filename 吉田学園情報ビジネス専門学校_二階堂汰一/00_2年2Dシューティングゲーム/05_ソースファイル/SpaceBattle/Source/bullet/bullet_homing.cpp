//=============================================================================
//
// �z�[�~���O�e [bullet_horming.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "bullet_homing.h"
#include "Player/player.h"
#include "Effect/effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//�T�C�Y
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))		//�F
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (150)									//�̗�
#define MINIMUM_MOVE (0)							//�ړ��ʂ̍ŏ��l
#define MOVE (5.0f)									//�ړ���
#define EFFECT_LIFE (7)								//�G�t�F�N�g���C�t

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletHoming::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletHoming::CBulletHoming()
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
void CBulletHoming::TextureUnload(void)
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
CBulletHoming * CBulletHoming::Create(D3DXVECTOR3 Position)
{
	//�z�[�~���O�e�̃|�C���^
	CBulletHoming * pBulletHoming = NULL;
	//�����z�[�~���O�e��NULL�̏ꍇ
	if (pBulletHoming == NULL)
	{
		//�z�[�~���O�e�̃������m��
		pBulletHoming = new CBulletHoming;
		//�����z�[�~���O�e��NULL����Ȃ��ꍇ
		if (pBulletHoming != NULL)
		{
			//�����������֐��Ăяo��
			pBulletHoming->Init();
			//�ʒu��ݒ肷��
			pBulletHoming->SetPosition(Position);
		}
	}
	//�z�[�~���O�e�̃|�C���^��Ԃ�
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
	if (GetLife() <= MINIMUM_LIFE)
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
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�ړ��ʂ��擾
	D3DXVECTOR3 Move = GetMove();
	//�v���C���[�擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�ڕW�Ƃ̋���
		float m_fDistance = float(sqrt((PlayerPosition.x - Position.x) * (PlayerPosition.x - Position.x) + (PlayerPosition.y - Position.y) * (PlayerPosition.y - Position.y)));
		//�����ڕW�̋����Ȃ�
		if (m_fDistance)
		{
			//�ړ��ʂ�ݒ肷��
			Move.x = ((PlayerPosition.x - GetPosition().x) / m_fDistance * MOVE);
			Move.y = ((PlayerPosition.y - GetPosition().y) / m_fDistance * MOVE);
		}
		else
		{
			//�ړ��ʂ�������
			Move.x = MINIMUM_MOVE;
			Move.y = MOVE;
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
