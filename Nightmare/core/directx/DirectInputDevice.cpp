
#include "../input.h"

#ifdef _WIN32

namespace dream
{

DirectInputDevice::DirectInputDevice(std::shared_ptr<WindowScreen> screen) :
	screen(screen)
{
	ZeroMemory(this->key_state, sizeof(this->key_state[0]) * NUM_KEY_MAX);
}

DirectInputDevice::~DirectInputDevice(void)
{
	this->Release();
}

void DirectInputDevice::Setup(void)
{
	HWND hwnd = this->screen->GetHandleWindow();
	HINSTANCE hInstance = this->screen->GetHandleInstance();
	
	// DirectInputオブジェクトの作成
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**) &direct_input, NULL);

	if (FAILED(hr))
	{
		MessageBox(hwnd, L"DirectInputオブジェクトの生成に失敗しました。", L"警告！", MB_OK);
		return;
	}

	this->SetupKeyboard();

	this->SetupMouse();
}

void DirectInputDevice::Release(void)
{
	if (this->keyboard_device != nullptr)
	{
		this->keyboard_device->Unacquire();
		this->keyboard_device->Release();
		this->keyboard_device = nullptr;
	}

	if (this->mouse_device != nullptr)
	{
		this->mouse_device->Unacquire();
		this->mouse_device->Release();
		this->mouse_device = nullptr;
	}

	if (this->joystick_device != nullptr)
	{
		this->joystick_device->Unacquire();
		this->joystick_device->Release();
		this->joystick_device = nullptr;
	}

	if (this->direct_input != nullptr)
	{
		this->direct_input->Release();
		this->direct_input = nullptr;
	}
}

void DirectInputDevice::SetupKeyboard(void)
{
	HRESULT hr;

	HINSTANCE hInstance = this->screen->GetHandleInstance();
	HWND hwnd = this->screen->GetHandleWindow();

	// デバイスオブジェクトを作成
	hr = this->direct_input->CreateDevice(GUID_SysKeyboard, &this->keyboard_device, NULL);
	if (FAILED(hr) || this->keyboard_device == NULL)
	{
		MessageBox(hwnd, L"キーボードがねぇ！", L"警告！", MB_ICONWARNING);
		return;
	}

	// データフォーマットを設定
	hr = this->keyboard_device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"キーボードのデータフォーマットを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = this->keyboard_device->SetCooperativeLevel(this->screen->GetHandleWindow(), (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"キーボードの協調モードを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	hr = this->keyboard_device->Acquire();

}

void DirectInputDevice::SetupMouse(void)
{
	HRESULT hr;

	HINSTANCE hInstance = this->screen->GetHandleInstance();
	HWND hwnd = this->screen->GetHandleWindow();

	// デバイスオブジェクトを作成
	hr = direct_input->CreateDevice(GUID_SysMouse, &mouse_device, NULL);
	if (FAILED(hr) || mouse_device == NULL)
	{
		MessageBox(hwnd, L"マウスがねぇ！", L"警告！", MB_ICONWARNING);
		return;
	}

	// データフォーマットを設定
	hr = mouse_device->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"マウスのデータフォーマットを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = mouse_device->SetCooperativeLevel(hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"マウスの協調モードを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return;
	}

	// デバイスの設定
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = mouse_device->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	mouse_device->Acquire();

}

void DirectInputDevice::Update(void)
{
	// キーボード入力の更新
	this->UpdateKeyboard();

	// マウス入力の更新
	this->UpdateMouse();

	// ゲームパッド入力の更新
	this->UpdateJoyStick();
}

void DirectInputDevice::UpdateKeyboard(void)
{

	HRESULT hr;
	BYTE keyStateOld[NUM_KEY_MAX];
	uint repeat_frame = 20;

	// 前回のデータを保存
	memcpy(keyStateOld, key_state, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = this->keyboard_device->GetDeviceState(sizeof(key_state), key_state);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			// トリガーとリリースを取得
			this->key_state_trigger[cnt] = (this->key_state[cnt] ^ keyStateOld[cnt]) & this->key_state[cnt];
			this->key_state_release[cnt] = (this->key_state[cnt] ^ keyStateOld[cnt]) & keyStateOld[cnt];

			// キーが押されているならリピートの判定処理
			if (this->key_state[cnt])
			{

				// repeat_frame フレーム経過してから値を取得
				if (this->key_state_repeat_cnt[cnt] < repeat_frame)
				{
					this->key_state_repeat_cnt[cnt]++;

					if (this->key_state_repeat_cnt[cnt] == 1 || this->key_state_repeat_cnt[cnt] >= repeat_frame)
					{
						this->key_state_repeat[cnt] = 0x80;
					}
					else
					{
						this->key_state_repeat[cnt] = 0;
					}
				}
			}
			else
			{
				this->key_state_repeat_cnt[cnt] = 0;
				this->key_state_repeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		hr = this->keyboard_device->Acquire();
	}

	return;
}

void DirectInputDevice::UpdateMouse(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseStateOld;

	// 画面情報を取得
	HINSTANCE hInstance = this->screen->GetHandleInstance();
	HWND hwnd = this->screen->GetHandleWindow();

	// 前回のデータを保存
	mouseStateOld = this->mouse_state;

	// マウスポインタの位置を取得
	GetCursorPos(&this->mouse_point);
	ScreenToClient(hwnd, &this->mouse_point);

	// デバイスからデータを取得
	hr = this->mouse_device->GetDeviceState(sizeof(this->mouse_state), &this->mouse_state);
	if (SUCCEEDED(hr))
	{
		// トリガーの取得
		for (int cnt = 0; cnt < 8; cnt++)
		{
			this->mouse_state_trigger.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ this->mouse_state.rgbButtons[cnt]) & this->mouse_state.rgbButtons[cnt]);
		}
	}
	else
	{
		this->mouse_device->Acquire();
	}

	return;
}

