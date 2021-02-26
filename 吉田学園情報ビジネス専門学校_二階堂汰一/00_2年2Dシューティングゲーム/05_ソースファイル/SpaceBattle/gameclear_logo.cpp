//=============================================================================
//
// �Q�[���N���A���S [gameclear_logo.cpp]
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
#include "gameclear_logo.h"
#include "player.h"
#include "enemy.h"
#include "bullet_fireball.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/gameclear_logo.png")
#define SIZE (D3DXVECTOR3(1000.0f,300.0f,0.0f))
#define INIT_COUNT (0)
#define INIT_TIME (0)
#define CLEAR_TIMNE (200)
#define SHOW_COLOR (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define HIDE_COLOR (D3DXCOLOR(0.0f,1.0f,1.0f,0.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameClearLogo::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameClearLogo::CGameClearLogo(int nPriority)
{
	m_nCount = INIT_COUNT;	//�J�E���g
	m_nTime = INIT_TIME;	//����
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
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE,									// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CGameClearLogo::TextureUnload(void)
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
CGameClearLogo * CGameClearLogo::Create(D3DXVECTOR3 Position)
{
	//�Q�[���N���A���S�̃|�C���^
	CGameClearLogo * pWarning = NULL;
	//�����Q�[���N���A���S�̃|�C���^��NULL�̏ꍇ
	if (pWarning == NULL)
	{
		//�Q�[���N���A���S�̃������m��
		pWarning = new CGameClearLogo;
		//�����Q�[���N���A���S�̃|�C���^��NULL����Ȃ��ꍇ
		if (pWarning != NULL)
		{
			//�ʒu���w�肷��
			pWarning->SetPosition(Position);
			//�����������֐��Ăяo��
			pWarning->Init();
		}
	}
	//�Q�[���N���A���S�̃|�C���^��Ԃ�
	return pWarning;
}

//=============================================================================
// ���������֐�
//=============================================================================
HRESULT CGameClearLogo::Init()
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2D�V�[�������������֐��Ăяo��
	CScene2d::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�F�̏����ݒ�
	SetColor(SHOW_COLOR);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameClearLogo::Uninit()
{
	//2D�V�[���I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameClearLogo::Update()
{
	//2D�V�[���X�V�����֐��Ăяo��
	CScene2d::Update();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�J�E���g�����Z����
	m_nCount++;
	//���Ԃ�i�߂�
	m_nTime++;
	//�w�肵���Ԋu���Ƃ�
	if (m_nCount % 20 == 0)
	{
		SetColor(SHOW_COLOR);
	}
	else if (m_nCount % 41 == 0)
	{
		SetColor(HIDE_COLOR);
	}
	if (m_nTime == CLEAR_TIMNE)
	{
		//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
		if (pPlayer != NULL)
		{
			//�v���C���[�̏��������֐��Ăяo��
			pPlayer->Clear();
		}
	}
	//�e�`�G�̃v���C�I���e�B����
	for (int nCountPriority = PRIORITY_BULLET; nCountPriority <= PRIORITY_ENEMY; nCountPriority++)
	{
		//�V�[���̑�������
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//�V�[���̎擾
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//�����V�[����NULL����Ȃ��ꍇ
			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE ObjType = pScene->GetObjType();
				//�����I�u�W�F�N�g�^�C�v���G��������
				if (ObjType == OBJTYPE_ENEMY)
				{
					//�G�̃|�C���^�擾
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//�����G�̃|�C���^��NULL����Ȃ��ꍇ
					if (pEnemy != NULL)
					{
						//�G�̏I�������֐��Ăяo��
						pEnemy->Uninit();
					}
				}
				//�����I�u�W�F�N�g�^�C�v���΋���������
				if (ObjType == OBJTYPE_FIRE_BALL)
				{
					//�΋��̃|�C���^�擾
					CBulletFireball * pBulletFireball = dynamic_cast<CBulletFireball*> (pScene);
					//�΋��̃|�C���^��NULL����Ȃ��ꍇ
					if (pBulletFireball != NULL)
					{
						//�΋��̏I�������֐��Ăяo��
						pBulletFireball->Uninit();
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameClearLogo::Draw()
{
	//2D�V�[���`�揈���֐��Ăяo��
	CScene2d::Draw();
}
