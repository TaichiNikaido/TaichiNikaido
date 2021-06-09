//=============================================================================
//
// �h���S���̗̑�UI [ui_life_dragon.cpp]
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
#include "ui_life_gauge_dragon.h"
#include "Polygon2d/gauge.h"
#include "Character/enemy_dragon.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE (D3DXVECTOR3(800.0f,15.0f,0.0f))
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 - (SIZE.x / 2),SCREEN_HEIGHT / 6,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDragonLifeGaugeUI::CDragonLifeGaugeUI()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDragonLifeGaugeUI::~CDragonLifeGaugeUI()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CDragonLifeGaugeUI * CDragonLifeGaugeUI::Create()
{
	//�h���S���̗̑�UI�|�C���^
	CDragonLifeGaugeUI * pDragonLifeUI = nullptr;
	//�h���S���̗̑�UI�|�C���^��nullptr�̏ꍇ
	if (pDragonLifeUI == nullptr)
	{
		//�h���S���̗̑�UI�̃������m��
		pDragonLifeUI = new CDragonLifeGaugeUI;
		//�h���S���̗̑�UI�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pDragonLifeUI != nullptr)
		{
			//�h���S���̗̑�UI�̈ʒu��ݒ肷��
			pDragonLifeUI->SetPosition(POSITION);
			//�h���S���̗̑�UI�̃T�C�Y��ݒ肷��
			pDragonLifeUI->SetSize(SIZE);
			//�h���S���̗̑�UI�̐F��ݒ肷��
			pDragonLifeUI->SetColor(COLOR);
			//�h���S���̗̑�UI�̏����������֐��Ăяo��
			pDragonLifeUI->Init();
		}
	}
	//�h���S���̗̑�UI�̃|�C���^��Ԃ�
	return pDragonLifeUI;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CDragonLifeGaugeUI::Init(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	D3DXVECTOR3 Size = GetSize();
	D3DXCOLOR Color = GetColor();
	//�h���S�����擾����
	CDragon * pDragpn = CGameMode::GetDragon();
	//�����h���S���̃|�C���^��nullptr����Ȃ��ꍇ
	if (pDragpn != nullptr)
	{
		//�h���S���̗̑͂��擾
		int nLife = pDragpn->GetLife();
		//�̗͂̍ő�l��ݒ�
		SetMaxLife(nLife);
		//�̗͂�ݒ�
		SetLife(nLife);
	}
	//�Q�[�W�̐��������֐��Ăяo��
	SetGauge(CGauge::Create(Position, Size, Color));
	//���C�t�̏����������֐��Ăяo��
	CLifeGaugeUI::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CDragonLifeGaugeUI::Uninit(void)
{
	//���C�t��UI�̏I�������֐��Ăяo��
	CLifeGaugeUI::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CDragonLifeGaugeUI::Update(void)
{
	//�̗�UI�̍X�V�����֐��Ăяo��
	CLifeGaugeUI::Update();
	//�h���S�����擾����
	CDragon * pDragon = CGameMode::GetDragon();
	//�����h���S���̃|�C���^��nullptr����Ȃ��ꍇ
	if (pDragon != nullptr)
	{
		//�h���S���̗̑͂��擾
		int nLife = pDragon->GetLife();
		//�̗͂�ݒ�
		SetLife(nLife);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CDragonLifeGaugeUI::Draw(void)
{
	//���C�t�Q�[�WUI�̕`�揈���֐��Ăяo��
	CLifeGaugeUI::Draw();
}