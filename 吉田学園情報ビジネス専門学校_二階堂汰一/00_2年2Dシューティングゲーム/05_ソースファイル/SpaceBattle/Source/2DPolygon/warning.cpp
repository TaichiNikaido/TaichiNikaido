//=============================================================================
//
// �x�� [warning.cpp]
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
#include "Base/text.h"
#include "warning.h"
#include "Player/player.h"
#include "Enemy/enemy_dragon.h"
#include "Bullet/bullet_fireball.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/warning.png")
#define SIZE (D3DXVECTOR3(920.0f,270.0f,0.0f))
#define RED_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define YELLOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define MINIMUM_COLOR_CHANGE_TIME (0)
#define MINIMUM_COLOR_CHANGE_COUNT (0)
#define INIT_POSITION (D3DXVECTOR3(DragonPosition.x, PlayerPosition.y, 0.0f))
#define COLOR_CHANGE_TIME (10)
#define COLOR_CHANGE_COUNT (2)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWarning::CWarning()
{
	m_nColorChangeTime = MINIMUM_COLOR_CHANGE_TIME;					//�F��ύX���鎞��
	m_nColorChangeCount = MINIMUM_COLOR_CHANGE_COUNT;				//�F��ύX����J�E���g
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWarning::~CWarning()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CWarning::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CWarning::TextureUnload(void)
{
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CWarning * CWarning::Create(void)
{
	//�x���̃|�C���^
	CWarning * pWarning = NULL;
	//�����x���̃|�C���^��NULL�̏ꍇ
	if (pWarning == NULL)
	{
		//�x���̃������m��
		pWarning = new CWarning;
		//�����x���̃|�C���^��NULL����Ȃ��ꍇ
		if (pWarning != NULL)
		{
			//�����������֐��Ăяo��
			pWarning->Init();
		}
	}
	//�x���̃|�C���^��Ԃ�
	return pWarning;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CWarning::Init()
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//�h���S�����擾
	CEnemyDragon * pDragon = CGameMode::GetDragon();
	//�h���S���̈ʒu���擾
	D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
	//2D�V�[�������������֐��Ăяo��
	CScene2d::Init();
	//�ʒu�̏����ݒ�
	SetPosition(INIT_POSITION);
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CWarning::Uninit()
{
	//2D�V�[���I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CWarning::Update()
{
	//2D�V�[���X�V�����֐��Ăяo��
	CScene2d::Update();
	//�ʒu�ݒ菈���֐��Ăяo��
	Position();
	//�F�ύX�����֐��Ăяo��
	ColorChange();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CWarning::Draw()
{
	//2D�V�[���`�揈���֐��Ăяo��
	CScene2d::Draw();
}

//=============================================================================
// �ʒu���菈���֐�
//=============================================================================
void CWarning::Position(void)
{
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�h���S�����擾
	CBulletFireball * pBulletFireBall = CGameMode::GetBulletFireBall();
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//�΋��̈ʒu���擾
	D3DXVECTOR3 FireBallPosition = pBulletFireBall->GetPosition();
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//X���W���h���S����X���W�ɍ��킹��
	Position.x = FireBallPosition.x;
	//Y���W���v���C���[��Y���W�ɍ��킹��
	Position.y = PlayerPosition.y;
	//�ʒu��ݒ肷��
	SetPosition(Position);
}

//=============================================================================
// �F�ύX�����֐�
//=============================================================================
void CWarning::ColorChange(void)
{
	//�����F�ύX���ԂɂȂ�����
	if (m_nColorChangeTime % COLOR_CHANGE_TIME == REMAINDER)
	{
		//�F���J�E���g�ɍ��킹�ĕύX����
		if (m_nColorChangeCount % COLOR_CHANGE_COUNT == REMAINDER)
		{
			//�F��ݒ肷��
			SetColor(YELLOW_COLOR);
		}
		else
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				//�F��ݒ肷��
				SetColor(RED_COLOR);
			}
		}
		//�F��ύX����J�E���g�����Z����
		m_nColorChangeCount++;
	}
	//�F��ύX���鎞�Ԃ����Z����
	m_nColorChangeTime++;
}
