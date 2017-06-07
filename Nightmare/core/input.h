
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
// ���͌��m���ȈՓI�ɗ��p�o����悤�ɂ����N���X
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
	// �����Ă���Ԃ̃L�[�̓��͂����m���܂��B
	// 
	static bool GetKeyPress(KeyType type);

	// 
	// �������u�ԂɃL�[�̓��͂����m���܂�
	// 
	static bool GetKeyRelease(KeyType type);

	// 
	// ���͂����u�Ԃ̃L�[�̓��͂����m���܂��B
	// 
	static bool GetKeyTrigger(KeyType type);

public:

	// 
	// �E�B���h�E������N�_�Ƀ}�E�X�̈ʒuX���擾���܂��B
	// 
	static int GetMouseX(void);

	// 
	// �E�B���h�E������N�_�Ƀ}�E�X�̈ʒuY���擾���܂��B
	// 
	static int GetMouseY(void);

	// 
	// �}�E�X��X���̈ړ��ʂ��擾���܂��B
	// 
	static int GetMouseAxisX(void);
	
	// 
	// �}�E�X��Y���̈ړ��ʂ��擾���܂��B
	// 
	static int GetMouseAxisY(void);

	// 
	// �}�E�X��Z���̈ړ��ʂ��擾���܂��B
	// 
	static int GetMouseAxisZ(void);

	// 
	// �}�E�X�̃{�^������͂��Ă���Ԃ����m���܂��B
	// 
	static bool GetMouseClickPress(ClickType type);

	// 
	// �}�E�X�̃{�^������͂����u�Ԃ����m���܂��B
	// 
	static bool GetMouseClickTrigger(ClickType type);

public:

	// 
	// �Q�[���p�b�h�̃{�^�����͂��Ă���Ԃ����m���܂��B
	// 
	static bool GetJoyStickButtomPress(uint buttom_num);

	// 
	// �Q�[���p�b�h�̃{�^�����͂��Ă���Ԃ����m���܂��B
	// 
	static bool GetJoyStickButtomRelease(uint buttom_num);

	// 
	// �Q�[���p�b�h�̃{�^�����͂��Ă���Ԃ����m���܂��B
	// 
	static bool GetJoyStickButtomTrigger(uint buttom_num);

	// 
	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͂�X�����m���܂��B
	// ���m�����l�ɉ����ĕԂ��l�͕ϓ����܂��B
	// 
	static int GetJoyStickAxisX(void);

	// 
	// �Q�[���p�b�h�̃X�e�B�b�N�̓���Y�������m���܂��B
	// ���m�����l�ɉ����ĕԂ��l�͕ϓ����܂��B
	// 
	static int GetJoyStickAxisY(void);

	// 
	// �Q�[���p�b�h�̃X�e�B�b�N�̓���Z�������m���܂��B
	// ���m�����l�ɉ����ĕԂ��l�͕ϓ����܂��B
	// 
	static int GetJoyStickAxisZ(void);

	// 
	// �n�b�g�X�C�b�`�̓��͌��m�����܂��B
	// �����̒l�ɑΉ������n�b�g�X�C�b�`�̌��m���o���܂��B
	// 
	static uint GetJoyStickPow(u8 num = 0);

public:

	// 
	// ���̃N���X�Ɏg�p����f�o�C�X����ݒ肵�܂��B
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
