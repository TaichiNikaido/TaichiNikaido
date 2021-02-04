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
	CScoreUI * pScoreUI;
	pScoreUI = new CScoreUI;
	pScoreUI->Init();
	return pScoreUI;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CScoreUI::Init(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumberTexture[nCount] = CUINumberTexture::Create(D3DXVECTOR3(POSITION.x - (SIZE.x * nCount), POSITION.y, 0.0f),SIZE);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CScoreUI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumberTexture[nCount] != NULL)
		{
			//Uninit,delete,NULL���
			m_apNumberTexture[nCount]->Uninit();
			delete m_apNumberTexture[nCount];
			m_apNumberTexture[nCount] = NULL;
		}
	}
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
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumberTexture[nCount]->Draw();
	}
}

//=============================================================================
// �X�R�A�ݒ�֐�
//=============================================================================
void CScoreUI::SetScore(int nScore)
{
	int integer = 0;	//�v�Z�p�ϐ�
	int nCntNumber = 0;	//�ԍ��J�E���^

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(nScore / std::pow(10.0f, nCntDigit)); //1�̈ʈȉ���؂�̂Ă�
		integer = int(integer * std::pow(10.0f, nCntDigit));
		m_apNumberTexture[nCntNumber]->SetNumber(int((nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}
