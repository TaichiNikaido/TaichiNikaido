//=============================================================================
//
// �p�[�e�B�N�� [particle.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_tool.h"
#include "renderer.h"
#include "particle.h"
#include "tool.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/particle.jpg")	//�e�N�X�`���̃p�X
#define STANDARD_SCALE (1.0f)						//���{
#define DEATH_LIBNE (0)								//���S���C��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle()
{
	m_Move = INITIAL_D3DXVECTOR3;	//�ړ���
	m_nLife = 0;					//�̗�
	m_fAngle = D3DXToRadian(0.0f);	//�p�x
	m_bLife = false;				//�̗͂��g�p���邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CParticle::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CParticle::TextureUnload(void)
{
	// �e�N�X�`���̔j��
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
CParticle * CParticle::Create(void)
{
	//�p�[�e�B�N���̃|�C���^
	CParticle * pParticle = NULL;
	//�����p�[�e�B�N���̃|�C���^��NULL�������ꍇ
	if (pParticle == NULL)
	{
		//�p�[�e�B�N���̃������m��
		pParticle = new CParticle;
		//�c�[���̎擾
		CTool * pTool = CToolMode::GetTool();
		if (pTool != NULL)
		{
			//�ʒu���擾����
			D3DXVECTOR3 Position = pTool->GetPosition();
			//��]���擾����
			D3DXVECTOR3 Rotation = pTool->GetRotation();
			//�T�C�Y���擾����
			D3DXVECTOR3 Size = pTool->GetSize();
			//�ړ��ʂ��擾����
			pParticle->m_Move = pTool->GetMove();
			//�F���擾����
			D3DXCOLOR Color = pTool->GetColor();
			//�g�k���擾����
			float fScale = pTool->GetScale();
			//�p�x���擾����
			pParticle->m_fAngle = D3DXToRadian(pTool->GetAngle());
			//���C�t�̎g�p��Ԃ��擾����
			pParticle->m_bLife = pTool->GetbLife();
			//�����p�[�e�B�N���̃|�C���^��NULL����Ȃ��ꍇ
			if (pParticle != NULL)
			{
				//�ʒu��ݒ肷��
				pParticle->SetPosition(Position);
				//��]��ݒ肷��
				pParticle->SetRotation(Rotation);
				//�T�C�Y��ݒ肷��
				pParticle->SetSize(Size);
				//�F��ݒ肷��
				pParticle->SetColor(Color);
				//�g�k�̎g�p��Ԃ�true��������
				if (pTool->GetbScale() == true)
				{
					//�g�k��ݒ肷��
					pParticle->SetScale(fScale);
				}
				else
				{
					//�g�k�𓙔{�Őݒ肷��
					pParticle->SetScale(STANDARD_SCALE);
				}
				//�p�[�e�B�N���̏������֐��Ăяo��
				pParticle->Init();
			}
		}
	}
	//�p�[�e�B�N���̃|�C���^��Ԃ�
	return pParticle;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CParticle::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�r���{�[�h�̏����������֐��Ăяo��
	CBillboard::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�c�[���̎擾
	CTool * pTool = CToolMode::GetTool();
	//�����c�[���̃|�C���^��NULL����Ȃ��ꍇ
	if (pTool != NULL)
	{
		//�̗͂��擾����
		m_nLife = pTool->GetLife();
		float fAngle = float(rand() % (int)pTool->GetAngle());
		m_fAngle = fAngle;
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CParticle::Uninit(void)
{
	//�r���{�[�h�̏I�������֐��Ăяo��
	CBillboard::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CParticle::Update(void)
{
	//�r���{�[�h�̍X�V�����֐��Ăяo��
	CBillboard::Update();
	//�c�[���̎擾
	CTool * pTool = CToolMode::GetTool();
	//�����c�[���̃|�C���^��NULL����Ȃ��ꍇ
	if (pTool != NULL)
	{
		//��]���擾����
		D3DXVECTOR3 Rotation = pTool->GetRotation();
		//�T�C�Y���擾����
		D3DXVECTOR3 Size = pTool->GetSize();
		//�ړ��ʂ��擾����
		m_Move = pTool->GetMove();
		//�F���擾����
		D3DXCOLOR Color = pTool->GetColor();
		//�g�k���擾����
		float fScale = pTool->GetScale();
		//�p�x���擾����
		//m_fAngle = D3DXToRadian(pTool->GetAngle());
		//�̗͂̎g�p��Ԃ��擾����
		m_bLife = pTool->GetbLife();
		//��]��ݒ肷��
		SetRotation(Rotation);
		//�T�C�Y��ݒ肷��
		SetSize(Size);
		//�F��ݒ肷��
		SetColor(Color);
		//�����g�k�̎g�p��Ԃ�true��������
		if (pTool->GetbScale() == true)
		{
			//�g�k��ݒ肷��
			SetScale(fScale);
		}
		else
		{
			//�g�k�𓙔{�ɐݒ肷��
			SetScale(STANDARD_SCALE);
		}
	}
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//X���W�̈ʒu�X�V
	Position.x += m_Move.x * cosf(D3DXToRadian(m_fAngle));
	//Y���W�̈ʒu�X�V
	Position.y += m_Move.y * sinf(D3DXToRadian(m_fAngle));
	//Z���W�̈ʒu�X�V
	Position.z += m_Move.z * sinf(D3DXToRadian(m_fAngle));
	//�ʒu��ݒ肷��
	SetPosition(Position);
	//�����̗͂̎g�p��Ԃ�true�̏ꍇ
	if (m_bLife == true)
	{
		//�̗͂����Z����
		m_nLife--;
		//�����̗͂�0�ɂȂ�����
		if (m_nLife <= DEATH_LIBNE)
		{
			//�I�������֐��Ăяo��
			Uninit();
			return;
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CParticle::Draw(void)
{
	//�r���{�[�h�̕`�揈���֐��Ăяo��
	CBillboard::Draw();
}
