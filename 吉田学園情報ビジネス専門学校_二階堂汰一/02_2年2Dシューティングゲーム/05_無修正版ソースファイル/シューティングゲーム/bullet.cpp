//=============================================================================
//
//	�e [bullet.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "score.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "warning.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[TEXTURE_MAX] = {};
D3DCOLOR CBullet::m_aColor[COLOR_MAX] = //�F�p�����[�^
{
	D3DCOLOR_RGBA(255,0,0,255),    //��
	D3DCOLOR_RGBA(255,128,0,255),// �I�����W
	D3DCOLOR_RGBA(255,255,0,255),// ���F
	D3DCOLOR_RGBA(0,255,0,255),//��
	D3DCOLOR_RGBA(0,0,255,255),//��
	D3DCOLOR_RGBA(128,0,255,255),//��
	D3DCOLOR_RGBA(255,0,255,255),//�s���N
	D3DCOLOR_RGBA(255,255,255,255)//��
};
bool CBullet::m_bFireBall = true;
bool CBullet::m_bCharage = true;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���	
	m_user = USER_NONE;						//�g�p��
	m_type = TYPE_NORMAL;	                //�^�C�v
	m_texture = BULLET_TEXTURE;				//�e�N�X�`��
	m_nAttack = 0;							//�U����
	m_fWidth = 0.0f;						//��
	m_fHeight = 0.0f;						//����
	m_pEffect = NULL;						//�G�t�F�N�g�̃|�C���^
	m_nCountBullet = 0;						//�J�E���g
	m_nBreatheCount = 0;					//�u���X�J�E���g
	m_nLife = 0;							//�̗�
	m_pCol = COLOR_ORANGE;					//�F�ւ̃|�C���^
	m_nCount = 0;							//�J�E���g
	m_fDistance = 0.0f;						//����
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_fSpeed = 0.0f;						//����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_fAngle = 0.0f;						//�p�x
	m_fLength = 0.0f;						//����
	m_fScale = 0.0f;						//�傫��
	m_fAddScale = 0.0f;						//�傫���̉��Z��
	m_bShotFireball = true;					//�΋������������ǂ���
	m_bFireBall = true;						//�΋��̎g�p���
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CBullet::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BULLET,								// �t�@�C���̖��O
		&m_apTexture[BULLET_TEXTURE]);				// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BEAM,								// �t�@�C���̖��O
		&m_apTexture[BEAM_TEXTURE]);					// �ǂݍ��ރ������[
														// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BIRA,								// �t�@�C���̖��O
		&m_apTexture[FLOWER_TEXTURE]);					// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FIRE,								// �t�@�C���̖��O
		&m_apTexture[FIRE_TEXTURE]);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,USER user,TYPE type, COLOR col, TEXTURE texture, int nAttack)
{
	CBullet * pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos,move, SizeWidth, SizeHeight,user,type,col,texture,nAttack);
	pBullet->SetPosition(pos);

	return pBullet;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,USER user, TYPE type, COLOR col, TEXTURE texture, int nAttack)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	m_pos = pos;	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = move;			//�ړ���
	m_user = user;			//�g�p��
	m_type = type;			//�^�C�v
	m_texture = texture;	//�e�N�X�`��
	m_nAttack = nAttack;	//�U����
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight;	//����
	m_pCol = col;			//�J���[
	m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(0, 0, 0, 0), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_NONE);
	m_nCountBullet = 0;		//�J�E���g
	m_nBreatheCount = 0;	//�u���X�J�E���g
	m_nLife = 175;			//�̗�
	//�����U���e��������
	if (m_type == TYPE_GUID)
	{
		m_nLife = 110;
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//����
	m_fAngle = atan2f((SizeHeight / 2), (SizeWidth / 2));
	m_fScale = 1.0f;		//�傫��
	m_fAddScale = 0.01f;	//�傫���̉��Z��
	m_bShotFireball = true;	//�΋������������ǂ���
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ڕW�̈ʒu
	//�I�u�W�F�^�C�v��e�ɂ���B
	SetObjType(CScene::OBJTYPE_BULLET);
	//�����^�C�v���΋���������
	if (m_type == TYPE_FIREBALL)
	{
		m_fScale = 0.1f;
		m_nLife = 75;
		SetObjType(CScene::OBJTYPE_FIREBALL);
		m_bCharage = true;
	}
	//�����^�C�v���΂�����r
	if (m_type == TYPE_FIRE)
	{
		SetObjType(CScene::OBJTYPE_FIRE);
	}
	//�ڕW�܂ł̋���
	m_fDistance = 0.0f;
	m_fSpeed = 5.0f;	//����
	//���_���W�̐ݒ�
	m_vpos[0].x = pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[1].x = pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[2].x = pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[3].x = pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;
	CPlayer * pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	//�v���C���[�ւ̊p�x
	m_rot.z = atan2f(PlayerPos.y - pos.y , PlayerPos.x - pos.x);
	//���_���W���Z�b�g
	SetVertexPosition(m_vpos);
	//�����e�N�X�`�����Ԃ�����r����
	if (m_texture == FLOWER_TEXTURE)
	{
		//�e�N�X�`���̐ݒ�
		SetTex(
			m_pCol * 0.1428f,
			0.0f,
			m_pCol * 0.1428f + 0.1428f,
			1.0f
		);
	}
      	else
	{
		//�e�N�X�`���̃Z�b�g
		SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
	//���_�J���[�̐ݒ�
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//�F�̃Z�b�g
	SetColor(m_col); 
	//�e�N�X�`���̊��蓖��
	BindTexture(m_apTexture[m_texture]);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBullet::Update(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	CScene2d::Update();
	//�ʒu���擾
	m_pos = GetPosition();
	//�ړ��\�͈͐��䏈���֐��Ăяo��
	MovableRange();
	//�Փ˔��菈���֐��Ăяo��
	Collision();
	if (m_type == TYPE_FIREBALL)
	{
		if (m_nCountBullet == 0)
		{
			CWarning::Create(D3DXVECTOR3(m_pos.x, m_TargetPos.y, 0.0f), D3DXVECTOR3(m_move.x, m_move.y, 0.0f), 1120 - 200, FIELD_HEIGHT / 4);
		}
	}
	//�ʒu�X�V�����֐��Ăяo��
	UpdatePosition();
	//�̗͌��Z�����֐��Ăяo��
	SubLife();
	//�G�t�F�N�g���������֐��Ăяo��
	EffectCreate();

	//�e�̃^�C�v���΋���������
	if (m_type == TYPE_FIREBALL)
	{
		//�����h���S���������Ă���
		if (CDragon::GetDeath() == false)
		{
			//�ڕW�̃X�P�[���ȉ��̎�
			if (m_fScale < 2.0f)
			{
				if (m_nCountBullet % 10 == 0)
				{
					//�g�債�Ă�
					m_fScale += 0.1f;
				}
			}
			else
			{
				//�΋��̔��ˏ�Ԃ��U�ɂ���
				m_bShotFireball = true;
			}
		}
		else
		{
			m_bFireBall = false;
			m_bCharage = false;
			Uninit();
			return;
		}
		m_nCountBullet++;
	}

	if (m_type == TYPE_FLOWER)
	{
		if (m_nCount == 100)
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
					if (objType == OBJTYPE_PLAYER)
					{
						//�v���C���[�̈ʒu���擾
						D3DXVECTOR3 player_pos;
						player_pos = pScene->GetPosition();
						////�ڕW�܂ł̋������Z�o//����͐������̃v���C���[�Ɍ����Ă̕����w��̂�
						D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(player_pos.x - m_pos.x, player_pos.y - m_pos.y, 0.0f);
						m_rot.y = atan2f(m_TargetDistance.y, m_TargetDistance.x);
						m_move = D3DXVECTOR3(cosf(m_rot.y)*5.5f, sinf(m_rot.y)*5.5f, 0.0f);
					}

				}
			}
		}
		m_nCount++;
	}
	//�i�s�����Ɍ��������킹��
	m_rot.z = atan2f((m_pos.x + m_move.x) - m_pos.x, (m_pos.y + m_move.y) - m_pos.y);
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
	if (m_texture == FLOWER_TEXTURE)
	{
		SetTex(
			m_pCol * 0.1428f,
			0.0f,
			m_pCol * 0.1428f + 0.1428f,
			1.0f
		);
	}
	else
	{
		//�e�N�X�`���̃Z�b�g
		SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//���_�J���[
	}
	//�F�̃Z�b�g
	SetColor(m_col);
	//���݈ʒu���Z�b�g
	SetPosition(m_pos);
}


