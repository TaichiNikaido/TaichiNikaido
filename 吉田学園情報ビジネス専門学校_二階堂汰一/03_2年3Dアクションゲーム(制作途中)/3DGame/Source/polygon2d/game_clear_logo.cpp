//=============================================================================
//
// �Q�[���N���A���S [game_clear_logo.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_clear_logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/game_clear_logo.png")				//�e�N�X�`���̃p�X
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//�ʒu
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//�T�C�Y
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))								//�F
#define DISPLAY_MINIMUM_TIME (0)											//�\�����Ԃ̍ŏ��l
#define DISPLAY_MAX_TIME (300)												//�\�����Ԃ̍ő�l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameClearLogo::m_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameClearLogo::CGameClearLogo(int nPriority) : CScene2d(nPriority)
{
	m_nDisplayTimeCount = DISPLAY_MINIMUM_TIME;		//�\�����Ԃ̃J�E���g
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameClearLogo::~CGameClearLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CGameClearLogo::TextureLoad(void)
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
void CGameClearLogo::TextureUnload(void)
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
CGameClearLogo * CGameClearLogo::Create(void)
{
	//�Q�[���N���A���S�̃|�C���^
	CGameClearLogo * pGameClearLogo = nullptr;
	//�Q�[���N���A���S�̃|�C���^��nullptr�̏ꍇ
	if (pGameClearLogo == nullptr)
	{
		//�Q�[���N���A���S�̃������m��
		pGameClearLogo = new CGameClearLogo;
		//�Q�[���N���A���S�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGameClearLogo != nullptr)
		{
			//�Q�[���N���A���S�̈ʒu�ݒ�
			pGameClearLogo->SetPosition(POSITION);
			//�Q�[���N���A���S�̃T�C�Y�ݒ�
			pGameClearLogo->SetSize(SIZE);
			//�Q�[���N���A���S�̐F�ݒ�
			pGameClearLogo->SetColor(COLOR);
			//�Q�[���N���A���S�̏����������֐��Ăяo��
			pGameClearLogo->Init();
		}
	}
	//�Q�[���N���A���S�̃|�C���^��Ԃ�
	return pGameClearLogo;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameClearLogo::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2D�V�[���̏����������֐��Ăяo��
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameClearLogo::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameClearLogo::Update(void)
{
	//2D�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//�����\�����Ԃ̃J�E���g���ő�l���z������
	if (m_nDisplayTimeCount >= DISPLAY_MAX_TIME)
	{
		//���U���g���[�h�ɑJ�ڂ���
		CManager::StartFade(CManager::MODE_RESULT);
	}
	//�\�����Ԃ̃J�E���g�����Z����
	m_nDisplayTimeCount++;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameClearLogo::Draw(void)
{
	//2D�V�[���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
