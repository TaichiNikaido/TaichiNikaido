//=============================================================================
//
// �΋��̔��� [explosion_fireball.cpp]
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
#include "explosion_fireball.h"
#include "enemy.h"
#include "warning.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define ATTACK (1)
#define MINIMUM_COUNTER__ANIME (0)
#define MINIMUM_PATTERN_ANIME (0)
#define ANIMATION_VALUE (0.125f)
#define MAX_COUNTER_ANIMATION (4)
#define MAX_PATTERN_ANIMATION (8)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionFireball::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionFireball::CExplosionFireball()
{
	m_nCounterAnime = MINIMUM_COUNTER__ANIME;	//�A�j���J�E���^
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//�A�j���p�^�[��
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionFireball::~CExplosionFireball()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExplosionFireball::TextureLoad(void)
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
void CExplosionFireball::TextureUnload(void)
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
CExplosionFireball * CExplosionFireball::Create(D3DXVECTOR3 Position)
{
	//�΋��̔����̃|�C���^
	CExplosionFireball * pExolosionFireball = NULL;
	//�΋��̔����̃|�C���^��NULL�̏ꍇ
	if (pExolosionFireball == NULL)
	{
		//�΋��̔����̃������m��
		pExolosionFireball = new CExplosionFireball;
	}
	//�����������֐��Ăяo��
	pExolosionFireball->Init();
	//�ʒu��ݒ肷��
	pExolosionFireball->SetPosition(Position);
	return pExolosionFireball;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExplosionFireball::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�댯�n�т��擾
	CWarning * pWarning = CGameMode::GetWarning();
	//�T�C�Y�̏����ݒ�
	D3DXVECTOR3 Size = pWarning->GetSize();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�����̏����������֐��Ăяo��
	CExplosion::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(Size);
	//�F�̏����ݒ�
	SetColor(COLOR);
	//�������̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExplosionFireball::Uninit(void)
{
	//�����̏I�������֐��Ăяo��
	CExplosion::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExplosionFireball::Update(void)
{
	//�����̍X�V�����֐��Ăяo��
	CExplosion::Update();
	//�A�j���[�V���������֐��Ăяo��
	Animation();
	//�Փ˔��菈���֐��Ăяo��
	Collision();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExplosionFireball::Draw(void)
{
	//�����̕`�揈���֐��Ăяo��
	CExplosion::Draw();
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CExplosionFireball::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_COUNTER_ANIMATION)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = MINIMUM_COUNTER__ANIME;
		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnime > MAX_PATTERN_ANIMATION)
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
// �A�j���[�V���������֐�
//=============================================================================
void CExplosionFireball::Collision(void)
{
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾
	D3DXVECTOR3 Size = GetSize();
	//�ڕW�̈ʒu���擾
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̃T�C�Y���擾
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
		//�v���C���[�Ƃ̏Փ˔���
		if (Position.x + Size.x / 2 > PlayerPosition.x - PlayerSize.x / 2 &&
			Position.x - Size.x / 2 < PlayerPosition.x + PlayerSize.x / 2 &&
			Position.y + Size.y / 2 > PlayerPosition.y - PlayerSize.y / 2 &&
			Position.y - Size.y / 2 < PlayerPosition.y + PlayerSize.y / 2)
		{
			//�v���C���[�̗̑͂����Z����
			pPlayer->SubLife(ATTACK);
		}
	}
}
