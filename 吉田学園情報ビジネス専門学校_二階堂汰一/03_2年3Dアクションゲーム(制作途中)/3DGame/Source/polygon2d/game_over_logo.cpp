//=============================================================================
//
// �Q�[���I�[�o�[���S [game_over_logo.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_over_logo.h"
#include "game_over_bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/game_over_logo.png")						//�e�N�X�`���̃p�X
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))				//�ʒu
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 3,0.0f))					//�T�C�Y
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,0.1f))										//�F
#define MINIMUM_ALPHA (0.0f)														//�A���t�@�l�̍ŏ��l
#define MAX_ALPHA (1.0f)															//�A���t�@�l�̍ő�l
#define ADD_ALPHA (0.005f)															//�A���t�@�l�̉��Z��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameOverLogo::m_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameOverLogo::CGameOverLogo(int nPriority) : CScene2d(nPriority)
{
	m_fAlpha = MINIMUM_ALPHA;		//�A���t�@�l
	m_fAddAlpha = MINIMUM_ALPHA;	//���Z����A���t�@�l
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameOverLogo::~CGameOverLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CGameOverLogo::TextureLoad(void)
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
void CGameOverLogo::TextureUnload(void)
{
	//�����e�N�X�`���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`���̃|�C���^��nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CGameOverLogo * CGameOverLogo::Create(void)
{
	//�Q�[���I�[�o�[���S�̃|�C���^
	CGameOverLogo * pGameOverLogo = nullptr;
	//�Q�[���I�[�o�[���S�̃|�C���^��nullptr�̏ꍇ
	if (pGameOverLogo == nullptr)
	{
		//�Q�[���I�[�o�[���S�̃������m��
		pGameOverLogo = new CGameOverLogo;
		//�Q�[���I�[�o�[���S�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGameOverLogo != nullptr)
		{
			//�Q�[���I�[�o�[���S�̈ʒu�ݒ�
			pGameOverLogo->SetPosition(POSITION);
			//�Q�[���I�[�o�[���S�̃T�C�Y�ݒ�
			pGameOverLogo->SetSize(SIZE);
			//�Q�[���I�[�o�[���S�̐F�ݒ�
			pGameOverLogo->SetColor(COLOR);
			//�Q�[���I�[�o�[���S�̏����������֐��Ăяo��
			pGameOverLogo->Init();
		}
	}
	//�Q�[���I�[�o�[���S�̃|�C���^��Ԃ�
	return pGameOverLogo;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameOverLogo::Init(void)
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
	//�Q�[���I�[�o�[�w�i�̐���
	CGameOverBG::Create();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameOverLogo::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameOverLogo::Update(void)
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
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameOverLogo::Draw(void)
{
	//2D�V�[���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
