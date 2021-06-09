//=============================================================================
//
// �v���C���[�̗̑�UI [ui_life_player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Mode/mode_game.h"
#include "ui_life_player.h"
#include "Polygon2d/heart_icon.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HEART_LIFE (4)		//1��UI�̗̑�
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 12 + 50.0f * nCount, SCREEN_HEIGHT / 8, 0.0f)	//�ʒu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerLifeUI::CPlayerLifeUI(int nPriority) : CScene(nPriority)
{
	memset(m_pHeartIcon, NULL, sizeof(m_pHeartIcon));		//�n�[�g�A�C�R���̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerLifeUI::~CPlayerLifeUI()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayerLifeUI * CPlayerLifeUI::Create()
{
	//�v���C���[�̗̑�UI�|�C���^
	CPlayerLifeUI * pPlayerLifeUI = nullptr;
	//�v���C���[�̗̑�UI�|�C���^��nullptr�̏ꍇ
	if (pPlayerLifeUI == nullptr)
	{
		//�v���C���[�̗̑�UI�̃������m��
		pPlayerLifeUI = new CPlayerLifeUI;
		//�v���C���[�̗̑�UI�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pPlayerLifeUI != nullptr)
		{
			//�v���C���[�̗̑�UI�̏����������֐��Ăяo��
			pPlayerLifeUI->Init();
		}
	}
	//�v���C���[�̗̑�UI�̃|�C���^��Ԃ�
	return pPlayerLifeUI;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayerLifeUI::Init(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̗̑͂��擾
		int nPlayerLife = pPlayer->GetLife();
		//�n�[�g�A�C�R���̐����������߂�
		m_nHeartIconCreateCount = nPlayerLife / HEART_LIFE;
		//�n�[�g�A�C�R���̐���������
		for (int nCount = 0; nCount < m_nHeartIconCreateCount; nCount++)
		{
			//�n�[�g�A�C�R���̐���
			m_pHeartIcon[nCount] = CHeartIcon::Create(POSITION));
			//�n�[�g�A�C�R���̃p�^�[���A�j����ݒ肷��(��΂�1�ɂ���)
			m_pHeartIcon[nCount]->SetPatternAnime(4);
		}
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayerLifeUI::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayerLifeUI::Update(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̗̑͂��擾
		int nPlayerLife = pPlayer->GetLife();
		//���݂̊��S�ɕ\������n�[�g�̌������߂�
		int nHeart = nPlayerLife / HEART_LIFE;
		//�c��̕\������n�[�g�̃��C�t
		int nHeartLife = nPlayerLife % HEART_LIFE;
		//����������
		for (int nCount = 0; nCount < m_nHeartIconCreateCount; nCount++)
		{
			//�n�[�g�A�C�R���̐F�����ɂ���
			m_pHeartIcon[nCount]->SetPatternAnime(0);
		}
		//�n�[�g�A�C�R���̐���������
		for (int nCount = 0; nCount < nHeart; nCount++)
		{
			//�n�[�g�A�C�R���̐F��Ԃɂ���
			m_pHeartIcon[nCount]->SetPatternAnime(4);
		}
		//�������̒l����������菬�����ꍇ
		if (nHeart < m_nHeartIconCreateCount)
		{
			//�����]��̒l��0�ł͂Ȃ��ꍇ
			if (nHeartLife > 0)
			{
				//�]��̏������Ԃ�����
				m_pHeartIcon[nHeart]->SetPatternAnime(nHeartLife);
			}
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayerLifeUI::Draw(void)
{
}
