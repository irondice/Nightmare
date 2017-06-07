
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
// �f�B�X�v���C�ɕ\������X�N���[���̏�����\���܂��B
// 
class Screen abstract
{
protected:

	// �X�N���[���̃^�C�g����
	std::string title;

	// �X�N���[���̃T�C�Y (�s�N�Z���P��)
	uint screen_width;
	uint screen_height;

public:

	// 
	// �X�N���[�����𐶐����܂��B
	// 
	explicit Screen(void);

	virtual ~Screen(void);

public:

	// 
	// �X�N���[���̃^�C�g����ݒ肵�܂��B
	// 
	virtual void SetScreenTitle(const char* title) {}

	// 
	// �X�N���[���̃T�C�Y��ݒ肵�܂��B
	// 
	void SetScreenSize(uint width, uint height)
	{
		this->screen_width = width;
		this->screen_height = height;
	}

public:

	// 
	// �X�N���[�����̃Z�b�g�A�b�v�����܂��B
	// 
	virtual void Setup(void) = 0 {}

	// 
	// �X�N���[�����̍X�V�����܂��B
	// 
	virtual ScreenResult Update(void) = 0 {}

	// 
	// �X�N���[�����̊J�������܂��B
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// �X�N���[���̕\���̗L����ݒ肵�܂��B
	// 
	virtual void ShowScreen(bool enable) {}

public:

	// 
	// �X�N���[���ɐݒ肳��Ă���^�C�g������Ԃ��܂��B
	// 
	std::string GetScreenTitle(const char* title) const
	{
		return this->title;
	}

	// 
	// �X�N���[���̉����T�C�Y��Ԃ��܂��B
	// 
	unsigned int GetScreenWidth(void) const
	{
		return this->screen_width;
	}

	// 
	// �X�N���[���̏c���T�C�Y��Ԃ��܂��B
	// 
	unsigned int GetScreenHeight(void) const
	{
		return this->screen_height;
	}

};

// 
// 3D�`�ʂ��T�|�[�g����f�o�C�X������\���܂��B
// 
class Device abstract
{
private:

	// �`�ʂ���X�N���[�����
	std::shared_ptr<Screen> screen;

	// �t�@�C���e�N�X�`���Ǘ��N���X
	TextureManager file_tex_manager;

public:

	// �`�ʂ���X�N���[������ݒ肵�Đ���
	explicit Device(std::shared_ptr<Screen> screen);
	virtual ~Device(void);

public:

	// 
	// �f�o�C�X���Z�b�g�A�b�v���܂�
	// 
	virtual void Setup(void) = 0 {}

	// 
	// �f�o�C�X�̕`�ʂ��J�n���܂��B
	// params:
	//   app - �`�ʂ���A�v���P�[�V����
	// 
	virtual void Draw(PApplication app) = 0 {}

	// 
	// �f�o�C�X�̏����J�����܂��B
	// 
	virtual void Release(void) = 0 {}

public:

	// 
	// �v���~�e�B�u��`�ʂ��܂��B
	// 
	virtual void DrawPrimitive(CRPrimitive primitive) = 0 {}

	// 
	// �C���f�b�N�X�o�b�t�@�t���̃v���~�e�B�u��`�ʂ��܂��B
	// 
	virtual void DrawPrimitiveIndexed(CRPrimitiveIndexed primitive) = 0 {}
	
	// 
	// �v���W�F�N�V�����̍X�V�����܂��B
	// 
	virtual void UpdateProjection(CRProjection projection) = 0 {}

	// 
	// �J�������̍X�V�����܂��B
	// 
	virtual void UpdateCamera(CRCamera camera) = 0 {}

	// 
	// ���C�g����ݒ肵�܂��B
	// 
	virtual void SetLight(int index, CRLight light) = 0 {}

	// 
	// ���C�g�����X�V���܂��B
	// 
	virtual void UpdateLight(int index) = 0 {}

