//=============================================================================
//
// ���e�̔��� [explosion_bomb.cpp]
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
#include "explosion_bomb.h"
#include "enemy.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(500.0f,500.0f,0.0f))	//�T�C�Y
#define MINIMUM_COUNTER__ANIME (0)				//�A�j���[�V�����ŏ��J�E���^
#define MINIMUM_PATTERN_ANIME (0)				//�A�j���[�V�����ŏ��p�^�[��
#define ANIMATION_VALUE (0.125f)				//�A�j���[�V�����̒l
#define MAX_COUNTER_ANIME (4)					//�A�j���[�V�����ő�J�E���^
#define MAX_PATTERN_ANIME (8)					//�A�j���[�V�����ő�p�^�[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionBomb::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionBomb::CExplosionBomb()
{
	m_nCounterAnime = MINIMUM_COUNTER__ANIME;	//�A�j���J�E���^
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//�A�j���p�^�[��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosionBomb::~CExplosionBomb()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExplosionBomb::TextureLoad(void)
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
// �e�N�X�`���j��
//=============================================================================
void CExplosionBomb::TextureUnload(void)
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
CExplosionBomb * CExplosionBomb::Create(D3DXVECTOR3 Position)
{
	//���e�̔��j�̃|�C���^
	CExplosionBomb * pExplosionBomb = NULL;
	//�������e�̔����̃|�C���^��NULL�̏ꍇ
	if (pExplosionBomb == NULL)
	{
		//���e�̔����̃������m��
		pExplosionBomb = new CExplosionBomb;
		//�������e�̔����̃|�C���^��NULL����Ȃ��ꍇ
		if (pExplosionBomb != NULL)
		{
			//�����������֐��Ăяo��
			pExplosionBomb->Init();
			//�ʒu��ݒ肷��
			pExplosionBomb->SetPosition(Position);
		}
	}
	//���e�̔��j�̃|�C���^��Ԃ�
	return pExplosionBomb;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExplosionBomb::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�����̏����������֐��Ăяo��
	CExplosion::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExplosionBomb::Uninit(void)
{
	//�����̏I�������֐��Ăяo��
	CExplosion::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExplosionBomb::Update(void)
{
	//�����̍X�V�����֐��Ăяo��
	CExplosion::Update();
	//�����蔻��
	Collision();
	//�A�j���[�V���������֐��Ăяo��
	Animation();

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExplosionBomb::Draw(void)
{
	//�����̕`�揈���֐��Ăяo��
	CExplosion::Draw();
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CExplosionBomb::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_COUNTER_ANIME)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = MINIMUM_COUNTER__ANIME;

		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnime > MAX_PATTERN_ANIME)
		{
			//�I�������֐��Ăяo��
			Uninit();
			return;
		}
	}
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �Փ˔��菈��
//=============================================================================
void CExplosionBomb::Collision(void)
{
	//�e�̃v���C�I���e�B����G�̃v���C�I���e�B�܂ŉ�
	for (int nCountPriority = 0; nCountPriority <= PRIORITY_ENEMY + 1; nCountPriority++)
	{
		//�V�[���̑�������
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//�V�[���̎擾
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//�����V�[����NULL����Ȃ��ꍇ
			if (pScene != NULL)
			{
				//�����I�u�W�F�N�g�^�C�v���΋�����Ȃ��Ƃ�
				if (pScene->GetObjType() != CScene::OBJTYPE_FIRE_BALL)
				{
					//�G�̃|�C���^
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//�����G�̃|�C���^��NULL����Ȃ��ꍇ
					if (pEnemy != NULL)
					{
						//�G�̈ʒu���擾����
						D3DXVECTOR3 EnemyPosition = pEnemy->GetPosition();
						//�G�̃T�C�Y���擾����
						D3DXVECTOR3 EnemySize = pEnemy->GetSize();
						//�G�Ƃ̏Փ˔���
						if (GetPosition().x + GetSize().x / 2 > EnemyPosition.x - (EnemySize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < EnemyPosition.x + (EnemySize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > EnemyPosition.y - (EnemySize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < EnemyPosition.y + (EnemySize.y / 2))
						{
							//�G�̃q�b�g�����֐��Ăяo��
							pEnemy->Hit();
						}
					}
					//�e�̃|�C���^
					CBullet * pBullet = dynamic_cast<CBullet*> (pScene);
					//�����e�̃|�C���^��NULL����Ȃ��ꍇ
					if (pBullet != NULL)
					{
						//�e�̈ʒu���擾����
						D3DXVECTOR3 BulletPosition = pBullet->GetPosition();
						//�e�̃T�C�Y���擾����
						D3DXVECTOR3 BulletSize = pBullet->GetSize();
						//�G�Ƃ̏Փ�
						if (GetPosition().x + GetSize().x / 2 > BulletPosition.x - (BulletSize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < BulletPosition.x + (BulletSize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > BulletPosition.y - (BulletSize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < BulletPosition.y + (BulletSize.y / 2))
						{
							//�e�̏����������֐��Ăяo��
							pBullet->Uninit();
						}
					}
				}
			}
		}
	}
}