//=============================================================================
// �`��֐�
//=============================================================================
void CBullet::Draw(void)
{
	if(m_type == TYPE_FIRE)
	{
		CRenderer * pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		CScene2d::Draw();
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{
		CScene2d::Draw();
	}
	
}

//=============================================================================
// �Փ˔��菈���֐�
//=============================================================================
void CBullet::Collision(void)
{
	//�Q�Ƃ���v���C�I���e�B��ݒ�
	int nCountPriority = 4;

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(nCountPriority, nCountScene);

		if (pScene != NULL)
		{
			//�I�u�W�F�^�C�v�̎擾
			OBJTYPE objType;
			objType = pScene->GetObjType();
			//�G�̈ʒu���擾
			D3DXVECTOR3 enemy_pos;
			enemy_pos = pScene->GetPosition();
			//�v���C���[�̈ʒu���擾
			D3DXVECTOR3 player_pos;
			player_pos = pScene->GetPosition();
			//�h���S���̈ʒu���擾
			D3DXVECTOR3 dragon_pos;
			dragon_pos = pScene->GetPosition();

			//�e�̎�ނɂ���ď����𕪂���
			switch (m_user)
			{
				//�����g�p�҂��v���C���[�̏ꍇ
			case USER_PLAYER:
				//�����I�u�W�F�^�C�v���G��������
				if (objType == OBJTYPE_ENEMY || objType == OBJTYPE_BOMBENEMY)
				{
					if (m_pos.x + BULLET_SIZE / 2 > enemy_pos.x - (EYE_SIZE / 2) &&
						m_pos.x - BULLET_SIZE / 2 < enemy_pos.x + (EYE_SIZE / 2) &&
						m_pos.y + BULLET_SIZE / 2 > enemy_pos.y - (EYE_SIZE / 2) &&
						m_pos.y - BULLET_SIZE / 2 < enemy_pos.y + (EYE_SIZE / 2))
					{
						//�G�l�~�[��HIT�֐��Ăяo��
						CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
						if (pScene != NULL)
						{
							pEnemy->Hit();
						}
						//�e�̍폜
						Uninit();
						return;
					}
				}
				//�����I�u�W�F�^�C�v���h���S����������
				if (objType == OBJTYPE_DRAGON)
				{
					if (CDragon::GetSpawn() == true)
					{
						if (m_pos.x + BULLET_SIZE / 2 > dragon_pos.x - 200 &&
							m_pos.x - BULLET_SIZE / 2 < dragon_pos.x + 200 &&
							m_pos.y + BULLET_SIZE / 2 > dragon_pos.y + 100 &&
							m_pos.y - BULLET_SIZE / 2 < dragon_pos.y + 200)
						{
							//�h���S��HIT�֐��Ăяo��
							CDragon * pDragon = dynamic_cast<CDragon*> (pScene);
							if (pScene != NULL)
							{
								pDragon->Hit();
							}
							//�e�̍폜
							Uninit();
							return;
						}
					}
				}
				break;
				//�e�̎g�p�҂��G�̏ꍇ
			case USER_ENEMY:
				//�����I�u�W�F�^�C�v���v���C���[�̏ꍇ
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.x + BULLET_SIZE / 2 > player_pos.x - (PLAYER_SIZE - 55) &&
						m_pos.x - BULLET_SIZE / 2 < player_pos.x + (PLAYER_SIZE - 55) &&
						m_pos.y + BULLET_SIZE / 2 > player_pos.y - (PLAYER_SIZE - 55) &&
						m_pos.y - BULLET_SIZE / 2 < player_pos.y + (PLAYER_SIZE - 55))
					{
						//�v���C���[��HIT�֐��Ăяo��
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						if (pPlayer != NULL)
						{
							pPlayer->Hit();
						}

						Uninit();
						return;
					}
				}
				break;
				//�e�̎g�p�҂��h���S���̏ꍇ
			case USER_DRAGON:
				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.x + BULLET_SIZE / 2 > player_pos.x - (PLAYER_SIZE - 45) &&
						m_pos.x - BULLET_SIZE / 2 < player_pos.x + (PLAYER_SIZE - 45) &&
						m_pos.y + BULLET_SIZE / 2 > player_pos.y - (PLAYER_SIZE - 45) &&
						m_pos.y - BULLET_SIZE / 2 < player_pos.y + (PLAYER_SIZE - 45))
					{
						//�v���C���[��HIT�֐��Ăяo��
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						pPlayer->Hit();
						//�e�̍폜
						Uninit();
						return;
					}

				}
				break;
			default:
				break;
				return;
			}

			//�e�̎�ނɂ�鏈������
			switch (m_type)
			{
				//�����e�̎�ނ��U���e�̏ꍇ
			case TYPE_GUID:
				//�I�u�W�F�^�C�v���v���C���[�̏ꍇ
				if (objType == OBJTYPE_PLAYER)
				{
					//�ڕW�Ƃ̋��������߂�
					m_fDistance = float(sqrt((player_pos.x - m_pos.x) * (player_pos.x - m_pos.x) + (player_pos.y - m_pos.y) * (player_pos.y - m_pos.y)));

					if (m_fDistance)
					{
						m_move.x = ((player_pos.x - m_pos.x) / m_fDistance * m_fSpeed);
						m_move.y = ((player_pos.y - m_pos.y) / m_fDistance * m_fSpeed);
					}
					else
					{
						m_move.x = 0;
						m_move.y = m_fSpeed;
					}
				}
				break;
				//�����e�̎�ނ��΋��̎�
			case TYPE_FIREBALL:
				//�ړ��ʂ̒ǉ�
				m_move.x = 0.0f;
				m_move.y = 5.0f;

				if (objType == OBJTYPE_PLAYER)
				{
					if (m_pos.y >= player_pos.y)
					{
						//�����̔���
						CExplosion::Create(m_pos, 1120 - 200, FIELD_HEIGHT / 4, CExplosion::TYPE_FIERBALL);
						m_bFireBall = false;
						m_bCharage = false;
						Uninit();
						return;
					}
					m_TargetPos = pScene->GetPosition();
				}

				//�����I�u�W�F�^�C�v���h���S���̎�
				if (objType == OBJTYPE_DRAGON)
				{
					//�΋���X���W�ƃh���S����X���W�����킹��
					m_pos.x = dragon_pos.x;
					//�����u���X���ˏ�Ԃ�true��������
					if (m_bShotFireball == true)
					{
						//�e��Y���W�Ɉړ��ʂ�ǉ�
						m_pos.y += m_move.y;
						//�����u���X���ˏ�Ԃ�false�ɂ���
						m_bShotFireball = false;
					}
					else
					{
						m_pos.y = dragon_pos.y + (DRAGON_SIZE_HEIGHT / 2);
					}
				}
				break;
			case TYPE_FIRE:
				if (objType == OBJTYPE_DRAGON)
				{
					m_pos.x = dragon_pos.x;

					m_move.y = 10.0f;
				}
				break;
			}
		}
	}
}

