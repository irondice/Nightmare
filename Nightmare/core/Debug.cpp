
// freopen �L�����ׂ̈ɒ�`
#define _CRT_SECURE_NO_WARNINGS

#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

namespace dream
{

void Debug::Setup(void)
{
	// Exe����̎��s�v���Z�X�ł��邩�𔻒�
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		// �R���\�[���̈���m��
		AllocConsole();
	}

	// printf�֘A�̏o�͂��R���\�[���ɐݒ�
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	// �f�o�b�O���[�h�J�n�̒ʒm
	Log("[Dream] Debug Mode Enable!\n");
}

void Debug::Release(void)
{
	// �R���\�[�������J��
	FreeConsole();
}

void Debug::Log(const char* message, ...)
{
	// ���̊֐��̉ψ��������̂܂�printf�֐��֓n���ׂ̏���
	va_list list;
	va_start(list, message);
	vprintf(message, list);
	printf("\n");
	va_end(list);
}

} // namespace dream
