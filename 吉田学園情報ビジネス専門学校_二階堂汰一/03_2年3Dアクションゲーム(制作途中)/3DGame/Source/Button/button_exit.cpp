//=============================================================================
//
// �I���{�^�� [button_exit.cpp]
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
#include "button_exit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_ENGLISH_PASS ("Data/Texture/Button/Button_English_Exit.png")	//�e�N�X�`���̃p�X
#define TEXTURE_JAPANESE_PASS ("Data/Texture/Button/Button_Japanese_Exit.png")	//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExitButton::m_apTexture[TEXTURE_MAX] = {};	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExitButton::CExitButton()
{
	m_TextureType = TEXTURE_NONE;	//�e�N�X�`���̎��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExitButton::~CExitButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CExitButton::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		//�f�o�C�X�ւ̃|�C���^
		TEXTURE_ENGLISH_PASS,				//�t�@�C���̖��O
		&m_apTexture[TEXTURE_ENGLISH]);		//�ǂݍ��ރ������[
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		//�f�o�C�X�ւ̃|�C���^
		TEXTURE_JAPANESE_PASS,				//�t�@�C���̖��O
		&m_apTexture[TEXTURE_JAPANESE]);	//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CExitButton::TextureUnload(void)
{
	//�e�N�X�`���̍ő吔����
	for (int nCount = TEXTURE_ENGLISH; nCount < TEXTURE_MAX; nCount++)
	{
		//�����e�N�X�`���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_apTexture[nCount] != nullptr)
		{
			//�e�N�X�`���̔j�������֐��Ăяo��
			m_apTexture[nCount]->Release();
			//�e�N�X�`����nullptr�ɂ���
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CExitButton * CExitButton::Create(D3DXVECTOR3 Position, TEXTURE_TYPE TextureType)
{
	//�I���{�^���̃|�C���^
	CExitButton * pExitButton = nullptr;
	//�I���{�^���̃|�C���^��nullptr�̏ꍇ
	if (pExitButton == nullptr)
	{
		//�I���{�^���̃������m��
		pExitButton = new CExitButton;
		//�I���{�^���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pExitButton != nullptr)
		{
			//�I���{�^���̈ʒu�ݒ�
			pExitButton->SetPosition(Position);
			//�e�N�X�`���̎�ނ�ݒ�
			pExitButton->m_TextureType = TextureType;
			//�I���{�^���̏����������֐��Ăяo��
			pExitButton->Init();
		}
	}
	//�I���{�^���̃|�C���^��Ԃ�
	return pExitButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExitButton::Init(void)
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
	BindTexture(m_apTexture[m_TextureType]);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExitButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExitButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExitButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CExitButton::Press(void)
{
	//�������Ƃ��̃T�E���h�Đ�
	PlayButtonSE(CButton::BUTTON_SE_PUSH);
	//�I��������
	exit(0);
}
