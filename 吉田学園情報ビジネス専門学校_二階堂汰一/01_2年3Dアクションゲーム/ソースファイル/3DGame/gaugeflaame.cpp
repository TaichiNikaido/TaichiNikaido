//=============================================================================
//
// �Q�[�W�g [gaugeflame.cpp]
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
#include "gaugeflame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_ANIMATIN_PATTERN (0)	//�A�j���[�V�����p�^�[���̍ŏ��l
#define MINIMUM_ANIMATION_VALUE (0.0f)	//�A�j���[�V�����̒l�̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGaugeFlame::CGaugeFlame()
{
	m_nAnimationPattern = MINIMUM_ANIMATIN_PATTERN;	//�A�j���[�V�����p�^�[��
	m_fAnimationValue = MINIMUM_ANIMATION_VALUE;	//�A�j���[�V�����̒l
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGaugeFlame::~CGaugeFlame()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGaugeFlame::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 1.0f);
	//2D�V�[���̏����������֐��Ăяo��
	CScene2d::Init();
	//�e�N�X�`����UV���W�̐ݒ�
	SetTexture(aTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGaugeFlame::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGaugeFlame::Update(void)
{
	//2D�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 1.0f);
	//�e�N�X�`����UV���W�̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGaugeFlame::Draw(void)
{
	//2D�V�[���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
