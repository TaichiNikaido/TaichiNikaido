//=============================================================================
//
// ���e�̓G�̓��� [enemy_bomb_body.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "enemy_bomb_body.h"
#include "enemy_bomb_head.h"
#include "Player/player.h"
#include "Bullet/bullet_direction.h"
#include "Bullet/bullet.h"
#include "Effect/explosion_death.h"
#include "Item/item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bombbody.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(100.0f,150.0f,0.0f))		//�T�C�Y7
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (12)									//�̗�
#define MOVE (D3DXVECTOR3(5.0f,0.0f,0.0f))			//�ړ���		
#define SCORE (10000)								//�X�R�A
#define MINIMUM_RADIAN (0.0f)						//���W�A���̍ŏ��l
#define ADD_RADIAN (0.1f)							//���W�A���̉��Z��
#define SPACE (10.0f)								//��ʒ[�Ƃ̋�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyBombBody::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyBombBody::CEnemyBombBody(int nPriority) : CEnemy(nPriority)
{
	m_pBombHead = NULL;				//���e�̓G�̓��̃|�C���^
	m_fRadian = MINIMUM_RADIAN;		//���W�A��
	m_fAddRadian = ADD_RADIAN;		//���W�A���̉��Z��
	m_bDeath = false;				//���񂾂��ǂ���
}							

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyBombBody::~CEnemyBombBody()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyBombBody::TextureLoad(void)
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
void CEnemyBombBody::TextureUnload(void)
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
CEnemyBombBody * CEnemyBombBody::Create(D3DXVECTOR3 Position, CEnemyBombHead * pHead)
{
	//���e�G�̑̂̃|�C���^
	CEnemyBombBody * pEnemyBombBody = NULL;
	//�������e�G�̑̂̃|�C���^��NULL�̏ꍇ
	if (pEnemyBombBody == NULL)
	{
		//���e�G�̑̂̃������m��
		pEnemyBombBody = new CEnemyBombBody;
		//�������e�G�̑̂̃|�C���^��NULL����Ȃ��ꍇ
		if (pEnemyBombBody != NULL)
		{
			//�ʒu��ݒ肷
			pEnemyBombBody->SetPosition(Position);
			//���e�G�̓��̃|�C���^
			pEnemyBombBody->m_pBombHead = pHead;
			//�����������֐��Ăяo��
			pEnemyBombBody->Init();
		}
	}
	//���e�G�̑̂̃|�C���^��Ԃ�
	return pEnemyBombBody;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyBombBody::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�Փ˃T�C�Y�̏����ݒ�
	SetCollisionSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�ړ��ʂ̏����ݒ�
	SetMove(MOVE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//��Ԃ��ړ���
	SetState(STATE_MOVE);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyBombBody::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyBombBody::Update(void)
{
	//�ړ������֐��Ăяo��
	Move();
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
	{
		//���S�����֐��Ăяo��
		Death();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemyBombBody::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyBombBody::Death(void)
{
	//��������ł��Ȃ�������
	if (m_bDeath == false)
	{
		//�v���C���[���擾����
		CPlayer * pPlayer = CGameMode::GetPlayer();
		//�T�E���h�̎擾
		CSound * pSound = CManager::GetSound();
		//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
		if (pPlayer != NULL)
		{
			//�����G�t�F�N�g�̐���
			CExplosionDeath::Create(GetPosition(), EXPLOSION_SIZE);
			//�����T�E���h��NULL����Ȃ��ꍇ
			if (pSound != NULL)
			{
				//�������̍Đ�
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			}
			//�v���C���[�̃X�R�A�����Z����
			pPlayer->AddScore(SCORE);
			//�S���E��
			m_pBombHead->DeathAll();
			//���S��Ԃɂ���
			m_bDeath = true;
		}
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CEnemyBombBody::Move(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//��]���擾����
	D3DXVECTOR3 Rotation = GetRotation();
	//�ړ��ʂ��擾
	D3DXVECTOR3 Move = GetMove();
	//���W�A�������Z����
	m_fRadian += m_fAddRadian;
	//�����������t��
	if (m_fRadian >= 360.0f)
	{
		//���W�A����0�ɂ���
		m_fRadian = MINIMUM_RADIAN;
	}
	//�ړ��ʂ̐ݒ�
	SetMove(D3DXVECTOR3(Move.x, float(5 * sin(m_fRadian)), Move.z));
	//��ʒ[�ɂ�����t������
	if (GetPosition().x < FIELD_WIDTH_MIN + SPACE)
	{
		//�ړ��ʂ̐ݒ�
		SetMove(D3DXVECTOR3(Move.x * -1.0f, Move.y, Move.z));
		//���W�A���𔽓]������
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	if (GetPosition().x > FIELD_WIDTH - SPACE)
	{
		//�ړ��ʂ̐ݒ�
		SetMove(D3DXVECTOR3(Move.x * -1.0f, Move.y, Move.z));
		//���W�A���𔽓]������
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//�i�s�����Ɍ��������킹��
	SetRotation(D3DXVECTOR3(Rotation.x, Rotation.y, atan2f((Position.x + Move.x) - Position.x, (Position.y + Move.y) - Position.y)));
}
