//=============================================================================
//
// �n�[�g�A�C�R�� [heart_icon.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "heart_icon.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/heart_icon.png")			//�e�N�X�`���p�X
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))					//�T�C�Y
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					//�F
#define ANIMATION_VALUE (0.2f)									//�A�j���[�V�����̒l
#define MINIMUM_PATTERN_ANIME (0)								//�p�^�[���A�j���̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHeartIcon::m_pTexture = nullptr;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHeartIcon::CHeartIcon(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//�p�^�[���A�j��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHeartIcon::~CHeartIcon()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CHeartIcon::TextureLoad(void)
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
void CHeartIcon::TextureUnload(void)
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
// ���������֐��Ăяo��
//=============================================================================
CHeartIcon * CHeartIcon::Create(D3DXVECTOR3 Position)
{
	//�|�[�Y�w�i�̃|�C���^
	CHeartIcon * pHeartIcon = nullptr;
	//�|�[�Y�w�i�̃|�C���^��nullptr�̏ꍇ
	if (pHeartIcon == nullptr)
	{
		//�|�[�Y�w�i�̃������m��
		pHeartIcon = new CHeartIcon;
		//�|�[�Y�w�i�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pHeartIcon != nullptr)
		{
			//�|�[�Y�w�i�̈ʒu�ݒ�
			pHeartIcon->SetPosition(Position);
			//�|�[�Y�w�i�̃T�C�Y�ݒ�
			pHeartIcon->SetSize(SIZE);
			//�|�[�Y�w�i�̐F�ݒ�
			pHeartIcon->SetColor(COLOR);
			//�|�[�Y�w�i�̏����������֐��Ăяo��
			pHeartIcon->Init();
		}
	}
	//�|�[�Y�w�i�̃|�C���^��Ԃ�
	return pHeartIcon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CHeartIcon::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
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
void CHeartIcon::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CHeartIcon::Update(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//2D�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CHeartIcon::Draw(void)
{
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����Q�[�����[�h�̃|�C���^��nullptr�ł͂Ȃ����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pGameMode != nullptr && pPlayer != nullptr)
	{
		//�����|�[�Y����������ĂȂ����v���C���[�����S��Ԃł͂Ȃ��ꍇ
		if (pGameMode->GetbCreatePause() == false && pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//2D�V�[���̕`�揈���֐��Ăяo��
			CScene2d::Draw();
		}
	}
}