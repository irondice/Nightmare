
#include "../converter.h"

#ifdef _WIN32

namespace dream
{

errno_t WindowStringConverter::err = 0;

void WindowStringConverter::Convert(LPCCH str, PWCHAR w_str, UINT length)
{
	size_t wLen = 0;
	::setlocale(LC_ALL, "japanese");
	WindowStringConverter::err = ::mbstowcs_s(&wLen, w_str, length, str, _TRUNCATE);
}

void WindowStringConverter::Convert(LPCWCH w_str, PCHAR str, UINT length)
{
	size_t wLen = 0;
	::setlocale(LC_ALL, "japanese");
	WindowStringConverter::err = ::wcstombs_s(&wLen, str, length, w_str, _TRUNCATE);
}

std::shared_ptr<WCHAR> WindowStringConverter::GetConvertString(LPCCH str)
{
	int length = strlen(str) + 1;
	PWCHAR w_str = new WCHAR[length];
	WindowStringConverter::Convert(str, w_str, length);
	return std::shared_ptr<WCHAR>(w_str);
}

std::shared_ptr<CHAR> WindowStringConverter::GetConvertString(LPCWCH w_str)
{
	int length = wcslen(w_str) + 1;
	PCHAR str = new CHAR[length];
	WindowStringConverter::Convert(w_str, str, length);
	return std::shared_ptr<CHAR>(str);
}

errno_t WindowStringConverter::GetErrorNumber(void)
{
	return WindowStringConverter::err;
}

} // namespace dream

#endif // _WIN32
