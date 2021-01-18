//=============================================================================
//
// �G���� [enemy.cpp]
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
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CEnemy::m_apScene[TYPE_MAX] = {};
int CEnemy::m_nCountEnemy = 2;
int CEnemy::m_nBombEnemyLife = 200;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority):CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�G�̈ړ���
	m_nLife = 0;							//�̗�
	m_nCountBullet = 0;						//�e�̃J�E���g
	m_nBulletIndex = 0;
	m_fBulletAngle = 0.0f;
	m_fWidth = 0.0f;						//��
	m_fHeight = 0.0f;						//����
	m_type = TYPE_NONE;						//�G�̎��
	memset(m_Location, 0, sizeof(m_Location));
	m_fTime = 0.0f;
	m_fStop = 0.0f;
	m_nEnemyTimeCount = 0;
	m_nHitCount = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleRot = 0.0f;
	m_fScale = 0.0f;
	m_nStayCount = 0;
	m_bHit = false;
	m_bShot = false;
	m_bStay = true;
	m_nColor = 0;
	m_fRd = 0.0f;
	m_fRdScale = 0.1f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// �e�N�X�`���̃��[�h�֐�
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EYE,								// �t�@�C���̖��O
		&m_apScene[TYPE_EYE]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FLOWER,								// �t�@�C���̖��O
		&m_apScene[TYPE_FLOWER]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SPIDER,								// �t�@�C���̖��O
		&m_apScene[TYPE_SPIDER]);					// �ǂݍ��ރ������[

													// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOMBHEAD,								// �t�@�C���̖��O
		&m_apScene[TYPE_BOMBHEAD]);					// �ǂݍ��ރ������[

													// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOMBBODY,								// �t�@�C���̖��O
		&m_apScene[TYPE_BOMBBODY]);					// �ǂݍ��ރ������[

													// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EYE2,								// �t�@�C���̖��O
		&m_apScene[TYPE_EYE2]);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h�֐�
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Release();
			m_apScene[nCount] = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type,int nLife)
{
	CEnemy * pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(pos, SizeWidth, SizeHeight, type,nLife);
	return pEnemy;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type,int nLife)
{
	CScene2d::Init(pos,SizeWidth,SizeHeight);

	if (type == TYPE_BOMBBODY || type == TYPE_BOMBHEAD)
	{
		//�I�u�W�F�^�C�v��G�ɂ���
		SetObjType(CScene::OBJTYPE_BOMBENEMY);
	}
	else
	{
		//�I�u�W�F�^�C�v��G�ɂ���
		SetObjType(CScene::OBJTYPE_ENEMY);
	}


	m_pos = pos;	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�G�̈ړ���
	if (type == TYPE_BOMBBODY || type == TYPE_BOMBHEAD)
	{
		m_move.x = 5.0f;
	}
	m_type = type;							//�G�̎��
	m_nLife = nLife;						//�̗�
	m_nCountBullet = 0;						//�e�̃J�E���^
	m_nBulletIndex = 0;
	m_fBulletAngle = 0.0f;
	m_fWidth = SizeWidth;					//��
	m_fHeight = SizeHeight;					//����
	m_fTime = 0.0f;
	m_nEnemyTimeCount = 0;
	m_nHitCount = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	// �Ίp���A�p�x�̐ݒ�
	m_fLength = sqrtf((float)(((m_fWidth / 2) * (m_fWidth / 2)) + ((m_fHeight / 2) * (m_fHeight / 2))));
	m_fAngle = atan2f((m_fHeight / 2), (m_fWidth / 2));
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleRot = 0.0f;
	if (m_type == TYPE_BOMBHEAD||m_type == TYPE_BOMBBODY)
	{
		m_fAngleRot = D3DXToRadian(90.0f) ;
	}
	m_fScale = 1.0f;
	m_bHit = false;
	m_bShot = false;
	m_bStay = true;
	m_nStayCount = 0;
	m_nColor = 0;
	//�����_���V�[�h�l
	int nRandSeed = rand() % 100;
	srand((unsigned int)nRandSeed);
	//m_fStop = float(100 + (rand() * ((FIELD_HEIGHT / 2) - 100 + 1.0) / (1.0 + RAND_MAX)));//�ڕW�����̌���
	m_fStop = float(rand() % (FIELD_HEIGHT / 2) + 100);

	switch (m_type)
	{
	case TYPE_FLOWER:
		m_fStop = float(rand() % (FIELD_HEIGHT / 6) + 100);
		break;
	case TYPE_SPIDER:
		m_fStop = float(rand() % (FIELD_HEIGHT / 6) + 100);
		break;
	}
	//���_���W�̐ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;
	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	if (m_type == TYPE_FLOWER)
	{
		//�e�N�X�`���Z�b�g
		SetTex(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);
	}
	else if (m_type == TYPE_SPIDER)
	{
		//�e�N�X�`���Z�b�g
		SetTex(
			m_nPatternAnim * 0.5f,
			0.0f,
			m_nPatternAnim * 0.5f + 0.5f,
			1.0f);
	}
	else
	{
		//�e�N�X�`���̃Z�b�g
		SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	}
	//�e�N�X�`���̊��蓖��
	BindTexture(m_apScene[m_type]);
	//�F�̃Z�b�g
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CEnemy::Update(void)
{
	CScene2d::Update();
	//�ʒu���擾
	m_pos = GetPosition();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	//�����e����ʊO�ɍs������
	if (m_pos.y < 0 ||
		m_pos.y > FIELD_HEIGHT ||
		m_pos.x < FIELD_WIDTH_MIN ||
		m_pos.x > FIELD_WIDTH)
	{
		//�G�̍폜
		Uninit();
		return;
	}

	switch (m_type)
	{
	case TYPE_EYE:
		//�v���C���[�����߂鏈��
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(4, nCountScene);
			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//�����I�u�W�F�^�C�v���v���C���[�̏ꍇ
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_bShot == false)
					{
						D3DXVECTOR3 playerpos = pScene->GetPosition();
						D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//�v���C���[�܂ł̋������v�Z
						m_fAngleRot = atan2f(m_TargetDistance.y, m_TargetDistance.x);//�v���C���̕��Ɍ������p�x���v�Z
						m_fAngleRot = m_fAngleRot * -1.0f;
					}
				}

			}
		}
		if (m_bStay == true)
		{
			//�G���w��̈ʒu�܂ňړ�������
			if (m_pos.y <= m_fStop)
			{
				//Y���Ɉړ��ʂ���
				m_move.y = 5.0f;
			}
			//�����G���w��̏ꏊ�Ŏ~�܂�����
			else
			{
				if (m_nBulletIndex < 4)
				{
					//�ŏ��v���C���[���ʒu���擾���Ĕ��˕��������߂�
					if (m_nBulletIndex <= 0)
					{
						int nCountPriority = 4;
						for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
						{
							CScene * pScene = GetScene(nCountPriority, nCountScene);
							if (pScene != NULL)
							{
								//�I�u�W�F�^�C�v�̎擾
								OBJTYPE objType;
								objType = pScene->GetObjType();
								//�����I�u�W�F�^�C�v���v���C���[�̏ꍇ
								if (objType == OBJTYPE_PLAYER)
								{
									D3DXVECTOR3 playerpos = pScene->GetPosition();
									D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//�v���C���[�܂ł̋������v�Z
									m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);//�v���C���̕��Ɍ������p�x���v�Z
									/*	m_fAngleRot = m_fBulletAngle * -1.0f;*/
								}
							}
						}
					}
					//�v���C���[������łȂ��Ƃ�
					if (CPlayer::GetbDeath() == false)
					{
						//�����e�̔���
						if (m_nCountBullet % 10 == 0)
						{
							m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(cosf(m_fBulletAngle)*BULLET_SPEAD, sinf(m_fBulletAngle)*BULLET_SPEAD, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_NORMAL, CBullet::COLOR_GREEN, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
							m_bShot = true;
							m_nBulletIndex++;
						}
					}
				}
				else
				{
					//�e�N�[���^�C��
					if (m_nCountBullet % 150 == 0)
					{
						m_nBulletIndex = 0;
					}
					m_bShot = false;
				}
				//Y���̈ړ��ʂ�0�ɂ���
				if (m_move.y >= 0.0f)
				{
					//����
					m_move.y += (0.0f - m_move.y)*RATE_MOVE;
				}
			}
			m_nStayCount++;
		}
		else
		{
				m_move.y = -7.0f;
				m_nStayCount = 0;
		}
		if (m_nStayCount == 500)
		{
			m_bStay = false;
		}

		//�e�̃J�E���g�����Z
		m_nCountBullet++;
		//�G�̑؍ݎ���
		m_nEnemyTimeCount++;
		break;
		case TYPE_EYE2:
			//�v���C���[�����߂鏈��
			for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
			{
				CScene * pScene = GetScene(4, nCountScene);
				if (pScene != NULL)
				{
					//�I�u�W�F�^�C�v�̎擾
					OBJTYPE objType;
					objType = pScene->GetObjType();
					//�����I�u�W�F�^�C�v���v���C���[�̏ꍇ
					if (objType == OBJTYPE_PLAYER)
					{
						if (m_bShot == false)
						{
							D3DXVECTOR3 playerpos = pScene->GetPosition();
							D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//�v���C���[�܂ł̋������v�Z
							m_fAngleRot = atan2f(m_TargetDistance.y, m_TargetDistance.x);//�v���C���̕��Ɍ������p�x���v�Z
							m_fAngleRot = m_fAngleRot * -1.0f;
						}
					}

				}
			}
			if (m_bStay == true)
			{
				//�G���w��̈ʒu�܂ňړ�������
				if (m_pos.y <= m_fStop)
				{
					//Y���Ɉړ��ʂ���
					m_move.y = 5.0f;
				}
				//�����G���w��̏ꏊ�Ŏ~�܂�����
				else
				{
						//�ŏ��v���C���[���ʒu���擾���Ĕ��˕��������߂�
						if (m_nBulletIndex <= 0)
						{
							int nCountPriority = 4;
							for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
							{
								CScene * pScene = GetScene(nCountPriority, nCountScene);
								if (pScene != NULL)
								{
									//�I�u�W�F�^�C�v�̎擾
									OBJTYPE objType;
									objType = pScene->GetObjType();
									//�����I�u�W�F�^�C�v���v���C���[�̏ꍇ
									if (objType == OBJTYPE_PLAYER)
									{
										D3DXVECTOR3 playerpos = pScene->GetPosition();
										D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(playerpos.x - m_pos.x, playerpos.y - m_pos.y, 0.0f);//�v���C���[�܂ł̋������v�Z
										m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);//�v���C���̕��Ɍ������p�x���v�Z
																										/*	m_fAngleRot = m_fBulletAngle * -1.0f;*/
									}
								}
							}
						}
						//�v���C���[������łȂ��Ƃ�
						if (CPlayer::GetbDeath() == false)
						{
							//�����e�̔���
							if (m_nCountBullet % 100 == 0)
							{
								m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(cosf(m_fBulletAngle)*BULLET_SPEAD, sinf(m_fBulletAngle)*BULLET_SPEAD, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_GUID, CBullet::COLOR_GREEN, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
								m_bShot = true;
								m_nBulletIndex++;
							}
						}
					else
					{
						//�e�N�[���^�C��
						if (m_nCountBullet % 150 == 0)
						{
							m_nBulletIndex = 0;
						}
						m_bShot = false;
					}
					//Y���̈ړ��ʂ�0�ɂ���
					if (m_move.y >= 0.0f)
					{
						//����
						m_move.y += (0.0f - m_move.y)*RATE_MOVE;
					}
				}
				m_nStayCount++;
			}
			else
			{
				m_move.y = -7.0f;
				m_nStayCount = 0;
			}
			if (m_nStayCount == 500)
			{
				m_bStay = false;
			}

			//�e�̃J�E���g�����Z
			m_nCountBullet++;
			//�G�̑؍ݎ���
			m_nEnemyTimeCount++;
			break;
	case TYPE_FLOWER:
		if (m_bStay == true)
		{
			//������~�ꏊ�ȉ��̎�
			if (m_pos.y <= m_fStop)
			{
				//Y���Ɉړ��ʂ���
				m_move.y = 5.0f;
			}
			//�����G���w��̏ꏊ�Ŏ~�܂�����
			else
			{
				//����
				m_move.y += (0.0f - m_move.y)*RATE_MOVE;

				//���e�𔭎˂���܂ł̎���
				if (m_nCountBullet >= 50)
				{
					//�v���C���[������łȂ��Ƃ�
					if (CPlayer::GetbDeath() == false)
					{
						if (m_nCountBullet % 20 == 0)
						{
							//�V���b�g���̍Đ�
							//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);

							if (m_nColor < 7)
							{
								for (int nCnt = 0; nCnt < 20; nCnt++)
								{
									CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, 0.0f), BULLET_SIZE * 4, BULLET_SIZE * 4, CBullet::USER_ENEMY, CBullet::TYPE_FLOWER, (CBullet::COLOR)m_nColor, CBullet::FLOWER_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
									//�e�̐���
									//CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCnt * (360 / 20)))*3.5f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_FLOWER, m_nColor, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
								}
							}

							//�F�̃J�E���g�����Z
							m_nColor++;
						}

						if (m_nColor > 7)
						{
							if (m_nCountBullet % 100 == 0)
							{
								m_nColor = 0;
							}
						}
					}
				}
				//�e�̃J�E���g�����Z
				m_nCountBullet++;
			}
			m_nStayCount++;
		}
		else
		{
			m_move.y = -7.0f;
			m_nStayCount = 0;
		}
		if (m_nStayCount == 400)
		{
			m_bStay = false;
		}

		break;
	case TYPE_SPIDER:
		//������~�ꏊ�ȉ��̎�
		if (m_pos.y <= m_fStop)
		{
			//Y���Ɉړ��ʂ���
			m_move.y = 5.0f;
		}
		//�����G���w��̏ꏊ�Ŏ~�܂�����
		else
		{
			//����
			m_move.y += (0.0f - m_move.y)*RATE_MOVE;

			//���e�𔭎˂���܂ł̎���
			if (m_nCountBullet >= 50)
			{
				//�v���C���[������łȂ��Ƃ�
				if (CPlayer::GetbDeath() == false)
				{
					if (m_nCountBullet % 20 == 0)
					{
						for (int nCnt = 0; nCnt < 9; nCnt++)
						{
							CBullet::Create(m_pos, D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_NORMAL, CBullet::COLOR_WHITE, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
						}
					}

					//�U���e�̔���
		/*			if (m_nCountBullet % 250 == 0)
					{
						m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + 10, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_ENEMY, CBullet::TYPE_GUID, CBullet::COLOR_RED, CBullet::BULLET_TEXTURE, EASY_ENEMY_BULLET_ATTACK);
					}*/
				}
			}
			//�e�̃J�E���g�����Z
			m_nCountBullet++;
		}
		break;
	case TYPE_BOMBHEAD:

		m_fRd += m_fRdScale;
		if (m_fRd >= 360)
		{
			m_fRd = 0;
		}

		m_move.y = float((5 * sin(m_fRd)));

		if (m_pos.x < FIELD_WIDTH_MIN + 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		if (m_pos.x > FIELD_WIDTH - 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		//�i�s�����Ɍ��������킹��
		m_fAngleRot = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
		break;
	case TYPE_BOMBBODY:

		m_fRd += m_fRdScale;
		if (m_fRd >= 360.0f)
		{
			m_fRd = 0;
		}

		m_move.y = float((5 * sin(m_fRd)));

		if (m_pos.x < FIELD_WIDTH_MIN + 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		if (m_pos.x > FIELD_WIDTH - 10.0f)
		{
			m_move.x = m_move.x * -1.0f;
			m_fRdScale = m_fRdScale * -1.0f;
		}
		//�i�s�����Ɍ��������킹��
		m_fAngleRot = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
		break;
	default:
		break;
	}

	switch (m_type)
	{
	case TYPE_FLOWER:
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

		break;
	case TYPE_SPIDER:
		if (m_nCounterAnim >= 7)
		{
			m_nCounterAnim = 0;

			m_nPatternAnim++;

			if (m_nPatternAnim > 6)
			{
				m_nPatternAnim = 0;
			}
		}
		break;
	}

	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnim++;

	//�ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//�����E������ʂ̊O�ɍs������
	if (m_pos.y >= FIELD_HEIGHT)
	{
		Uninit();
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

	//���_���W�̐ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_fAngleRot) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//���݈ʒu�̃Z�b�g
	SetPosition(m_pos);

	if (m_type == TYPE_FLOWER)
	{
		//�e�N�X�`���Z�b�g
		SetTex(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);
	}
	else if (m_type == TYPE_SPIDER)
	{
		//�e�N�X�`���Z�b�g
		SetTex(
			m_nPatternAnim * 0.5f,
			0.0f,
			m_nPatternAnim * 0.5f + 0.5f,
			1.0f);
	}
	else
	{
		//�e�N�X�`���̃Z�b�g
		SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	}

	//�F�̃Z�b�g
	SetColor(m_col);
	m_fTime++;
}

//=============================================================================
// �`��֐�
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT�֐�
//=============================================================================
void CEnemy::Hit(void)
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
// �̗͌��Z�֐�
//=============================================================================
void CEnemy::SubLife(int nValue)
{
	//�X�R�A�擾
	CScore * pScore = CGame::GetScore();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	if (m_type == TYPE_BOMBBODY || m_type == TYPE_BOMBHEAD)
	{
		m_nBombEnemyLife -= nValue;

		if (m_nBombEnemyLife < 0)
		{
			int nCountPriority = 4;
			for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
			{
				CScene * pScene = GetScene(nCountPriority, nCountScene);
				if (pScene != NULL)
				{
					//�I�u�W�F�^�C�v�̎擾
					OBJTYPE objType;
					objType = pScene->GetObjType();
					//�����I�u�W�F�^�C�v���{���I�̏ꍇ
					if (objType == OBJTYPE_BOMBENEMY)
					{
						D3DXVECTOR3 pos = pScene->GetPosition();
						//�����̔���
						CExplosion::Create(pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);

						//�G�̎�ނɂ���ăX�R�A�̉��Z�ʂ�ς���
						switch (m_type)
						{
						case TYPE_BOMBBODY:
							//�X�R�A�̉��Z�֐��Ăяo��
							pScore->AddScore(1000);
							//�����̔���
							CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
							//CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_SCORE);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
							break;
						case TYPE_BOMBHEAD:
							//�X�R�A�̉��Z�֐��Ăяo��
							pScore->AddScore(10000);
							//�����̔���
							CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
							CItem::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
							break;

						}

						pScene->Uninit();
					}

				}
			}
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			m_nBombEnemyLife = 200;
	/*		Uninit();
			return;*/
		}
	}
	else
	{
		//�̗͂̌��Z����
		m_nLife -= nValue;




		//�G�̃��C�t��ENEMY_MIN_HP�ȉ��ɂȂ����Ƃ�
		if (m_nLife <= ENEMY_MIN_HP)
		{
			//�G�̎�ނɂ���ăX�R�A�̉��Z�ʂ�ς���
			switch (m_type)
			{
			case TYPE_EYE:
				//�X�R�A�̉��Z�֐��Ăяo��
				pScore->AddScore(10000);
				//�����̔���
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				//CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_SCORE);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_FLOWER:
				//�X�R�A�̉��Z�֐��Ăяo��
				pScore->AddScore(50000);
				//�񕜃A�C�e���̃h���b�v
				CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_OWN);
				//�����̔���
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_SPIDER:
				//�X�R�A�̉��Z�֐��Ăяo��
				pScore->AddScore(100000);
				//LVUP�A�C�e���̃h���b�v
				CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);
				//�����̔���
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
			case TYPE_EYE2:
				//�X�R�A�̉��Z�֐��Ăяo��
				pScore->AddScore(100000);
				//LVUP�A�C�e���̃h���b�v
				//CItem::Create(m_pos, ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);
				//�����̔���
				CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				break;
				//case TYPE_HARD:
				//	//�X�R�A�̉��Z�֐��Ăяo��
				//	pScore->AddScore(100000);
				//	//�����̔���
				//	CExplosion::Create(m_pos, ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
				//	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
				//	break;
			}
			m_nCountEnemy--;

			if (m_nCountEnemy == 0)
			{
				m_nCountEnemy = 2;
				//���U���g�Ɉړ�
				//CManager::StartFade(CManager::MODE_RESULT);
			}
			Uninit();
			return;
		}
	}
}
