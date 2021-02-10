//=============================================================================
//
// �X�R�A��UI [ui_score.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <cmath>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "ui_number_texture.h"
#include "ui_score.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POSITION (D3DXVECTOR3(1495.0f,25.0f,0.0f))
#define SIZE (D3DXVECTOR3(47.0f,47.0f,0.0f))
#define MINIMUM_INTEGER (0)
#define MINIMUM_COUNT_NUMBER (0)
#define NUM_CONVERSION (10.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScoreUI::CScoreUI(int nPriority) : CScene(nPriority)
{
	memset(m_apNumberTexture, NULL, sizeof(m_apNumberTexture));	//UI�p�e�N�X�`���ւ̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScoreUI::~CScoreUI()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CScoreUI * CScoreUI::Create(void)
{
	//�X�R�A��UI�̃|�C���^
	CScoreUI * pScoreUI = NULL;
	//�����X�R�A��UI�̃|�C���^��NULL�̏ꍇ
	if (pScoreUI == NULL)
	{
		//�X�R�A��UI�̃������m��
		pScoreUI = new CScoreUI;
	}
	//�����������֐��Ăяo��
	pScoreUI->Init();
	return pScoreUI;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CScoreUI::Init(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//�����̃e�N�X�`���̐��������֐��Ăяo��
		m_apNumberTexture[nCount] = CUINumberTexture::Create(D3DXVECTOR3(POSITION.x - (SIZE.x * nCount), POSITION.y, 0.0f),SIZE);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CScoreUI::Uninit(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//���������̃e�N�X�`����NULL����Ȃ��ꍇ
		if (m_apNumberTexture[nCount] != NULL)
		{
			//�����̃e�N�X�`���̏I�������֐��Ăяo��
			m_apNumberTexture[nCount]->Uninit();
			//�����̃e�N�X�`���̃������j��
			delete m_apNumberTexture[nCount];
			//�����̃e�N�X�`����NULL�ɂ���
			m_apNumberTexture[nCount] = NULL;
		}
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CScoreUI::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CScoreUI::Draw(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//�����̃e�N�X�`���̕`�揈���֐��Ăяo��
		m_apNumberTexture[nCount]->Draw();
	}
}

//=============================================================================
// �X�R�A�ݒ�֐�
//=============================================================================
void CScoreUI::SetScore(int nScore)
{
	int integer = MINIMUM_INTEGER;			//�v�Z�p�ϐ�
	int nCntNumber = MINIMUM_COUNT_NUMBER;	//�ԍ��J�E���^
	//�ő包������
	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		//�o�������l�̌����̈��̌����̐������o
		integer = int(nScore / std::pow(NUM_CONVERSION, nCntDigit));
		//�؂�̂Ă��������������|����
		integer = int(integer * std::pow(NUM_CONVERSION, nCntDigit));
		//������ݒ肷���̌����̐����Ɖ��̌����̐����������Ď�菜��
		m_apNumberTexture[nCntNumber]->SetNumber(int((nScore - integer) / std::pow(NUM_CONVERSION, nCntDigit - 1)));
	}
}
