//=============================================================================
//
// ���C�� [main.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX		(4)
#define INITIAL_D3DXVECTOR3 (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define INITIAL_D3DXCOLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define INITIAL_INT (0)
#define INITIAL_FLOAT (0.0f)
#define MAX_TEXT (32)

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"ws2_32.lib")

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float		rhw;	//���W�ϊ��p���W��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`��
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`��
}VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif
#endif