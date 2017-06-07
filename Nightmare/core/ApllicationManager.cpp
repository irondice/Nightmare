
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

	// アプリケーションの開放処理
	current_app->Release();

	// 参照情報を削除
	current_app = nullptr;

}

void ApplicationManager::Setup(void)
{
	
	// スクリーン情報のセットアップ
	if (this->screen != nullptr)
	{
		this->screen->Setup();
		Debug::Log("Screen Enabled.");
	}

	// デバイス情報のセットアップ
	if (this->device != nullptr)
	{
		this->device->Setup();
		Debug::Log("GraphicDevice Enabled.");
	}

	// 入力デバイスのセットアップ
	if (this->input != nullptr)
	{
		this->input->Setup();
		Input::SetInputDevice(this->input.get());
		Debug::Log("InputDevice Enabled.");
	}

}

void ApplicationManager::Run(void)
{

	// 動作させるアプリケーションが無い場合は処理をせず終了させます。
	if (this->current_app != nullptr)
	{

		// 動作させるアプリケーションのセットアップ処理
		this->current_app->Setup();

		// 動作させるアプリケーションの初期化処理
		this->current_app->Init();

		// アプリケーションループ
		while (true)
		{

			ScreenResult result = this->screen->Update();
			
			if (result == ScreenResult::Exit)
			{
				return;
			}

			if (result == ScreenResult::Run)
			{

				// アプリケーションが終了状態になっていた場合
				// またはアプリケーション情報が登録を抹消された場合
				// アプリケーションループから抜け出します。
				if (this->current_app == nullptr || this->current_app->IsExit())
				{
					break;
				}

				// 入力デバイスの更新
				if (this->input != nullptr)
				{
					this->input->Update();
				}

				// アプリケーションの動作
				this->current_app->Update();

				// アプリケーションの描写
				if (this->device != nullptr)
				{
					this->device->Draw(this->current_app.get());
				}

			}

		}

		// 動作中のアプリケーション情報の開放をします。
		this->current_app->Release();

	}

}

void ApplicationManager::Release(void)
{

	if (this->input != nullptr)
	{

		// 入力デバイス情報を開放します。
		this->input->Release();

		// 入力デバイス情報のメモリ解放
		this->input.reset();

	}

	if (this->device != nullptr)
	{

		// デバイス情報の開放をします。
		this->device->Release();

		// デバイス情報のメモリ開放
		this->device.reset();

	}

	if (this->screen != nullptr)
	{

		// スクリーン情報の開放をします。
		this->screen->Release();

		// スクリーン情報のメモリ解放
		this->screen.reset();

	}

}

PApplication ApplicationManager::GetApplication(void)
{
	return this->current_app.get();
}

} // namespace dream
