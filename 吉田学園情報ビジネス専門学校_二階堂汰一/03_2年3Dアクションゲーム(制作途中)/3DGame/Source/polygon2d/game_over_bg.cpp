//=============================================================================
//
// �Q�[���I�[�o�[�w�i [game_over_bg.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_over_bg.h"
#include "Button/game_over_button_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//�ʒu
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//�T�C�Y
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.1f))								//�F
#define BUTTON_MANAGER_CREATE_MINIMUM_COUNT (0)								//�{�^���}�l�[�W���[�̐����J�E���g�̍ŏ��l
#define BUTTON_MANAGER_CREATE_MAX_COUNT (1)									//�{�^���}�l�[�W���[�̐����J�E���g�̍ő�l
#define BUTTON_MANAGER_CREATE_MINIMUM_TIME (0)								//�{�^���}�l�[�W���[�̐����^�C�~���O�̍ŏ��l
#define BUTTON_MANAGER_CREATE_MAX_TIME (100)								//�{�^���}�l�[�W���[�̐����^�C�~���O�̍ő�l
#define BUTTON_MANAGER_CREATE_ADD_TIME (5)									//�{�^���}�l�[�W���[�̐����^�C�~���O�̉��Z�n
#define MINIMUM_ALPHA (0.0f)												//�A���t�@�l�̍ŏ��l
#define MAX_ALPHA (1.0f)													//�A���t�@�l�̍ő�l
#define ADD_ALPHA (0.0035f)													//�A���t�@�l�̉��Z��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameOverBG::CGameOverBG(int nPriority) : CScene2d(nPriority)
{
	m_nButtonCreateTime = BUTTON_MANAGER_CREATE_MINIMUM_TIME;		//�{�^���}�l�[�W���[�̐����^�C�~���O
	m_nButtonCreateCount = BUTTON_MANAGER_CREATE_MINIMUM_COUNT;		//�{�^���}�l�[�W���[�̐����J�E���g
	m_fAlpha = MINIMUM_ALPHA;										//�A���t�@�l
	m_fAddAlpha = MINIMUM_ALPHA;									//���Z����A���t�@�l
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameOverBG::~CGameOverBG()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CGameOverBG * CGameOverBG::Create(void)
{
	//�Q�[���I�[�o�[�w�i�̃|�C���^
	CGameOverBG * pGameOverBG = nullptr;
	//�Q�[���I�[�o�[�w�i�̃|�C���^��nullptr�̏ꍇ
	if (pGameOverBG == nullptr)
	{
		//�Q�[���I�[�o�[�w�i�̃������m��
		pGameOverBG = new CGameOverBG;
		//�Q�[���I�[�o�[�w�i�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGameOverBG != nullptr)
		{
			//�Q�[���I�[�o�[�w�i�̈ʒu�ݒ�
			pGameOverBG->SetPosition(POSITION);
			//�Q�[���I�[�o�[�w�i�̃T�C�Y�ݒ�
			pGameOverBG->SetSize(SIZE);
			//�Q�[���I�[�o�[�w�i�̐F�ݒ�
			pGameOverBG->SetColor(COLOR);
			//�Q�[���I�[�o�[�w�i�̏����������֐��Ăяo��
			pGameOverBG->Init();
		}
	}
	//�Q�[���I�[�o�[�w�i�̃|�C���^��Ԃ�
	return pGameOverBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameOverBG::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2D�V�[���̏����������֐��Ăяo��
	CScene2d::Init();
	//�A���t�@�l�̉��Z�ʂ�ݒ�
	m_fAddAlpha = ADD_ALPHA;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameOverBG::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameOverBG::Update(void)
{
	//2D�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//�����A���t�@�`���ő�l��艺�̏ꍇ
	if (m_fAlpha < MAX_ALPHA)
	{
		//�A���t�@�l�����Z����
		m_fAlpha += m_fAddAlpha;
		//�F��ݒ肷��
		SetColor(D3DXCOLOR(COLOR.r, COLOR.g, COLOR.b, m_fAlpha));
	}
	else
	{
		//�{�^���}�l�[�W���[�����^�C�~���O�����Z����
		m_nButtonCreateTime += BUTTON_MANAGER_CREATE_ADD_TIME;
		//�����{�^���}�l�[�W���[�����^�C�~���O���ő�l�ȏォ�{�^�������J�E���g���ŏ��l�ɂȂ����ꍇ
		if (m_nButtonCreateTime >= BUTTON_MANAGER_CREATE_MAX_TIME && m_nButtonCreateCount == BUTTON_MANAGER_CREATE_MINIMUM_COUNT)
		{
			//�{�^���}�l�[�W�������J�E���g���ő�l�ɂ���
			m_nButtonCreateCount = BUTTON_MANAGER_CREATE_MAX_COUNT;
			//�����{�^���}�l�[�W�������J�E���g���ő�l�ɂȂ����ꍇ
			if (m_nButtonCreateCount == BUTTON_MANAGER_CREATE_MAX_COUNT)
			{
				//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̐���
				CGameOverButtonManager::Create();
			}
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameOverBG::Draw(void)
{
	//2D�V�[���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
