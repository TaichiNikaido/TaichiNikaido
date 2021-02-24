//=============================================================================
//
// �΋��̔��� [explosion_fireball.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "explosion_dragon.h"
#include "explosion_death.h"
#include "enemy_dragon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_TIMNE (0)
#define EXPLOSION_DRAGON_SIZE D3DXVECTOR3(200.0f,200.0f,200.0f)
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosionDragon::CExplosionDragon()
{
	m_nTime = INITIAL_TIMNE;	//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosionDragon::~CExplosionDragon()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CExplosionDragon * CExplosionDragon::Create(void)
{
	//�h���S���̔����̃|�C���^
	CExplosionDragon * pExplosionDragon = NULL;
	//�����h���S���̔����̃|�C���^��NULL�̏ꍇ
	if (pExplosionDragon == NULL)
	{
		//�h���S���̔����̃������m��
		pExplosionDragon = new CExplosionDragon;
		//�����h���S���̔����̃|�C���^��NULL����Ȃ��ꍇ
		if (pExplosionDragon != NULL)
		{
			//�����������֐��Ăяo��
			pExplosionDragon->Init();
		}
	}
	//�h���S���̔����̃|�C���^��Ԃ�
	return pExplosionDragon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CExplosionDragon::Init(void)
{
	//�h���S���̎擾
	CEnemyDragon * pEnemyDragon = CGameMode::GetDragon();
	//�����h���S���̃|�C���^��NULL����Ȃ��ꍇ
	if (pEnemyDragon != NULL)
	{
		//�h���S���̈ʒu���擾����
		D3DXVECTOR3 DoragonPosition = pEnemyDragon->GetPosition();
		CExplosionDeath::Create(DoragonPosition, EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x + 50.0f, DoragonPosition.y + 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x + 50.0f, DoragonPosition.y - 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x - 50.0f, DoragonPosition.y + 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
		CExplosionDeath::Create(D3DXVECTOR3(DoragonPosition.x - 50.0f, DoragonPosition.y - 50.0f, DoragonPosition.z), EXPLOSION_DRAGON_SIZE);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CExplosionDragon::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CExplosionDragon::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CExplosionDragon::Draw(void)
{
}
