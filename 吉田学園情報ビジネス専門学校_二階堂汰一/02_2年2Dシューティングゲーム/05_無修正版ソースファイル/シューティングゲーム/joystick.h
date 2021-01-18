//=============================================================================
//
// ジョイスティック処理 [joystick.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#define INITGUID

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define JS_X 0
#define JS_Y 1
#define JS_A 2
#define JS_B 3
#define	NUM_JS_MAX (256)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInputJoystick : public CInput
{
public:
	CInputJoystick();
	~CInputJoystick();
	HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	void UninitInput(void);
	void UpdateInput(void);
	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);
	BOOL CreateEffect(HWND);
	static BOOL CALLBACK EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }
	static LPDIRECTINPUTEFFECT GetEffect(void) { return m_IpDIEffect; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;
	DIDEVCAPS	m_diDevCaps;				//Caps
	static LPDIRECTINPUTEFFECT m_IpDIEffect;//エフェクト
	DWORD m_dwNumForceFeedbackAxis;			//フォースフィードバック
	DWORD m_rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  m_rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;

	BYTE m_aJoyState[NUM_JS_MAX];			// ジョイスティックの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];	//ジョイスティックトリガー情報
	BYTE m_aJoyStateRelease[NUM_JS_MAX];	// ジョイスティックリリース情報
};
#endif