//=============================================================================
// �ړ��\�͈͐��䏈���֐��֐�
//=============================================================================
void CBullet::MovableRange(void)
{
	//�����e����ʊO�ɍs������
	if (m_pos.y < 0 ||
		m_pos.y > FIELD_HEIGHT ||
		m_pos.x < FIELD_WIDTH_MIN ||
		m_pos.x > FIELD_WIDTH)
	{
		//�e�̍폜
		Uninit();
		return;
	}
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CBullet::SubLife(void)
{
	//�e�̃^�C�v���U���e��������
	if (m_type == TYPE_GUID)
	{
		//���C�t�̌��Z
		m_nLife--;
		//�������C�t��0�ȉ��ɂȂ����Ƃ�
		if (m_nLife <= 0)
		{
			//�e�̍폜
			Uninit();
			return;
		}
	}
	if (m_type == TYPE_FIRE)
	{
		m_nLife--;
		if (m_nLife <= 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// �ʒu�X�V�����֐�
//=============================================================================
void CBullet::UpdatePosition(void)
{
	//�e�̃^�C�v���_�������e�̎�
	if (m_type == TYPE_AIM)
	{
		//�ʒu�X�V
		m_pos.x += m_move.x * cosf(m_fAngle);
		m_pos.y += m_move.y * sinf(m_fAngle);
	}
	else
	{
		//�ʒu�X�V
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
	}
}

//=============================================================================
// �G�t�F�N�g���������֐�
//=============================================================================
void CBullet::EffectCreate(void)
{
	//�e�̃^�C�v���ʏ�e�̎�
	if (m_type == TYPE_NORMAL)
	{
		//�G�t�F�N�g�̐���
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE / 2, CEffect::TYPE_PLAYER);
	}
	//�e�̃^�C�v���U���e��������
	if (m_type == TYPE_GUID)
	{
		m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(255, 0, 0, 255), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	//�e�̃^�C�v��n_way�e��������
	if (m_type == TYPE_N_WAY)
	{
		//�G�t�F�N�g�̐���
		m_pEffect = CEffect::Create(m_pos, D3DCOLOR_RGBA(0, 0, 255, 255), BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	//�e�̃^�C�v���_�������e�̎�
	if (m_type == TYPE_AIM)
	{
		//�G�t�F�N�g�̐���
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_ENEMY);
	}
	if (m_type == TYPE_BREATHE)
	{
		//�G�t�F�N�g�̐���
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], BULLET_SIZE* 1.5f, BULLET_SIZE * 1.5f, EFFECT_LIFE, CEffect::TYPE_PLAYER);
	}
	//�e�̃^�C�v���΋���������
	if (m_type == TYPE_FIREBALL)
	{
		//�G�t�F�N�g�̐���
		m_pEffect = CEffect::Create(m_pos, m_aColor[m_pCol], (m_fWidth + 10.0f) * m_fScale, (m_fWidth + 10.0f) * m_fScale, 20, CEffect::TYPE_DRAGON);
	}
}
