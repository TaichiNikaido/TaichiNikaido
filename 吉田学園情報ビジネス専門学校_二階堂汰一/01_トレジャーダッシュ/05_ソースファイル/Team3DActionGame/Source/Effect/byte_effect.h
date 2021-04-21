//******************************************************************************
// バイトエフェクト [stan_effect.h]
// Author : 管原 司
//******************************************************************************
#ifndef _BYTE_EFFECT_H_
#define _BYTE_EFFECT_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "effect.h"
//******************************************************************************
// クラス
//******************************************************************************
class CByte_Effect : public CEffect
{
public:
	// 列挙型
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	}TYPE;
	CByte_Effect(int nPriority = 0);
	~CByte_Effect();
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CEffect::TEX_TYPE TexType, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void ByteEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	void Move(void);
	D3DXVECTOR3 m_SavePos;	// 位置保存
	TYPE m_Type;			// 種類
	int m_nCount;			// カウント
	bool bEndByte;			// 終了
};
#endif