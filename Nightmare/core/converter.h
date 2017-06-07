
#ifndef __NM_CONVERTER_H__
#define __NM_CONVERTER_H__

#include "project.h"

#ifdef _WIN32

namespace dream
{

// 
// �����̕ϊ��Ɏg�p����N���X�ł��B
// 
class WindowStringConverter
{
private:

	static errno_t err;			// �G���[�R�[�h

public:

	// 
	// ����������C�h������ɕϊ����܂��B
	// w_str �����̔z��̐��� str �����̕������ȏ�̐���p�ӂ��Ă��������B
	// 
	// @param str   - �ϊ��Ώۂ̕����z��
	// @param w_str - �i�[��̃��C�h�����z��
	// 
	static void Convert(LPCCH str, PWCHAR w_str, UINT length);

	// 
	// ���C�h������𕶎���ɕϊ����܂��B
	// str �����̔z��̐��� w_str �����̕������ȏ�̐���p�ӂ��Ă��������B
	// 
	// @param w_str - �ϊ��Ώۂ̃��C�h�����z��
	// @param str   - �i�[��̕����z��
	// 
	static void Convert(LPCWCH w_str, PCHAR str, UINT length);

	// 
	// ����������C�h������ɕϊ��������ʂ�Ԃ��܂��B
	// 
	// @param str - �ϊ��Ώۂ̕����z��
	// @return      �ϊ���̃��C�h������
	// 
	static std::shared_ptr<WCHAR> GetConvertString(LPCCH str);

	// 
	// ���C�h������𕶎���ɕϊ��������ʂ�Ԃ��܂��B
	// 
	// @param w_str - �ϊ��Ώۂ̃��C�h������
	// @return      - �ϊ���̕�����
	// 
	static std::shared_ptr<CHAR> GetConvertString(LPCWCH w_str);

public:

	// 
	// �N���X���ŏ��������ۂɋN�����G���[�R�[�h��Ԃ��܂��B
	// 
	static errno_t GetErrorNumber(void);

};

} // namespace dream

#endif // _WIN32

#endif // __NM_CONVERTER_H__
