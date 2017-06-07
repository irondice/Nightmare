
#include "application.h"
#include "debug.h"

namespace dream
{

ApplicationManager::ApplicationManager(void)
{
	this->current_app = nullptr;
}

ApplicationManager::~ApplicationManager(void)
{
	this->Release();
}

void ApplicationManager::UnRegisterApplication(void)
{

	// �A�v���P�[�V�����̊J������
	current_app->Release();

	// �Q�Ə����폜
	current_app = nullptr;

}

void ApplicationManager::Setup(void)
{
	
	// �X�N���[�����̃Z�b�g�A�b�v
	if (this->screen != nullptr)
	{
		this->screen->Setup();
		Debug::Log("Screen Enabled.");
	}

	// �f�o�C�X���̃Z�b�g�A�b�v
	if (this->device != nullptr)
	{
		this->device->Setup();
		Debug::Log("GraphicDevice Enabled.");
	}

	// ���̓f�o�C�X�̃Z�b�g�A�b�v
	if (this->input != nullptr)
	{
		this->input->Setup();
		Input::SetInputDevice(this->input.get());
		Debug::Log("InputDevice Enabled.");
	}

}

void ApplicationManager::Run(void)
{

	// ���삳����A�v���P�[�V�����������ꍇ�͏����������I�������܂��B
	if (this->current_app != nullptr)
	{

		// ���삳����A�v���P�[�V�����̃Z�b�g�A�b�v����
		this->current_app->Setup();

		// ���삳����A�v���P�[�V�����̏���������
		this->current_app->Init();

		// �A�v���P�[�V�������[�v
		while (true)
		{

			ScreenResult result = this->screen->Update();
			
			if (result == ScreenResult::Exit)
			{
				return;
			}

			if (result == ScreenResult::Run)
			{

				// �A�v���P�[�V�������I����ԂɂȂ��Ă����ꍇ
				// �܂��̓A�v���P�[�V������񂪓o�^�𖕏����ꂽ�ꍇ
				// �A�v���P�[�V�������[�v���甲���o���܂��B
				if (this->current_app == nullptr || this->current_app->IsExit())
				{
					break;
				}

				// ���̓f�o�C�X�̍X�V
				if (this->input != nullptr)
				{
					this->input->Update();
				}

				// �A�v���P�[�V�����̓���
				this->current_app->Update();

				// �A�v���P�[�V�����̕`��
				if (this->device != nullptr)
				{
					this->device->Draw(this->current_app.get());
				}

			}

		}

		// ���쒆�̃A�v���P�[�V�������̊J�������܂��B
		this->current_app->Release();

	}

}

void ApplicationManager::Release(void)
{

	if (this->input != nullptr)
	{

		// ���̓f�o�C�X�����J�����܂��B
		this->input->Release();

		// ���̓f�o�C�X���̃��������
		this->input.reset();

	}

	if (this->device != nullptr)
	{

		// �f�o�C�X���̊J�������܂��B
		this->device->Release();

		// �f�o�C�X���̃������J��
		this->device.reset();

	}

	if (this->screen != nullptr)
	{

		// �X�N���[�����̊J�������܂��B
		this->screen->Release();

		// �X�N���[�����̃��������
		this->screen.reset();

	}

}

PApplication ApplicationManager::GetApplication(void)
{
	return this->current_app.get();
}

} // namespace dream
