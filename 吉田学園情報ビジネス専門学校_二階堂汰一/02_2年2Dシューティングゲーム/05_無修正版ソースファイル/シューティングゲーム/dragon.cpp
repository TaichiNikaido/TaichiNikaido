//=============================================================================
//
// �h���S������ [dragon.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "dragon.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"
#include "wormhole.h"
#include "warning.h"
#include "title.h"
#include "warning.h"

LPDIRECT3DTEXTURE9 CDragon::m_pScene = NULL;
bool CDragon::m_bSpawn = false;
bool CDragon::m_bDeath = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDragon::CDragon(int nPriority) :CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ���
	m_nLife = 0;							//�̗�
	m_nCountBullet = 0;						//�e�̃J�E���g
	m_nCountAI = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fWidth = 0.0f;						//��
	m_fHeight = 0.0f;						//����
	m_fTime = 0.0f;
	m_nHitCount = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_fAngle = 0.0f;						//�p�x
	m_fLength = 0.0f;						//����
	m_fScale = 0.0f;		//�傫��
	m_fAddScale = 0.0f;	//�傫���̉��Z��
	m_bHit = false;
	m_bSpawn = false;
	m_bDeath = false;
	m_TargetDistance = D3DXVECTOR3(0.0f,0.0f,0.0f);//�ڕW�܂ł̋���
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ڕW�n�_
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// �e�N�X�`���̃��[�h�֐�
//=============================================================================
HRESULT CDragon::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DRAGON,								// �t�@�C���̖��O
		&m_pScene);									// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h�֐�
//=============================================================================
void CDragon::Unload(void)
{
		//�e�N�X�`���̔j��
		if (m_pScene != NULL)
		{
			m_pScene->Release();
			m_pScene = NULL;
		}
}

