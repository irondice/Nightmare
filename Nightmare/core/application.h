
#ifndef __NM_APPLICATION_H__
#define __NM_APPLICATION_H__

#include "input.h"
#include "device.h"
#include "types.h"
#include "project.h"

namespace dream
{

// 
// �A�v���P�[�V������\�����ۃN���X�ł��B
// �Q�[������Ɋւ�郁�C����������������ꍇ���̃N���X���p�����Ă��������B
// 
class Application abstract
{
protected:

	// �������Ǘ����̃N���X
	std::shared_ptr<ApplicationManager> application_manager;

private:

	// �A�v���P�[�V�����ŗL��ID
	std::string app_id;

	// �I����ԂɂȂ����̂��������Ǘ����ɓn������
	bool exit;

public:

	explicit Application(std::shared_ptr<ApplicationManager> manager, const char* id);
	virtual ~Application(void);

public:

	// 
	// �Z�b�g�A�b�v���s���܂��B
	// Init�֐��Ƃ͈قȂ��x�݂̂̎��s�ɗ}�������ꍇ�͂�����
	// 
	virtual void Setup(void) = 0 {}

	// 
	// ���������s���֐�
	// 
	virtual void Init(void) = 0 {}

	// 
	// �X�V���s���֐�
	// 
	virtual void Update(void) = 0 {}

	// 
	// �`�ʂ��s���֐�
	// 
	virtual void Draw(RDevice device) = 0 {}

	// 
	// �J�����s������
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// ���̃A�v���P�[�V�����̃A�v���P�[�V�����}�l�[�W���[���Ăяo���܂��B
	// 
	PApplicationManager GetApplicationManager(void);

	// 
	// �A�v���P�[�V�������I����ԂɂȂ��Ă��邩�𔻒肵�܂��B
	// 
	bool IsExit(void) const;

	// 
	// �A�v���P�[�V�����ŗL��ID��Ԃ��܂��B
	// 
	std::string GetID(void) const
	{
		return this->app_id;
	}

};

// 
// �A�v���P�[�V�����̊Ǘ����s���N���X�ł��B
// 
class ApplicationManager
{
private:

	// ���삳����A�v���P�[�V����
	std::shared_ptr<Application> current_app;

	// Manager Clases.
	std::shared_ptr<Screen> screen;
	std::shared_ptr<Device> device;
	std::shared_ptr<InputDevice> input;

public:

	// 
	// �A�v���P�[�V�����}�l�[�W���[�̐������s���܂��B
	// 
	explicit ApplicationManager(void);
	virtual ~ApplicationManager(void);

public:

	// 
	// �Ǘ�������A�v���P�[�V�����N���X��o�^���܂��B
	// 
	void RegisterApplication(std::shared_ptr<Application> app)
	{
		this->current_app = app;
	}

	// 
	// �Ǘ����Ă���A�v���P�[�V�����N���X���������܂��B
	// 
	void UnRegisterApplication(void);

	void SetScreen(std::shared_ptr<Screen> screen)
	{
		this->screen = screen;
	}

	void SetDevice(std::shared_ptr<Device> device)
	{
		this->device = device;
	}

	void SetInputDevice(std::shared_ptr<InputDevice> input)
	{
		this->input = input;
	}

public:

	// 
	// �Z�b�g�A�b�v����
	// 
	void Setup(void);

	// 
	// ���s����
	// 
	void Run(void);

	// 
	// �J������
	// 
	void Release(void);

public:

	// 
	// �A�v���P�[�V�������擾���܂��B
	// 
	PApplication GetApplication(void);

	PDevice GetDevice(void)
	{
		return this->device.get();
	}

};

} // namespace dream

#endif // __NM_APPLICATION_H__
