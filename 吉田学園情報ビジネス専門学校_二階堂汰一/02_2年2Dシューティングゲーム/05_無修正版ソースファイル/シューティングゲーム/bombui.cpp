//=============================================================================
//
// ���e��UI���� [bombui.cpp]
// Author: ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "bombtexture.h"
#include "bomb.h"
#include "bombui.h"
#include <cmath>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBombUI::CBombUI(int nPriority) :CScene(nPriority)
{
	memset(m_apBombUI, 0, sizeof(m_apBombUI));
	m_nBombUI = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBombUI::~CBombUI()
{
}

//=============================================================================
// ����
//=============================================================================
CBombUI * CBombUI::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CBombUI * pBombUI;
	pBombUI = new CBombUI;
	pBombUI->Init(pos, SizeWidth, SizeHeight);
	return pBombUI;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBombUI::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
	{
		m_apBombUI[nCount] = CBombTexture::Create(D3DXVECTOR3(pos.x + (SizeWidth * nCount), pos.y, 0.0f), SizeWidth, SizeHeight);
	}

	m_nBombUI = 0;	//���e��UI
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBombUI::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBombUI::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBombUI::Draw(void)
{
	for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
	{
		m_apBombUI[nCount]->Draw();
	}
}

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CBombUI::SetBombUI(int nBomb)
{
	//�������e��UI���ő吔�ȉ���������
	if (m_nBombUI <= PLAYER_MAX_BOMB)
	{
		//���e��UI�Ɉ�������
		m_nBombUI = nBomb;

		for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
		{
			m_apBombUI[nCount]->SetBombTexture(100);
		}

		for (int nCount = 0; nCount < m_nBombUI; nCount++)
		{
			m_apBombUI[nCount]->SetBombTexture(255);
		}
	}
}

//=============================================================================
// ���Z�֐�
//=============================================================================
void CBombUI::AddBombUI(int nValue)
{
	//���e��UI�Ɉ��������Z����
	m_nBombUI += nValue;
	//���e��UI���Z�b�g
	SetBombUI(m_nBombUI);
}

//=============================================================================
// ���Z�֐�
//=============================================================================
void CBombUI::SubBombUI(int nValue)
{
	//���e��UI�Ɉ��������Z����
	m_nBombUI -= nValue;
	//���e��UI���Z�b�g
	SetBombUI(m_nBombUI);
}