//=============================================================================
// �����֐�
//=============================================================================
CDragon * CDragon::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nLife)
{
	CDragon * pDragon;
	pDragon = new CDragon;
	pDragon->Init(pos, SizeWidth, SizeHeight, nLife);
	return pDragon;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CDragon::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nLife)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�I�u�W�F�^�C�v���h���S���ɂ���
	SetObjType(CScene::OBJTYPE_DRAGON);

	m_pos = pos;	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�h���S���̈ړ���
	m_nLife = nLife;						//�̗�
	m_nCountBullet = 0;						//�e�̃J�E���^
	m_nCountAI = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fWidth = SizeWidth;					//��
	m_fHeight = SizeHeight;					//����
	m_fTime = 0.0f;
	m_nHitCount = 0;
	m_bHit = false;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����
	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//����
	m_fAngle = atan2f((SizeWidth / 2), (SizeWidth / 2));
	m_fScale = 0.1f;
	m_fAddScale = 0.01f;	//�傫���̉��Z��
	m_TargetDistance = D3DXVECTOR3(500, 0.0f, 0.0f);//�ڕW�܂ł̋���
	m_TargetPos = D3DXVECTOR3(500, 0.0f, 0.0f);//�ڕW�n�_
	m_bSpawn = false;
	m_bDeath = false;
	pSound->PlaySound(CSound::SOUND_LABEL_DRAGON);
	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pScene);
	//�F�̃Z�b�g
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CDragon::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CDragon::Update(void)
{
	CScene2d::Update();
	//�ʒu���擾
	m_pos = GetPosition();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�Q�Ƃ���v���C�I���e�B�̎w��
	int nCountPriority = 4;

	if (m_fScale <= 1.0f)
	{
		m_fScale += m_fAddScale;
	}
	else
	{
		m_bSpawn = true;
	}


	if (m_bSpawn == true)
	{
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(nCountPriority, nCountScene);

			if (pScene != NULL)
			{
				//�v���C���[�̈ʒu���擾
				D3DXVECTOR3 player_pos;
				player_pos = pScene->GetPosition();
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE objType;
				objType = pScene->GetObjType();
			}
		}

		if (CBullet::GetbCharage() == true)
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//�ڕW�����ɋ߂Â�����ڕW���Đݒ肷��
			if (m_pos.x >= m_TargetPos.x - 50 / 2 &&
				m_pos.x < m_TargetPos.x + 50 / 2 &&
				m_pos.y >= m_TargetPos.y - 50 / 2 &&
				m_pos.y < m_TargetPos.y + 50 / 2)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
			}
			////�ڕW�����ɋ߂Â�����ڕW���Đݒ肷��
			//else if (m_pos.x > FIELD_WIDTH - 600 ||
			//	m_pos.x < FIELD_WIDTH_MIN + 600 ||
			//	m_pos.y > FIELD_HEIGHT ||
			//	m_pos.y < 0)
			//{
			//	//�����_���V�[�h�l
			//	int nRandSeed = rand() % (FIELD_WIDTH - 600) + (FIELD_WIDTH_MIN + 600);
			//	srand((unsigned int)nRandSeed);
			//	m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 600) + (FIELD_WIDTH_MIN + 600));//�ڕW�����̌���
			//	m_TargetPos.y = (float)(rand() % 300 + 200);
			//}
			else
			{
				m_TargetDistance = D3DXVECTOR3(m_TargetPos.x - m_pos.x, m_TargetPos.y - m_pos.y, 0.0f);//�ڕW�܂ł̋������Z�o
				m_rot.y = atan2f(m_TargetDistance.y, m_TargetDistance.x);
				m_move = D3DXVECTOR3(cosf(m_rot.y)*2.5f, sinf(m_rot.y)*2.5f, 0.0f);
			}
			if (m_pos.x > FIELD_WIDTH - 200)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += -600.0f;
			}
			if (m_pos.x < FIELD_WIDTH_MIN + 200)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += 200.0f;
			}
		}
	
		//�����E������ʂ̊O�ɍs������
		if (m_pos.y >= FIELD_HEIGHT)
		{
			Uninit();
		}
		//�v���C���[������łȂ��Ƃ�
		if (CPlayer::GetbDeath() == false)
		{
				if (m_nCountBullet % 400 == 0)
				{
					//�΋��̔���
					m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (DRAGON_SIZE_HEIGHT / 2), 0.0f), m_move, 35.0f, 35.0f, CBullet::USER_DRAGON, CBullet::TYPE_FIREBALL, CBullet::COLOR_ORANGE, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
				}

					//m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (DRAGON_SIZE_HEIGHT / 2), 0.0f), m_move, 35.0f, 35.0f, CBullet::USER_DRAGON, CBullet::TYPE_FIRE, CBullet::COLOR_PINK, CBullet::FIRE_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
			}
		//�o���b�g�̃J�E���g��i�߂�
		m_nCountBullet++;
	}

	//�e�N�X�`���A�j���[�V����
	if (m_nCounterAnim >= 7)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim++;

		if (m_nPatternAnim > 6)
		{
			m_nPatternAnim = 0;
		}
	}

	//�F�̐ݒ�
	if (m_bHit == true)
	{
		m_nHitCount++;
		if (m_nHitCount == 5)
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			m_bHit = false;
			m_nHitCount = 0;
		}
	}

	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnim++;

	//�ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//���_���W�̐ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//���݈ʒu�̃Z�b�g
	SetPosition(m_pos);
	//�e�N�X�`���Z�b�g
	SetTex(
		m_nPatternAnim * 0.1666f,
		0.0f,
		m_nPatternAnim * 0.1666f + 0.1666f,
		1.0f);
	//�F�̃Z�b�g
	SetColor(m_col);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CDragon::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT�֐�
//=============================================================================
void CDragon::Hit(void)
{
	//�X�R�A���擾
	CScore * pScore = CGame::GetScore();
	//�X�R�A���Z
	pScore->AddScore(100);
	//�̗͂̌��Z
	SubLife(10);
	//HIT��Ԃ�true�ɂ���
	m_bHit = true;
	//�F�̃Z�b�g
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//�F�̃Z�b�g
	SetColor(m_col);
}

//=============================================================================
// �̗͂̌��Z�֐�
//=============================================================================
void CDragon::SubLife(int nValue)
{
	//�X�R�A�擾
	CScore * pScore = CGame::GetScore();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�̗͂̌��Z����
	m_nLife -= nValue;

	//�h���S���̃��C�t��MIN_HP�ȉ��ɂȂ����Ƃ�
	if (m_nLife <= DRAGON_MIN_HP)
	{
		//�X�R�A�̉��Z�֐��Ăяo��
		pScore->AddScore(100000);
		//�����̔���
		CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
		//�������̔���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		m_bDeath = true;
		m_bSpawn = false;
		pSound->StopSound();
		//���O���͂Ɉړ�
		CManager::StartFade(CManager::MODE_RESULT);
		if (CTitle::GetbReplay() == true)
		{
			CManager::StartFade(CManager::MODE_TITLE);
			m_bSpawn = false;
			m_bDeath = false;
			CWormhole::SetSpawn(false);
		}
		//�h���S���̍폜
		Uninit();
		return;
	}
}

void CDragon::SetSpawn(bool bDeath)
{
	m_bSpawn = bDeath;
}

void CDragon::SetDeath(bool bDeath)
{
	m_bDeath = bDeath;
}