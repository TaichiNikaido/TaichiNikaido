//=============================================================================
//
// キャラクター [character.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3d.h"
#include "model.h"
#include "motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharacter : public CScene3d
{
public:
	CCharacter();
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetModelScriptPass(const char * pModelScriptPass) { m_apModelScriptPass[0] = pModelScriptPass; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	CModel * GetModel(int nParts) { return m_pModel[nParts]; }
	CMotion * GetpMotion(void) { return m_pMotion; }
private:
	const char * m_apModelScriptPass[32];					//モデルのスクリプトパス
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];				//モデルデータ
	CMotion * m_pMotion;									//モーションのポインタ
	CModel * m_pModel[MAX_PARTS];							//モデルのポインタ
};
#endif
