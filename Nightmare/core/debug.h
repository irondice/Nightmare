
#ifndef __NM_DEBUG_H__
#define __NM_DEBUG_H__

#include "types.h"
#include "project.h"

namespace dream
{

// 
// デバッグ情報を表示するクラスです。
// このクラスで定義された関数や定義の殆どは
// Debug::Setup(void) の呼び出し有無で無効化出来ます。
// 
// デバッグ
// - コンソール画面が表示されます。
//   - メッセージ表示には Log(const char* message, ...) を使用します。
// 
class Debug
{
public:

	// 
	// デバッグ情報を呼び出します。
	// 
	static void Setup(void);

	// 
	// デバッグ情報を開放します。
	// 
	static void Release(void);

	// 
	// デバッグメッセージを表示します。
	// 
	static void Log(const char* message, ...);

};

} // namespace dream

#endif // __NM_DEBUG_H__
