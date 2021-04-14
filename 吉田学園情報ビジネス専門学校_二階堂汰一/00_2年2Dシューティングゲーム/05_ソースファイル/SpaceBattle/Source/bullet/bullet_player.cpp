//=============================================================================
//
// �v���C���[�̒e [bullet_player.cpp]
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
#include "Base/sound.h"
#include "Player/player.h"
#include "Enemy/enemy.h"
#include "bullet_player.h"
#include "Effect/effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//�T�C�Y
#define COLOR (D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))		//�F
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (175)									//�̗�
#define EFFECT_LIFE (7)								//�G�t�F�N�g�̗̑�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletPlayer::CBulletPlayer()
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
void CBulletPlayer::TextureUnload(void)
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
CBulletPlayer * CBulletPlayer::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Speed)
{
	//�v���C���[�̒e�̃|�C���^
	CBulletPlayer * pBulletPlayer = NULL;
	//�����v���C���[�̒e��NULL�̏ꍇ
	if (pBulletPlayer == NULL)
	{
		//�v���C���[�̒e�̃������m��
		pBulletPlayer = new CBulletPlayer;
		//�����v���C���[�̒e��NULL����Ȃ��ꍇ
		if (pBulletPlayer != NULL)
		{
			//�����������֐��Ăяo��
			pBulletPlayer->Init();
			//�ʒu��ݒ肷��
			pBulletPlayer->SetPosition(Position);
			//�ړ��ʂ�ݒ肷��
			pBulletPlayer->SetMove(Speed);
		}
	}
	//�v���C���[�̃|�C���^�̒e��Ԃ�
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
	//�����T�E���h��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�V���b�g���̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	}
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
	//�G�t�F�N�g�̐���
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
	//�ړ��ʂ�ݒ肷��
	SetMove(Move);
	//�e�̍X�V�����֐��Ăяo��
	CBullet::Update();
	//�Փ˔��菈���֐��Ăяo��
	Collision();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
	{
		//�����������֐��Ăяo��
		Uninit();
		return;
	}
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
	//�G�̃v���C�I���e�B����
	for (int nCountPriority = PRIORITY_BULLET; nCountPriority <= PRIORITY_ENEMY; nCountPriority++)
	{
		//�V�[���̑�������
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//�V�[���̎擾
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//�����V�[����NULL����Ȃ��ꍇ
			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJECT_TYPE ObjType = pScene->GetObjectType();
				//�����I�u�W�F�N�g�^�C�v���G��������
				if (ObjType == OBJECT_TYPE_ENEMY)
				{
					//�G�̃|�C���^�擾
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//�����G�̃|�C���^��NULL����Ȃ��ꍇ
					if (pEnemy != NULL)
					{
						//�G�̈ʒu���擾
						D3DXVECTOR3 EnemyPosition = pEnemy->GetPosition();
						//�G�̃T�C�Y���擾
						D3DXVECTOR3 EnemySize = pEnemy->GetSize();
						//�G�Ƃ̏Փ˔���
						if (GetPosition().x + GetSize().x / 2 > EnemyPosition.x - (EnemySize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < EnemyPosition.x + (EnemySize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > EnemyPosition.y - (EnemySize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < EnemyPosition.y + (EnemySize.y / 2))
						{
							//�G�̃q�b�g�����֐��Ăяo��
							pEnemy->Hit();
							//���C�t��0�ɂ���
							SetLife(MINIMUM_LIFE);
							return;
						}
					}
				}
			}
		}
	}
}
