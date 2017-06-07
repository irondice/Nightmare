
#ifndef __NM_DEVICE_H__
#define __NM_DEVICE_H__

#include "texture.h"
#include "render.h"
#include "primitive.h"
#include "camera.h"
#include "converter.h"
#include "project.h"

namespace dream
{

enum class ScreenResult
{
	Run,
	Wait,
	Exit,
};

// 
// ディスプレイに表示するスクリーンの処理を表します。
// 
class Screen abstract
{
protected:

	// スクリーンのタイトル名
	std::string title;

	// スクリーンのサイズ (ピクセル単位)
	uint screen_width;
	uint screen_height;

public:

	// 
	// スクリーン情報を生成します。
	// 
	explicit Screen(void);

	virtual ~Screen(void);

public:

	// 
	// スクリーンのタイトルを設定します。
	// 
	virtual void SetScreenTitle(const char* title) {}

	// 
	// スクリーンのサイズを設定します。
	// 
	void SetScreenSize(uint width, uint height)
	{
		this->screen_width = width;
		this->screen_height = height;
	}

public:

	// 
	// スクリーン情報のセットアップをします。
	// 
	virtual void Setup(void) = 0 {}

	// 
	// スクリーン情報の更新をします。
	// 
	virtual ScreenResult Update(void) = 0 {}

	// 
	// スクリーン情報の開放をします。
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// スクリーンの表示の有無を設定します。
	// 
	virtual void ShowScreen(bool enable) {}

public:

	// 
	// スクリーンに設定されているタイトル名を返します。
	// 
	std::string GetScreenTitle(const char* title) const
	{
		return this->title;
	}

	// 
	// スクリーンの横幅サイズを返します。
	// 
	unsigned int GetScreenWidth(void) const
	{
		return this->screen_width;
	}

	// 
	// スクリーンの縦幅サイズを返します。
	// 
	unsigned int GetScreenHeight(void) const
	{
		return this->screen_height;
	}

};

// 
// 3D描写をサポートするデバイス処理を表します。
// 
class Device abstract
{
private:

	// 描写するスクリーン情報
	std::shared_ptr<Screen> screen;

	// ファイルテクスチャ管理クラス
	TextureManager file_tex_manager;

public:

	// 描写するスクリーン情報を設定して生成
	explicit Device(std::shared_ptr<Screen> screen);
	virtual ~Device(void);

public:

	// 
	// デバイスをセットアップします
	// 
	virtual void Setup(void) = 0 {}

	// 
	// デバイスの描写を開始します。
	// params:
	//   app - 描写するアプリケーション
	// 
	virtual void Draw(PApplication app) = 0 {}

	// 
	// デバイスの情報を開放します。
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// プリミティブを描写します。
	// 
	virtual void DrawPrimitive(CRPrimitive primitive) = 0 {}

	// 
	// インデックスバッファ付きのプリミティブを描写します。
	// 
	virtual void DrawPrimitiveIndexed(CRPrimitiveIndexed primitive) = 0 {}
	
	// 
	// プロジェクションの更新をします。
	// 
	virtual void UpdateProjection(CRProjection projection) = 0 {}

	// 
	// カメラ情報の更新をします。
	// 
	virtual void UpdateCamera(CRCamera camera) = 0 {}

	// 
	// ライト情報を設定します。
	// 
	virtual void SetLight(int index, CRLight light) = 0 {}

	// 
	// ライト情報を更新します。
	// 
	virtual void UpdateLight(int index) = 0 {}

	// 
	// レンダリング設定を有効化します。
	// 
	virtual void EnableRenderState(RenderType type) = 0 {}

	// 
	// レンダリング設定を無効化します。
	// 
	virtual void DisableRenderState(RenderType type) = 0 {}

	// 
	// テクスチャを読み込みます。
	// 読み込んだテクスチャは返し値以外に GetFileTextureManager(src) からでも取得出来ます。
	// 
	virtual std::shared_ptr<Texture> LoadTextureFile(const char* src) = 0 {}

public:

	// 
	// スクリーン情報を取得します。
	// 
	std::shared_ptr<Screen> GetScreen(void)
	{
		return this->screen;
	}

