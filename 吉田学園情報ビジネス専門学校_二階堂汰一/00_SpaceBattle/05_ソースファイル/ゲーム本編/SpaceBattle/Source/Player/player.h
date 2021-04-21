//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene2d.h"
#include "System/name.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS  (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f))	//�v���C���[�̈ʒu
#define PLAYER_SIZE (D3DXVECTOR3(65.0f,65.0f,0.0f))								//�v���C���[�̃T�C�Y													
#define PLAYER_MAX_BOMB (5)														//�v���C���[�̍ő�{����
#define PLAYER_MAX_LIFE (5)														//�v���C���[�̍ő僉�C�t

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer :public CScene2d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//���S
		STATE_INVINCIBLE,	//���G
		STATE_MAX
	}STATE;		//���
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//�����
		INPUT_DOWN,		//������
		INPUT_LEFT,		//������
		INPUT_RIGHT,	//�E����
		INPUT_BOMB,		//�{������
		INPUT_SHOT,		//�e����
		INPUT_MAX
	}INPUT;		//���͏��
	typedef enum
	{
		ATTACK_NONE = -1,
		ATTACK_SHOT,	//�e����
		ATTACK_BOMB,	//�{������
		ATTACK_MAX
	}ATTACK;	//�U�����
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;		//���x��
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(void);
	void SubLife(int nValue);
	void LevelUp(void);
	void AddBomb(void);
	void SubBomb(void);
	void AddScore(int nValue);
	void SubScore(int nValue);
	STATE GetState(void) { return m_State; }
	int GetScore(void) { return m_nScore; }
	static void SetPlayerName(int nCount, char aName);
	static void SetbReplay(bool bReplay) { m_bReplay = bReplay; }
	static bool GetReplay(void) { return m_bReplay; }
	void Clear(void);
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Invincible(void);
	void Respawn(void);
	D3DXVECTOR3 MovableRange(void);
	void Replay(void);
	void DeleteAllBullet(void);
	void TimeCount(void);
	void DataSave(void);
	void InputDataSave(void);
	void InputDataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	static  char m_aPlayerName[MAX_NAME];	//���O
	static bool m_bReplay;					//���v���C�Ȃ̂�
	D3DXVECTOR3 m_Move;						//�ړ���
	int m_nLife;							//�̗�
	int m_nBomb;							//���e�̏�����
	int m_nUseBomb;							//���e�̎g�p��
	int m_nDeathCount;						//���S��
	int m_nContinue;						//�R���e�B�j���[��
	int m_nScore;							//�X�R�A
	int m_nLevel;							//���x��
	int m_nDeathTime;						//���S����
	int m_nInvincibleTime;					//���G����
	int m_nBulletInterval;					//���ˊԊu
	float m_fSpeed;							//����
	char m_aInputData[15000][INPUT_MAX];	//���͏��
	STATE m_State;							//���
	INPUT m_Input;							//���̓L�[���
	ATTACK m_Attack;						//�U�����
};
#endif