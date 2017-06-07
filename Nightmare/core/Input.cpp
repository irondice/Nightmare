
#include "input.h"

namespace dream
{

PInputDevice Input::device = nullptr;

bool Input::GetKeyPress(KeyType type)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetKeyPress(type);
}

bool Input::GetKeyTrigger(KeyType type)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetKeyTrigger(type);
}

bool Input::GetKeyRelease(KeyType type)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetKeyRelease(type);
}



int Input::GetMouseX(void)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseX();
}

int Input::GetMouseY(void)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseY();
}



int Input::GetMouseAxisX(void)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseAxisX();
}

int Input::GetMouseAxisY(void)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseAxisY();
}

int Input::GetMouseAxisZ(void)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseAxisZ();
}



bool Input::GetMouseClickPress(ClickType type)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseClickPress(type);
}

bool Input::GetMouseClickTrigger(ClickType type)
{
	if (Input::device == nullptr) return false;
	return Input::device->GetMouseClickTrigger(type);
}





bool Input::GetJoyStickButtomPress(uint buttom_num)
{
	if (Input::device == nullptr) return false;

}

bool Input::GetJoyStickButtomRelease(uint buttom_num)
{
	if (Input::device == nullptr) return false;

}

bool Input::GetJoyStickButtomTrigger(uint buttom_num)
{
	if (Input::device == nullptr) return false;

}

int Input::GetJoyStickAxisX(void)
{
	if (Input::device == nullptr) return false;

}

int Input::GetJoyStickAxisY(void)
{
	if (Input::device == nullptr) return false;

}

int Input::GetJoyStickAxisZ(void)
{
	if (Input::device == nullptr) return false;

}

uint Input::GetJoyStickPow(u8 num)
{
	if (Input::device == nullptr) return false;

}



} // namespace dream
