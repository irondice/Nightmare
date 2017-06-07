
#ifndef __NM_PROJECT_H__
#define __NM_PROJECT_H__



// ======================================================================
// 
// ライブラリ依存のヘッダー展開
// 
// ======================================================================



#define NM_USE_DIRECTX
#define NM_USE_OPENGL



#ifdef _WIN32

// 実装先のライブラリ
#include <windows.h>
#undef max
#undef min

#endif // _WIN32



#ifdef NM_USE_DIRECTX

// レンダリング関連のライブラリ
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

// 入力関連のライブラリ
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// サウンド関連のライブラリ
#include <XAudio2.h>

#endif // __NM_USE_DIRECTX__



#ifdef NM_USE_OPENGL

// レンダリング関連のライブラリ
#include <gl\GL.h>

// 入力関連のライブラリ
#include <gl\GLU.h>

#endif // NM_USE_OPENGL



// C++/STD ライブラリ
#include <memory>
#include <unordered_map>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <limits>
#include <thread>
#include <algorithm>



// ======================================================================
// 
// ライブラリで使用する定義
// 
// ======================================================================

#define NM_SAFE_DELETE(_ptr)			delete _ptr; _ptr			= nullptr;
#define NM_RETURN_THIS					return *this



// ======================================================================
// 
// Nightmareで定義される名前空間の前方宣言
// 
// ======================================================================

namespace dream
{

// ==================================================================================================== // 
// Utils関連のクラス前方宣言
// ==================================================================================================== // 

class Vector;
using PVector = Vector *;
using RVector = Vector &;
using CVector = const Vector;
using CPVector = const PVector;
using CRVector = const RVector;



// ==================================================================================================== // 
// Application関連のクラス前方宣言
// ==================================================================================================== // 

class Application;
using PApplication = Application *;
using RApplication = Application &;
using CApplication = const Application;
using CPApplication = const PApplication;
using CRApplication = const RApplication;

class ApplicationManager;
using PApplicationManager = ApplicationManager *;
using RApplicationManager = ApplicationManager &;
using CApplicationManager = const ApplicationManager;
using CPApplicationManager = const PApplicationManager;
using CRApplicationManager = const RApplicationManager;



// ==================================================================================================== // 
// Input関連のクラス前方宣言
// ==================================================================================================== // 

class Input;
using PInput = Input *;
using RInput = Input &;
using CInput = const Input;
using CPInput = const PInput;
using CRInput = const RInput;

class InputDevice;
using PInputDevice = InputDevice *;
using RInputDevice = InputDevice &;
using CInputDevice = const InputDevice;
using CPInputDevice = const PInputDevice;
using CRInputDevice = const RInputDevice;

#ifdef NM_USE_DIRECTX

class DirectInputDevice;
using PDirectInputDevice = DirectInputDevice *;
using RDirectInputDevice = DirectInputDevice &;
using CDirectInputDevice = const DirectInputDevice;
using CPDirectInputDevice = const PDirectInputDevice;
using CRDirectInputDevice = const RDirectInputDevice;

#endif // NM_USE_DIRECTX

// ==================================================================================================== // 
// Device関連のクラス前方宣言
// ==================================================================================================== // 

class Screen;
using PScreen = Screen *;
using RScreen = Screen &;
using CScreen = const Screen;
using CPScreen = const PScreen;
using CRScreen = const RScreen;

#ifdef _WIN32

class WindowScreen;
using PWindowScreen = WindowScreen *;
using RWindowScreen = WindowScreen &;
using CWindowScreen = const WindowScreen;
using CPWindowScreen = const PWindowScreen;
using CRWindowScreen = const RWindowScreen;

#endif // _WIN32

class Device;
using PDevice = Device *;
using RDevice = Device &;
using CDevice = const Device;
using CPDevice = const PDevice;
using CRDevice = const RDevice;

#ifdef NM_USE_DIRECTX

class DirectDevice;
using PDirectDevice = DirectDevice *;
using RDirectDevice = DirectDevice &;
using CDirectDevice = const DirectDevice;
using CPDirectDevice = const PDirectDevice;
using CRDirectDevice = const RDirectDevice;

#endif // NM_USE_DIRECTX

#ifdef NM_USE_OPENGL

class OpenDevice;
using POpenDevice = OpenDevice *;
using ROpenDevice = OpenDevice &;
using COpenDevice = const OpenDevice;
using CPOpenDevice = const POpenDevice;
using CROpenDevice = const ROpenDevice;

#endif // NM_USE_OPENGL

struct Color;
using PColor = Color *;
using RColor = Color &;
using CColor = const Color;
using CPColor = const PColor;
using CRColor = const RColor;

struct Vertex;
using PVertex = Vertex *;
using RVertex = Vertex &;
using CVertex = const Vertex;
using CPVertex = const PVertex;
using CRVertex = const RVertex;

enum struct PrimitiveType;

class Primitive;
using PPrimitive = Primitive *;
using RPrimitive = Primitive &;
using CPrimitive = const Primitive;
using CPPrimitive = const PPrimitive;
using CRPrimitive = const RPrimitive;

class PrimitiveIndexed;
using PPrimitiveIndexed = PrimitiveIndexed *;
using RPrimitiveIndexed = PrimitiveIndexed &;
using CPrimitiveIndexed = const PrimitiveIndexed;
using CPPrimitiveIndexed = const PPrimitiveIndexed;
using CRPrimitiveIndexed = const RPrimitiveIndexed;

struct Camera;
using PCamera = Camera *;
using RCamera = Camera &;
using CCamera = const Camera;
using CPCamera = const PCamera;
using CRCamera = const RCamera;

struct Projection;
using PProjection = Projection *;
using RProjection = Projection &;
using CProjection = const Projection;
using CPProjection = const PProjection;
using CRProjection = const RProjection;

struct Light;
using PLight = Light *;
using RLight = Light &;
using CLight = const Light;
using CPLight = const PLight;
using CRLight = const RLight;

class Texture;
using PTexture = Texture *;
using RTexture = Texture &;
using CTexture = const Texture;
using CPTexture = const PTexture;
using CRTexture = const RTexture;

#ifdef NM_USE_DIRECTX

class DirectTexture;
using PDirectTexture = DirectTexture *;
using RDirectTexture = DirectTexture &;
using CDirectTexture = const DirectTexture;
using CPDirectTexture = const PDirectTexture;
using CRDirectTexture = const RDirectTexture;

#endif // NM_USE_DIRECTX

class TextureManager;
using PTextureManager = TextureManager *;
using RTextureManager = TextureManager &;
using CTextureManager = const TextureManager;
using CPTextureManager = const PTextureManager;
using CRTextureManager = const RTextureManager;



// ==================================================================================================== // 
// Sound関連のクラス前方宣言
// ==================================================================================================== // 

class Sound;
using PSound = Sound *;
using RSound = Sound &;
using CSound = const Sound;
using CPSound = const PSound;
using CRSound = const RSound;

class SoundManager;
using PSoundManager = SoundManager *;
using RSoundManager = SoundManager &;
using CSoundManager = const SoundManager;
using CPSoundManager = const PSoundManager;
using CRSoundManager = const RSoundManager;



}

#endif // __NM_PROJECT_H__