	// 
	// DirectDevice::LoadTextureFile(const char* src) で読み込んだテクスチャ情報を管理クラスを返します。
	// 読み込んだテクスチャファイル対応するIDは LoadTextureFile()関数の src引数 です。
	// 
	RTextureManager GetFileTextureManager(void)
	{
		return this->file_tex_manager;
	}

};

// ==================================================================================================== // 
// 
// Windows側の実装
// 
// ==================================================================================================== // 

// 
// Windows側によるスクリーン制御を行うクラス
// 
class WindowScreen final : public Screen
{
private:

	HINSTANCE hInstance;
	WNDCLASSEX wcex;
	HWND hwnd;

public:

	// 
	// スクリーンを生成します。
	// params:
	//   hInstance - Windows側によるアプリケーションのハンドルインスタンス
	// 
	explicit WindowScreen(HINSTANCE hInstance);

	~WindowScreen(void) {}

private:

	// 
	// ウィンドウクラスのデフォルト設定
	// 
	void DefWindowClassEx(WNDCLASSEX& wcex);

public:

	void SetScreenTitle(const char* title) override;

public:

	void Setup(void) override;

	ScreenResult Update(void) override;

	void Release(void) override;

public:

	virtual void ShowScreen(bool enable) override;

private:

	static LRESULT CALLBACK DefWndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);

public:

	HINSTANCE GetHandleInstance(void)
	{
		return this->hInstance;
	}

	HWND GetHandleWindow(void)
	{
		return this->hwnd;
	}

};

#ifdef NM_USE_DIRECTX

// ==================================================================================================== // 
// 
// DirectX側の実装
// 
// ==================================================================================================== // 

class DirectDevice final : public Device
{
private:

	// 
	// DirectX用のメモリ構造体
	// テクスチャステージは5つに固定
	// 
	typedef struct _D3DXVERTEX
	{
		float x, y, z;
		float nx, ny, nz;
		D3DCOLOR color;
		float tu0, tv0;
		float tu1, tv1;
		float tu2, tv2;
		float tu3, tv3;
		float tu4, tv4;
	} D3DXVERTEX, * LPD3DXVERTEX;

private:

	LPDIRECT3D9 directx;
	LPDIRECT3DDEVICE9 device;
	D3DPRESENT_PARAMETERS params;

public:

	explicit DirectDevice(std::shared_ptr<WindowScreen> screen);
	~DirectDevice(void);

private:

	void DefDeviceParameter(D3DPRESENT_PARAMETERS& params);

public:

	void Setup(void) override;

	void Draw(PApplication app) override;

	void Release(void) override;

public:

	void DrawPrimitive(CRPrimitive primitive) override;

	void DrawPrimitiveIndexed(CRPrimitiveIndexed primitive) override;

	void UpdateProjection(CRProjection projection) override;

	void UpdateCamera(CRCamera camera) override;

	void SetLight(int index, CRLight light) override;

	void UpdateLight(int index) override;

	void EnableRenderState(RenderType type) override;

	void DisableRenderState(RenderType type) override;

	std::shared_ptr<Texture> LoadTextureFile(const char* src) override;

private:

	// 
	// ベクトル情報を変換します。
	// 
	LPD3DXVECTOR3 ConvertD3DVector3(LPD3DXVECTOR3 vec, CRVector vector);

	// 
	// 頂点情報をDX向けに変換します。
	// 
	LPD3DXVERTEX ConvertD3DVertex(LPD3DXVERTEX vtx, CRVertex vertex);

	// 
	// プリミティブの種類をDXに変換します。
	// 
	D3DPRIMITIVETYPE ConvertD3DPrimitiveType(PrimitiveType type);

	// 
	// ライト情報をDX向けに変換します。
	// 
	D3DLIGHT9 ConvertD3DLight(CRLight light);

	// 
	// ライトの種類をDX向けに変換します。
	// 
	D3DLIGHTTYPE ConvertD3DLightType(LightType type);

	// 
	// プリミティブにあるテクスチャ情報を取得します。
	// 
	LPDIRECT3DTEXTURE9 GetTexture(uint stage_num, CRPrimitive primitive);

public:

	// 
	// DirectXの描写デバイスを取得します。
	// ※このコードを呼び出す場合は内部依存になる為別のプラットフォームでの動作はしません。
	// 
	LPDIRECT3DDEVICE9 GetDirectDevice(void)
	{
		return this->device;
	}

};

#endif // NM_ISE_DIRECTX

#ifdef NM_USE_OPENGL

// OpenGLのデバイス定義

#endif // NM_USE_OPENGL

} // namespace dream

#endif // __NM_DEVICE_H__
