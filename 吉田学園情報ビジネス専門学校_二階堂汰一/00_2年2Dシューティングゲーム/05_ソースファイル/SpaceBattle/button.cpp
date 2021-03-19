//=============================================================================
//
// �{�^�� [button.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <cmath>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE (D3DXVECTOR3(431.0f,83.0f,0.0f))							//�T�C�Y
#define SHOW_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						//������F
#define HIDE_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.3f))						//�኱������F
#define PLAY_BUTTON_TEXTURE ("Data/Texture/Button/button_play.png")		//�v���C�{�^���̃e�N�X�`��
#define REPLAY_BUTTON_TEXTURE ("Data/Texture/Button/button_replay.png")	//���v���C�{�^���̃e�N�X�`��
#define EXIT_BUTTON_TEXTRUE ("Data/Texture/Button/button_exit.png")		//�I���{�^���̃e�N�X�`��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CButton::m_apTexture[BUTTON_MAX] = {};	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CButton::CButton(int nPriority)
{
	m_Button = BUTTON_NONE;	//�{�^�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CButton::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		PLAY_BUTTON_TEXTURE,				// �t�@�C���̖��O
		&m_apTexture[BUTTON_PLAY]);			// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		REPLAY_BUTTON_TEXTURE,				// �t�@�C���̖��O
		&m_apTexture[BUTTON_REPLAY]);		// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		EXIT_BUTTON_TEXTRUE,				// �t�@�C���̖��O
		&m_apTexture[BUTTON_EXIT]);			// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CButton::TextureUnload(void)
{
	//�{�^���̍ő吔��
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�����e�N�X�`����NULL����Ȃ��ꍇ
		if (m_apTexture[nCount] != NULL)
		{
			//�e�N�X�`���̔j�������֐��Ăяo��
			m_apTexture[nCount]->Release();
			//�e�N�X�`����NULL�ɂ���
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CButton * CButton::Create(D3DXVECTOR3 Positon, BUTTON Button)
{
	//�{�^���̃|�C���^
	CButton * pButton = NULL;
	//�{�^���̃|�C���^��NULL�̏ꍇ
	if (pButton == NULL)
	{
		//�{�^���̃������m��
		pButton = new CButton;
		//�{�^���̃|�C���^��NULL����Ȃ��ꍇ
		if (pButton != NULL)
		{
			//�ʒu��ݒ肷��
			pButton->SetPosition(Positon);
			//�����������֐��Ăяo��
			pButton->Init(Button);
		}
	}
	//�{�^���̃|�C���^��Ԃ�
	return pButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CButton::Init(BUTTON Button)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2d�V�[���̏����������֐��Ăяo��
	CScene2d::Init();
	//�T�C�Y�̐ݒ�
	SetSize(SIZE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_apTexture[Button]);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CButton::Uninit(void)
{
	//2d�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CButton::Update(void)
{
	//2d�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CButton::Draw(void)
{
	//2d�V�[���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CButton::SelectButton(bool bSelect)
{
	//�����I�����ꂽ��
	if (bSelect == true)
	{
		//�F���w�肷��
		D3DXCOLOR Color = SHOW_COLOR;
		//�F��ݒ肷��
		SetColor(Color);
	}
	else
	{
		//�F���w�肷��
		D3DXCOLOR Color = HIDE_COLOR;
		//�F��ݒ肷��
		SetColor(Color);
	}
}