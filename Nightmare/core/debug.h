
#ifndef __NM_DEBUG_H__
#define __NM_DEBUG_H__

#include "types.h"
#include "project.h"

namespace dream
{

// 
// �f�o�b�O����\������N���X�ł��B
// ���̃N���X�Œ�`���ꂽ�֐����`�̖w�ǂ�
// Debug::Setup(void) �̌Ăяo���L���Ŗ������o���܂��B
// 
// �f�o�b�O
// - �R���\�[����ʂ��\������܂��B
//   - ���b�Z�[�W�\���ɂ� Log(const char* message, ...) ���g�p���܂��B
// 
class Debug
{
public:

	// 
	// �f�o�b�O�����Ăяo���܂��B
	// 
	static void Setup(void);

	// 
	// �f�o�b�O�����J�����܂��B
	// 
	static void Release(void);

	// 
	// �f�o�b�O���b�Z�[�W��\�����܂��B
	// 
	static void Log(const char* message, ...);

};

} // namespace dream

#endif // __NM_DEBUG_H__
