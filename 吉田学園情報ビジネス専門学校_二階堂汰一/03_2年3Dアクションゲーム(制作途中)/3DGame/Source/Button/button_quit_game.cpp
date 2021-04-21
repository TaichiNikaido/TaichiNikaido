//=============================================================================
//
// �Q�[���ɖ߂�{�^�� [button_quit_game.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "button_quit_game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_ReturnGame.png")		//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CQuitGameButton::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CQuitGameButton::CQuitGameButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CQuitGameButton::~CQuitGameButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CQuitGameButton::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	//�f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					//�t�@�C���̖��O
		&m_pTexture);					//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CQuitGameButton::TextureUnload(void)
{
	//�����e�N�X�`���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CQuitGameButton * CQuitGameButton::Create(D3DXVECTOR3 Position)
{
	//�Q�[���ɖ߂�{�^���̃|�C���^
	CQuitGameButton * pQuitGameButton = nullptr;
	//�Q�[���ɖ߂�{�^���|�C���^��nullptr�̏ꍇ
	if (pQuitGameButton == nullptr)
	{
		//�Q�[���ɖ߂�{�^���̃������m��
		pQuitGameButton = new CQuitGameButton;
		//�Q�[���ɖ߂�{�^���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pQuitGameButton != nullptr)
		{
			//�Q�[���ɖ߂�{�^���̈ʒu�ݒ�
			pQuitGameButton->SetPosition(Position);
			//�Q�[���ɖ߂�{�^���̏����������֐��Ăяo��
			pQuitGameButton->Init();
		}
	}
	//�Q�[���ɖ߂�{�^���̃|�C���^��Ԃ�
	return pQuitGameButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CQuitGameButton::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�{�^���̏����������֐��Ăяo��
	CButton::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CQuitGameButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CQuitGameButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CQuitGameButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CQuitGameButton::Press(void)
{
	//�`���[�g���A�����[�h�̎擾
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pSound != nullptr)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//�����`���[�g���A�����[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pTutorialMode != nullptr)
	{
		//�|�[�Y���g�p��Ԃɂ���
		pTutorialMode->SetbPouse(false);
	}
	//�����Q�[�����[�h�̃|�C���^��nullptr����Ȃ��ꍇ
	if (pGameMode != nullptr)
	{
		//�|�[�Y���g�p��Ԃɂ���
		pGameMode->SetbPouse(false);
	}
}