void DirectInputDevice::UpdateJoyStick(void)
{

}

bool DirectInputDevice::GetMouseClickPress(ClickType type)
{

	switch (type)
	{

	case ClickType::CENTER:
	{
		return ((this->mouse_state.rgbButtons[2] & 0x80) != 0);
	}
	break;

	case ClickType::LEFT:
	{
		return ((this->mouse_state.rgbButtons[0] & 0x80) != 0);
	}
	break;

	case ClickType::RIGHT:
	{
		return ((this->mouse_state.rgbButtons[1] & 0x80) != 00);
	}
	break;

	}

	return false;
}

bool DirectInputDevice::GetMouseClickTrigger(ClickType type)
{
	switch (type)
	{

	case ClickType::CENTER:
	{
		return ((this->mouse_state.rgbButtons[2] & 0x80) != 0);
	}
	break;

	case ClickType::LEFT:
	{
		return ((this->mouse_state_trigger.rgbButtons[0] & 0x80) != 0);
	}
	break;

	case ClickType::RIGHT:
	{
		return ((this->mouse_state_trigger.rgbButtons[1] & 0x80) != 0);
	}
	break;

	}

	return false;
}

int DirectInputDevice::GetDirectInputKey(KeyType type)
{
	switch (type)
	{
	case dream::KeyType::A:
		return DIK_A;
	case dream::KeyType::B:
		return DIK_B;
	case dream::KeyType::C:
		return DIK_C;
	case dream::KeyType::D:
		return DIK_D;
	case dream::KeyType::E:
		return DIK_E;
	case dream::KeyType::F:
		return DIK_F;
	case dream::KeyType::G:
		return DIK_G;
	case dream::KeyType::H:
		return DIK_H;
	case dream::KeyType::I:
		return DIK_I;
	case dream::KeyType::J:
		return DIK_J;
	case dream::KeyType::K:
		return DIK_K;
	case dream::KeyType::L:
		return DIK_L;
	case dream::KeyType::M:
		return DIK_M;
	case dream::KeyType::N:
		return DIK_N;
	case dream::KeyType::O:
		return DIK_O;
	case dream::KeyType::P:
		return DIK_P;
	case dream::KeyType::Q:
		return DIK_Q;
	case dream::KeyType::R:
		return DIK_R;
	case dream::KeyType::S:
		return DIK_S;
	case dream::KeyType::T:
		return DIK_T;
	case dream::KeyType::U:
		return DIK_U;
	case dream::KeyType::V:
		return DIK_V;
	case dream::KeyType::W:
		return DIK_W;
	case dream::KeyType::X:
		return DIK_X;
	case dream::KeyType::Y:
		return DIK_Y;
	case dream::KeyType::Z:
		return DIK_Z;
	case dream::KeyType::NUM0:
		return DIK_0;
	case dream::KeyType::NUM1:
		return DIK_1;
	case dream::KeyType::NUM2:
		return DIK_2;
	case dream::KeyType::NUM3:
		return DIK_3;
	case dream::KeyType::NUM4:
		return DIK_4;
	case dream::KeyType::NUM5:
		return DIK_5;
	case dream::KeyType::NUM6:
		return DIK_6;
	case dream::KeyType::NUM7:
		return DIK_7;
	case dream::KeyType::NUM8:
		return DIK_8;
	case dream::KeyType::NUM9:
		return DIK_9;
	case dream::KeyType::SPACE:
		return DIK_SPACE;
	case dream::KeyType::RETURN:
		return DIK_RETURN;
	case dream::KeyType::SHIFT:
		return DIK_LSHIFT;
	case dream::KeyType::CONTROLE:
		return DIK_LCONTROL;
	case dream::KeyType::UP:
		return DIK_UP;
	case dream::KeyType::DOWN:
		return DIK_DOWN;
	case dream::KeyType::LEFT:
		return DIK_LEFT;
	case dream::KeyType::RIGHT:
		return DIK_RIGHT;
	case dream::KeyType::ESC:
		return DIK_ESCAPE;
	default:
		return 0;
	}
}

} // namespace dream

#endif // _WIN#2
