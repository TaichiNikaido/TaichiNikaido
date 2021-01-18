//=============================================================================
//
// �X�R�A���� [Score.cpp]
// Author: ��K������
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "player.h"
#include <cmath>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) :CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;	//�X�R�A
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight)
{
	CScore * pScore;
	pScore = new CScore;
	pScore->Init(pos, SizeWidth, SizeHeight);
	return pScore;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight)
{

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x - (SizeWidth * nCount), pos.y, 0.0f), SizeHeight, SizeWidth);
	}
	m_nScore = 0;	//�X�R�A
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//Uninit,delete,NULL���
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CScore::Update(void)
{
	CPlayer::SetPlayerScpre(m_nScore);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
// ���Z�֐�
//=============================================================================
void CScore::AddScore(int nValue)
{
	//�X�R�A�Ɉ����̒l�����Z
	m_nScore += nValue;
	//�X�R�A���Z�b�g����
	SetScore(m_nScore);
}

void CScore::SubScore(int nValue)
{
	//�X�R�A�Ɉ����̒l�����Z
	m_nScore -= nValue;
	//�X�R�A���Z�b�g����
	SetScore(m_nScore);
}

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CScore::SetScore(int nScore)
{
	//�X�R�A�Ɉ�������
	m_nScore = nScore;

	int integer = 0;	//�v�Z�p�ϐ�
	int nCntNumber = 0;	//�ԍ��J�E���^

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nScore / std::pow(10.0f, nCntDigit)); //1�̈ʈȉ���؂�̂Ă�
		integer = int(integer * std::pow(10.0f, nCntDigit));
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}