//=============================================================================
//
// �x�� [warning.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "text.h"
#include "warning.h"
#include "player.h"
#include "enemy_dragon.h"
#include "bullet_fireball.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/warning.png")
#define SIZE (D3DXVECTOR3(920.0f,270.0f,0.0f))
#define RED_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define YELLOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWarning::CWarning()
{
	m_nColorChangeTime = 0;					//�F��ύX���鎞��
	m_nColorChangeCount = 0;				//�F��ύX����J�E���g
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
	CRenderer *pRenderer = CManager::GetRenderer();
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
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CWarning * CWarning::Create(void)
{
	CWarning * pWarning;
	pWarning = new CWarning;
	pWarning->Init();
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
	SetPosition(D3DXVECTOR3(DragonPosition.x, PlayerPosition.y, 0.0f));
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
	CEnemyDragon * pDragon = CGameMode::GetDragon();
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
	//�΋��̈ʒu���擾
	D3DXVECTOR3 FireBallPosition = pDragon->GetBulletFireBall()->GetPosition();
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
	if (m_nColorChangeTime % 10 == 0)
	{
		if (m_nColorChangeCount % 2 == 0)
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
