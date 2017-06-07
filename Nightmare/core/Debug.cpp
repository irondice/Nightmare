
// freopen 有効化の為に定義
#define _CRT_SECURE_NO_WARNINGS

#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

namespace dream
{

void Debug::Setup(void)
{
	// Exeからの実行プロセスであるかを判定
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		// コンソール領域を確保
		AllocConsole();
	}

	// printf関連の出力をコンソールに設定
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	// デバッグモード開始の通知
	Log("[Dream] Debug Mode Enable!\n");
}

void Debug::Release(void)
{
	// コンソール情報を開放
	FreeConsole();
}

void Debug::Log(const char* message, ...)
{
	// この関数の可変引数をそのままprintf関数へ渡す為の処理
	va_list list;
	va_start(list, message);
	vprintf(message, list);
	printf("\n");
	va_end(list);
}

} // namespace dream
