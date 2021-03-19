//=============================================================================
//
// �΂̕��̃e�N�X�`�� [particle_texture_sparks.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PARTICLE_TEXTURE_SPARKS_H_
#define _PARTICLE_TEXTURE_SPARKS_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "particle_texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSparksTexture :public CParticleTexture
{
public:
	CSparksTexture();
	~CSparksTexture();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CSparksTexture * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation,D3DXVECTOR3 Size,D3DXVECTOR3 Move,int nLife);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};
#endif