//=============================================================================
//
// ���[���z�[�� [wormhole.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "mode_game.h"
#include "wormhole.h"
#include "enemy_dragon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WORMHOLE ("Data/Texture/wormhole/wormhole.png")
#define WORMHOLE_EFFECT ("Data/Texture/wormhole/wormhole_effect.png")
#define ADD_SCALE (0.01f)
#define SUB_SCALE (0.01f)
#define WORMHOLE_EFFECT_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define WORMHOLE_SIZE (D3DXVECTOR3(200.0f,200.0f,0.0f))
#define WORMHOLE_EFFECT_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define WORMHOLE_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define MAX_SCALE (2.0f)
#define MINIMUM_SCALE (0.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWormhole::m_apTexture[2] = {};	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWormhole::CWormhole(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2d, NULL, sizeof(m_apScene2d));	//�V�[��2D�ւ̃|�C���^
	m_bSpawn = false;								//�X�|�[��������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWormhole::~CWormhole()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CWormhole::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		WORMHOLE_EFFECT,							// �t�@�C���̖��O
		&m_apTexture[TEXTURE_WORMHOLE]);				// �ǂݍ��ރ������[
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		WORMHOLE,									// �t�@�C���̖��O
		&m_apTexture[TEXTURE_WORMHOLE_EFFECT]);		// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CWormhole::TextureUnload(void)
{
	//�ő�e�N�X�`��������
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
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
CWormhole * CWormhole::Create(D3DXVECTOR3 Position)
{
	//���[���z�[���̃|�C���^
	CWormhole * pWormhole = NULL;
	//�������[���z�[����NULL�̏ꍇ
	if (pWormhole == NULL)
	{
		//���[���z�[���̃������m��
		pWormhole = new CWormhole;
	}
	//�������[���z�[����NULL����Ȃ��ꍇ
	if (pWormhole != NULL)
	{
		//�����������֐��Ăяo��
		pWormhole->Init();
		//�e�N�X�`���̍ő吔����
		for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
		{
			//�ʒu��ݒ肷��
			pWormhole->m_apScene2d[nCount]->SetPosition(Position);
		}
	}
	//���[���z�[���̃|�C���^��Ԃ�
	return pWormhole;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CWormhole::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//�����V�[��2D��NULL�̏ꍇ
		if (m_apScene2d[nCount] == NULL)
		{
			//�V�[��2D�̃������m��
			m_apScene2d[nCount] = new CScene2d(2);
		}
		//�V�[��2D�̏����������֐��Ăяo��
		m_apScene2d[nCount]->Init();
	}
	//�T�C�Y�̏����ݒ�
	m_apScene2d[TEXTURE_WORMHOLE]->SetSize(WORMHOLE_SIZE);
	//�F�̏����ݒ�
	m_apScene2d[TEXTURE_WORMHOLE]->SetColor(WORMHOLE_COLOR);
	//�T�C�Y�̏����ݒ�
	m_apScene2d[TEXTURE_WORMHOLE_EFFECT]->SetSize(WORMHOLE_EFFECT_SIZE);
	//�F�̏����ݒ�
	m_apScene2d[TEXTURE_WORMHOLE_EFFECT]->SetColor(WORMHOLE_EFFECT_COLOR);
	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		m_apScene2d[nCount]->SetTexture(aTexture);
		//�e�N�X�`���̊��蓖��
		m_apScene2d[nCount]->BindTexture(m_apTexture[nCount]);
	}
	//�����T�E���h��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�T�E���h�̒�~
		pSound->StopSound();
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CWormhole::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CWormhole::Update(void)
{
	//�g�k�����֐��Ăяo��
	Scale();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CWormhole::Draw(void)
{
}

//=============================================================================
// �g�k�����֐�
//=============================================================================
void CWormhole::Scale(void)
{
	D3DXVECTOR3 Rotation;	//��]
	float fScale;			//�g�k
	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//��]���擾����
		Rotation = m_apScene2d[nCount]->GetRotation();
		//�g�k���擾����
		fScale = m_apScene2d[nCount]->GetScale();
	}
	//��]����
	Rotation.z -= D3DX_PI * 0.01f;
	//������]���~�������z������
	if (Rotation.z >= D3DX_PI)
	{
		//��]��������
		Rotation.z += D3DX_PI * 2.0f;
	}
	//�����g�k���ő�ɂȂ肩�X�|�[�����Ă��Ȃ��ꍇ
	if (fScale <= MAX_SCALE && m_bSpawn == false)
	{
		//�g�傷��
		fScale += ADD_SCALE;
	}
	else
	{
		//�����X�|�[�����Ă��Ȃ�������
		if (m_bSpawn == false)
		{
			//�X�|�[�������֐��Ăяo��
			Spawn();
		}
	}
	//�����X�|�[��������
	if (m_bSpawn == true)
	{
		//�k������
		fScale -= SUB_SCALE;
		//�g�嗦��0�ȉ��ɂȂ�����
		if (fScale <= MINIMUM_SCALE)
		{
			//�I�������֐��Ăяo��
			Uninit();
			return;
		}
	}
	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//��]�̐ݒ�
		m_apScene2d[nCount]->SetRotation(Rotation);
		//�g�k�̐ݒ�
		m_apScene2d[nCount]->SetScale(fScale);
	}
}

//=============================================================================
// �X�|�[�������֐�
//=============================================================================
void CWormhole::Spawn(void)
{
	//�X�|�[����^�ɂ���
	m_bSpawn = true;
	//�ʒu���擾
	D3DXVECTOR3 Position = m_apScene2d[TEXTURE_WORMHOLE]->GetPosition();
	//�h���S���̐��������֐��Ăяo��
	CGameMode::SetDragon(CEnemyDragon::Create(Position));
}
