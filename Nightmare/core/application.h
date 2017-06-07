
#ifndef __NM_APPLICATION_H__
#define __NM_APPLICATION_H__

#include "input.h"
#include "device.h"
#include "types.h"
#include "project.h"

namespace dream
{

// 
// アプリケーションを表す抽象クラスです。
// ゲーム動作に関わるメイン処理を実装する場合このクラスを継承してください。
// 
class Application abstract
{
protected:

	// メモリ管理元のクラス
	std::shared_ptr<ApplicationManager> application_manager;

private:

	// アプリケーション固有のID
	std::string app_id;

	// 終了状態になったのをメモリ管理元に渡す処理
	bool exit;

public:

	explicit Application(std::shared_ptr<ApplicationManager> manager, const char* id);
	virtual ~Application(void);

public:

	// 
	// セットアップを行います。
	// Init関数とは異なり一度のみの実行に抑えたい場合はこちら
	// 
	virtual void Setup(void) = 0 {}

	// 
	// 初期化を行う関数
	// 
	virtual void Init(void) = 0 {}

	// 
	// 更新を行う関数
	// 
	virtual void Update(void) = 0 {}

	// 
	// 描写を行う関数
	// 
	virtual void Draw(RDevice device) = 0 {}

	// 
	// 開放を行う処理
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// このアプリケーションのアプリケーションマネージャーを呼び出します。
	// 
	PApplicationManager GetApplicationManager(void);

	// 
	// アプリケーションが終了状態になっているかを判定します。
	// 
	bool IsExit(void) const;

	// 
	// アプリケーション固有のIDを返します。
	// 
	std::string GetID(void) const
	{
		return this->app_id;
	}

};

// 
// アプリケーションの管理を行うクラスです。
// 
class ApplicationManager
{
private:

	// 動作させるアプリケーション
	std::shared_ptr<Application> current_app;

	// Manager Clases.
	std::shared_ptr<Screen> screen;
	std::shared_ptr<Device> device;
	std::shared_ptr<InputDevice> input;

public:

	// 
	// アプリケーションマネージャーの生成を行います。
	// 
	explicit ApplicationManager(void);
	virtual ~ApplicationManager(void);

public:

	// 
	// 管理をするアプリケーションクラスを登録します。
	// 
	void RegisterApplication(std::shared_ptr<Application> app)
	{
		this->current_app = app;
	}

	// 
	// 管理しているアプリケーションクラスを解除します。
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
	// セットアップ処理
	// 
	void Setup(void);

	// 
	// 実行処理
	// 
	void Run(void);

	// 
	// 開放処理
	// 
	void Release(void);

public:

	// 
	// アプリケーションを取得します。
	// 
	PApplication GetApplication(void);

	PDevice GetDevice(void)
	{
		return this->device.get();
	}

};

} // namespace dream

#endif // __NM_APPLICATION_H__
