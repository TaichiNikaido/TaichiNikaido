//=============================================================================
//
// ���[���z�[�� [wormhole.h]
// Author : ��K������
//
//=============================================================================
#ifndef _WORMHOLE_H_
#define _WORMHOLE_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WORMHOLE		"data/TEXTURE/hole002.png"	//�e�N�X�`���̕ۑ���
#define TEXTURE_WORMHOLEEFFECT	"data/TEXTURE/hole001.png"	//�e�N�X�`���̕ۑ���
#define MAX_WORMHOLE_TEXTURE 2								//���[���z�[���̃e�N�X�`���̍ő吔
#define WORMHOLE_TEXTURE_SIZE 50.0f							//���[���z�[���̃e�N�X�`���T�C�Y
#define WORMHOLEEFFECT_TEXTURE_SIZE 200.0f					//���[���z�[���̃G�t�F�N�g�T�C�Y
#define WORMHOLE_SPEED 1.0f									//���[���z�[���̃X�s�[�h
#define WORMHOLE_SIZE 50.0f									//���[���z�[���̓����蔻��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWormhole :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_DRAGON,
		TYPE_BOSS,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		TEX_NONE = -1,
		TEX_HOLE,
		TEX_EFFECT,
		TEX_MAX
	}TEXTURE;
	CWormhole(int nPriority = 4);
	~CWormhole();
	static HRESULT Load(void);
	static void Unload(void);
	static CWormhole * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,TYPE type,TEXTURE texture,D3DCOLOR col);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Spawn(void);
	static bool GetSpawn(void){return m_bSpawn; };
	static void SetSpawn(bool bSpawn);
private:
	void Scale(void);
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_WORMHOLE_TEXTURE];
	static bool	m_bSpawn;
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
	D3DCOLOR	m_col[NUM_VERTEX];	//���_�J���[
	D3DXVECTOR3	m_rot;				//����
	TYPE		m_Type;				//�^�C�v
	TEXTURE     m_Texture;			//�e�N�X�`��
	float		m_fAngle;			//�p�x
	float		m_fLength;			//����
	float		m_fScale;			//�傫��
	float		m_fAddScale;		//�傫���̉��Z��
	int			m_nCountSpawn;		//�X�|�[���J�E���g
};
#endif