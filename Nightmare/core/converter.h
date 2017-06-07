
#ifndef __NM_CONVERTER_H__
#define __NM_CONVERTER_H__

#include "project.h"

#ifdef _WIN32

namespace dream
{

// 
// 文字の変換に使用するクラスです。
// 
class WindowStringConverter
{
private:

	static errno_t err;			// エラーコード

public:

	// 
	// 文字列をワイド文字列に変換します。
	// w_str 引数の配列の数は str 引数の文字数以上の数を用意してください。
	// 
	// @param str   - 変換対象の文字配列
	// @param w_str - 格納先のワイド文字配列
	// 
	static void Convert(LPCCH str, PWCHAR w_str, UINT length);

	// 
	// ワイド文字列を文字列に変換します。
	// str 引数の配列の数は w_str 引数の文字数以上の数を用意してください。
	// 
	// @param w_str - 変換対象のワイド文字配列
	// @param str   - 格納先の文字配列
	// 
	static void Convert(LPCWCH w_str, PCHAR str, UINT length);

	// 
	// 文字列をワイド文字列に変換した結果を返します。
	// 
	// @param str - 変換対象の文字配列
	// @return      変換後のワイド文字列
	// 
	static std::shared_ptr<WCHAR> GetConvertString(LPCCH str);

	// 
	// ワイド文字列を文字列に変換した結果を返します。
	// 
	// @param w_str - 変換対象のワイド文字列
	// @return      - 変換後の文字列
	// 
	static std::shared_ptr<CHAR> GetConvertString(LPCWCH w_str);

public:

	// 
	// クラス内で処理した際に起きたエラーコードを返します。
	// 
	static errno_t GetErrorNumber(void);

};

} // namespace dream

#endif // _WIN32

#endif // __NM_CONVERTER_H__
