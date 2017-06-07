
#ifndef __NM_INPUT_H__
#define __NM_INPUT_H__

#include "screen.h"
#include "types.h"
#include "project.h"

namespace dream
{

enum class KeyType
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	SPACE,
	RETURN,
	SHIFT,
	CONTROLE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
};

enum class ClickType
{
	LEFT,
	RIGHT,
	CENTER,
};

// 
// 入力検知を簡易的に利用出来るようにしたクラス
// 
class Input final
{
private:

	static PInputDevice device;

private:

	Input(void) {}
	~Input(void) {}

public:

	// 
	// 押している間のキーの入力を検知します。
	// 
	static bool GetKeyPress(KeyType type);

	// 
	// 離した瞬間にキーの入力を検知します
	// 
	static bool GetKeyRelease(KeyType type);

	// 
	// 入力した瞬間のキーの入力を検知します。
	// 
	static bool GetKeyTrigger(KeyType type);

public:

	// 
	// ウィンドウ左上を起点にマウスの位置Xを取得します。
	// 
	static int GetMouseX(void);

	// 
	// ウィンドウ左上を起点にマウスの位置Yを取得します。
	// 
	static int GetMouseY(void);

	// 
	// マウスのX軸の移動量を取得します。
	// 
	static int GetMouseAxisX(void);
	
	// 
	// マウスのY軸の移動量を取得します。
	// 
	static int GetMouseAxisY(void);

	// 
	// マウスのZ軸の移動量を取得します。
	// 
	static int GetMouseAxisZ(void);

	// 
	// マウスのボタンを入力している間を検知します。
	// 
	static bool GetMouseClickPress(ClickType type);

	// 
	// マウスのボタンを入力した瞬間を検知します。
	// 
	static bool GetMouseClickTrigger(ClickType type);

public:

	// 
	// ゲームパッドのボタン入力している間を検知します。
	// 
	static bool GetJoyStickButtomPress(uint buttom_num);

	// 
	// ゲームパッドのボタン入力している間を検知します。
	// 
	static bool GetJoyStickButtomRelease(uint buttom_num);

	// 
	// ゲームパッドのボタン入力している間を検知します。
	// 
	static bool GetJoyStickButtomTrigger(uint buttom_num);

	// 
	// ゲームパッドのスティックの入力をX軸検知します。
	// 検知した値に応じて返し値は変動します。
	// 
	static int GetJoyStickAxisX(void);

	// 
	// ゲームパッドのスティックの入力Y軸を検知します。
	// 検知した値に応じて返し値は変動します。
	// 
	static int GetJoyStickAxisY(void);

	// 
	// ゲームパッドのスティックの入力Z軸を検知します。
	// 検知した値に応じて返し値は変動します。
	// 
	static int GetJoyStickAxisZ(void);

	// 
	// ハットスイッチの入力検知をします。
	// 引数の値に対応したハットスイッチの検知が出来ます。
	// 
	static uint GetJoyStickPow(u8 num = 0);

public:

	// 
	// このクラスに使用するデバイス情報を設定します。
	// 
	static void SetInputDevice(PInputDevice device)
	{
		Input::device = device;
	}

};

class InputDevice abstract
{
public:

	explicit InputDevice(void) {}
	virtual ~InputDevice(void) {}

public:

	virtual void Setup(void) = 0 {}

	virtual void Release(void) = 0 {}

	virtual void Update(void) = 0 {}

	virtual bool GetKeyPress(KeyType type) = 0 {}
	virtual bool GetKeyRelease(KeyType type) = 0 {}
	virtual bool GetKeyTrigger(KeyType type) = 0 {}

public:

	virtual int GetMouseX(void) = 0 {}
	virtual int GetMouseY(void) = 0 {}

	virtual int GetMouseAxisX(void) = 0 {}
	virtual int GetMouseAxisY(void) = 0 {}
	virtual int GetMouseAxisZ(void) = 0 {}

	virtual bool GetMouseClickPress(ClickType type) = 0 {}
	virtual bool GetMouseClickTrigger(ClickType type) = 0 {}

};

#ifdef NM_USE_DIRECTX

class DirectInputDevice : public InputDevice
{
private:

	const static uint NUM_KEY_MAX = 256;
	const static uint NUM_BUTTON_MAX = 32;

private:

	std::shared_ptr<WindowScreen> screen;

	LPDIRECTINPUT8 direct_input = nullptr;

	LPDIRECTINPUTDEVICE8 keyboard_device	= nullptr;
	BYTE key_state[NUM_KEY_MAX];
	BYTE key_state_trigger[NUM_KEY_MAX];
	BYTE key_state_repeat[NUM_KEY_MAX];
	BYTE key_state_release[NUM_KEY_MAX];
	uint key_state_repeat_cnt[NUM_KEY_MAX];

	LPDIRECTINPUTDEVICE8 mouse_device		= nullptr;
	DIMOUSESTATE2 mouse_state;
	DIMOUSESTATE2 mouse_state_trigger;
	POINT mouse_point;

	LPDIRECTINPUTDEVICE8 joystick_device	= nullptr;
	DIDEVCAPS devcaps;
	DIJOYSTATE state;
	BYTE key_state_joystick[NUM_BUTTON_MAX];
	BYTE key_state_trigger_joystick[NUM_BUTTON_MAX];
	BYTE key_state_repeat_joystick[NUM_BUTTON_MAX];
	BYTE key_state_release_joystick[NUM_BUTTON_MAX];
	uint key_state_repeat_cnt_joystick[NUM_BUTTON_MAX];

public:

	DirectInputDevice(std::shared_ptr<WindowScreen> screen);
	~DirectInputDevice(void);

public:

	void Setup(void) override;

	void Release(void) override;

private:

	void SetupKeyboard(void);

	void SetupMouse(void);

public:

	void Update(void) override;

private:

	void UpdateKeyboard(void);

	void UpdateMouse(void);

	void UpdateJoyStick(void);

public:

	bool GetKeyPress(KeyType type) override
	{
		return ((this->key_state[this->GetDirectInputKey(type)] & 0x80) != 0);
	}

	bool GetKeyTrigger(KeyType type) override
	{
		return ((this->key_state_trigger[this->GetDirectInputKey(type)] & 0x80) != 0);
	}

	bool GetKeyRelease(KeyType type) override
	{
		return ((this->key_state_release[this->GetDirectInputKey(type)] & 0x80) != 0);
	}

public:

	int GetMouseX(void) override
	{
		return this->mouse_point.x;
	}

	int GetMouseY(void) override
	{
		return this->mouse_point.y;
	}

	int GetMouseAxisX(void) override
	{
		return this->mouse_state.lX;
	}

	int GetMouseAxisY(void) override
	{
		return this->mouse_state.lY;
	}

	int GetMouseAxisZ(void) override
	{
		return this->mouse_state.lZ;
	}

public:

	bool GetMouseClickPress(ClickType type) override;

	bool GetMouseClickTrigger(ClickType type) override;

private:

	int GetDirectInputKey(KeyType type);

private:

	std::string GetErrorMessage(HRESULT hr);

};

#endif // NM_USE_DIRECTX

} // namespace dream

#endif // __NM_INPUT_H__