	// 
	// �����_�����O�ݒ��L�������܂��B
	// 
	virtual void EnableRenderState(RenderType type) = 0 {}

	// 
	// �����_�����O�ݒ�𖳌������܂��B
	// 
	virtual void DisableRenderState(RenderType type) = 0 {}

	// 
	// �e�N�X�`����ǂݍ��݂܂��B
	// �ǂݍ��񂾃e�N�X�`���͕Ԃ��l�ȊO�� GetFileTextureManager(src) ����ł��擾�o���܂��B
	// 
	virtual std::shared_ptr<Texture> LoadTextureFile(const char* src) = 0 {}

public:

	// 
	// �X�N���[�������擾���܂��B
	// 
	std::shared_ptr<Screen> GetScreen(void)
	{
		return this->screen;
	}

	// 
	// DirectDevice::LoadTextureFile(const char* src) �œǂݍ��񂾃e�N�X�`�������Ǘ��N���X��Ԃ��܂��B
	// �ǂݍ��񂾃e�N�X�`���t�@�C���Ή�����ID�� LoadTextureFile()�֐��� src���� �ł��B
	// 
	RTextureManager GetFileTextureManager(void)
	{
		return this->file_tex_manager;
	}

};

// ==================================================================================================== // 
// 
// Windows���̎���
// 
// ==================================================================================================== // 

// 
// Windows���ɂ��X�N���[��������s���N���X
// 
class WindowScreen final : public Screen
{
private:

	HINSTANCE hInstance;
	WNDCLASSEX wcex;
	HWND hwnd;

public:

	// 
	// �X�N���[���𐶐����܂��B
	// params:
	//   hInstance - Windows���ɂ��A�v���P�[�V�����̃n���h���C���X�^���X
	// 
	explicit WindowScreen(HINSTANCE hInstance);

	~WindowScreen(void) {}

private:

	// 
	// �E�B���h�E�N���X�̃f�t�H���g�ݒ�
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
// DirectX���̎���
// 
// ==================================================================================================== // 

class DirectDevice final : public Device
{
private:

	// 
	// DirectX�p�̃������\����
	// �e�N�X�`���X�e�[�W��5�ɌŒ�
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
	// �x�N�g������ϊ����܂��B
	// 
	LPD3DXVECTOR3 ConvertD3DVector3(LPD3DXVECTOR3 vec, CRVector vector);

	// 
	// ���_����DX�����ɕϊ����܂��B
	// 
	LPD3DXVERTEX ConvertD3DVertex(LPD3DXVERTEX vtx, CRVertex vertex);

	// 
	// �v���~�e�B�u�̎�ނ�DX�ɕϊ����܂��B
	// 
	D3DPRIMITIVETYPE ConvertD3DPrimitiveType(PrimitiveType type);

	// 
	// ���C�g����DX�����ɕϊ����܂��B
	// 
	D3DLIGHT9 ConvertD3DLight(CRLight light);

	// 
	// ���C�g�̎�ނ�DX�����ɕϊ����܂��B
	// 
	D3DLIGHTTYPE ConvertD3DLightType(LightType type);

	// 
	// �v���~�e�B�u�ɂ���e�N�X�`�������擾���܂��B
	// 
	LPDIRECT3DTEXTURE9 GetTexture(uint stage_num, CRPrimitive primitive);

public:

	// 
	// DirectX�̕`�ʃf�o�C�X���擾���܂��B
	// �����̃R�[�h���Ăяo���ꍇ�͓����ˑ��ɂȂ�וʂ̃v���b�g�t�H�[���ł̓���͂��܂���B
	// 
	LPDIRECT3DDEVICE9 GetDirectDevice(void)
	{
		return this->device;
	}

};

#endif // NM_ISE_DIRECTX

#ifdef NM_USE_OPENGL

// OpenGL�̃f�o�C�X��`

#endif // NM_USE_OPENGL

} // namespace dream

#endif // __NM_DEVICE_H__
