
#include "../device.h"
#include "../application.h"

#ifdef NM_USE_DIRECTX

namespace dream
{

DirectDevice::DirectDevice(std::shared_ptr<WindowScreen> screen) : 
	Device(screen)
{
	this->DefDeviceParameter(this->params);
}

DirectDevice::~DirectDevice(void)
{
	this->Release();
}

void DirectDevice::DefDeviceParameter(D3DPRESENT_PARAMETERS& params)
{
	::ZeroMemory(&params, sizeof(params));
	params.BackBufferWidth = GetScreen()->GetScreenWidth();
	params.BackBufferHeight = GetScreen()->GetScreenHeight();
	params.Windowed = TRUE;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;
}

void DirectDevice::Setup(void)
{
	// DirextX���擾
	this->directx = Direct3DCreate9(D3D_SDK_VERSION);

	// �f�o�C�X�̎擾
	this->directx->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		((WindowScreen*) this->GetScreen().get())->GetHandleWindow(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&this->params,
		&this->device);
}

void DirectDevice::Draw(PApplication app)
{

	// �`�ʂ��J�n
	// �f�o�C�X�����N���A
	this->device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(50, 100, 255),
		1.0f, 
		0);

	// �]����������悤�ɖ���
	if (this->device->BeginScene())
	{

		// �A�v���P�[�V�����̕`�ʏ�����
		app->Draw(*this);

		// �`�ʂ��I��
		this->device->EndScene();

	}

	// �]������ׂ̏��𑗐M
	this->device->Present(NULL, NULL, NULL, NULL);

}

void DirectDevice::Release(void)
{
	// �f�o�C�X���J��
	if (this->device != nullptr)
	{
		this->device->Release();
		this->device = nullptr;
	}

	// DirectX�{�̂��J��
	if (this->directx != nullptr)
	{
		this->directx->Release();
		this->directx = nullptr;
	}
}

void DirectDevice::DrawPrimitive(CRPrimitive primitive)
{

	// �f�o�C�X�ɓ]������ׂ̍\���̏����m��
	LPD3DXVERTEX dx_vtx = new D3DXVERTEX[primitive.GetMaxVertexSize()];

	// ���_���̕ϊ�
	for (uint i = 0; i < primitive.GetMaxVertexSize(); i++)
	{
		this->ConvertD3DVertex(&dx_vtx[i], primitive.GetVertexs()[i]);
	}

	// D3DXVERTEX�̍\���̂ɍ��킹��
	this->device->SetFVF(
		D3DFVF_XYZ | 
		D3DFVF_NORMAL | 
		D3DFVF_DIFFUSE | 
		D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 | D3DFVF_TEX4 | D3DFVF_TEX5);

	// �e�N�X�`���X�e�[�W�̔z�u
	for (uint i = 0; i < 5; i++)
	{
		LPDIRECT3DTEXTURE9 tex = this->GetTexture(i, primitive);
		
		if (tex != nullptr)
		{
			this->device->SetTexture(i, tex);
		}
	}

	// ���_�����f�o�C�X�֓]��
	this->device->DrawPrimitiveUP(
		this->ConvertD3DPrimitiveType(primitive.GetType()),
		primitive.GetCount(),
		dx_vtx,
		sizeof(D3DXVERTEX));

	// �]�����I������̂ō\���̏����J��
	delete[] dx_vtx;
}

void DirectDevice::DrawPrimitiveIndexed(CRPrimitiveIndexed primitive)
{

	// �f�o�C�X�ɓ]������ׂ̍\���̏����m��
	LPD3DXVERTEX dx_vtx = new D3DXVERTEX[primitive.GetMaxVertexSize()];
	DWORD * indexes = new DWORD[primitive.GetIndexSize()];

	// ���_���̕ϊ�
	for (uint i = 0; i < primitive.GetMaxVertexSize(); i++)
	{
		this->ConvertD3DVertex(&dx_vtx[i], primitive.GetVertexs()[i]);
	}

	// �C���f�b�N�X�z��̕ϊ�
	for (uint i = 0; i < primitive.GetIndexSize(); i++)
	{
		indexes[i] = primitive.GetIndex(i);
	}

	// D3DXVERTEX�̍\���̂ɍ��킹��
	this->device->SetFVF(
		D3DFVF_XYZ |
		D3DFVF_NORMAL |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 | D3DFVF_TEX4 | D3DFVF_TEX5);

	// �e�N�X�`���X�e�[�W�̐ݒ�
	for (uint i = 0; i < 5; i++)
	{
		this->device->SetTexture(i, this->GetTexture(i, primitive));
	}

	// ���_�����f�o�C�X�֓]��
	this->device->DrawIndexedPrimitiveUP(
		this->ConvertD3DPrimitiveType(primitive.GetType()),
		0,
		primitive.GetMaxVertexSize(),
		primitive.GetCount(),
		indexes,
		D3DFORMAT::D3DFMT_INDEX32,
		dx_vtx,
		sizeof(D3DXVERTEX));
	
	// �]�����I������̂ō\���̏����J��
	delete[] indexes;
	delete[] dx_vtx;
}

void DirectDevice::UpdateProjection(CRProjection projection)
{
	D3DXMATRIX mxProj;

	switch (projection.type)
	{

	// �p�[�X�y�N�e�B�u�ϊ�
	case ProjectionType::Perspective:
	{
		D3DXMatrixPerspectiveLH(&mxProj,
			projection.width, projection.height,
			projection.zn, projection.zf);
	}
	break;

	// �I���\�ϊ�
	case ProjectionType::Ortho:
	{
		D3DXMatrixOrthoLH(&mxProj,
			projection.width, projection.height,
			projection.zn, projection.zf);
	}
	break;

	}

	// �v���W�F�N�V�����p�C�v���C����ݒ�
	this->device->SetTransform(D3DTS_PROJECTION, &mxProj);
}

void DirectDevice::UpdateCamera(CRCamera camera)
{
	D3DXMATRIX mxView;
	D3DXVECTOR3 eye, at, up;

	// �ʒu����ϊ�
	ConvertD3DVector3(&eye, camera.pos);
	ConvertD3DVector3(&at, camera.target);
	ConvertD3DVector3(&up, camera.up);

	// DirectX�̕⏕�֐����g���Đ���
	::D3DXMatrixLookAtLH(&mxView, &eye, &at, &up);

	// �r���[�C���O�p�C�v���C����ݒ�
	this->device->SetTransform(D3DTS_VIEW, &mxView);
}

void DirectDevice::SetLight(int index, CRLight light)
{

	// ���C�g�����f�o�C�X�p�ɕϊ�
	D3DLIGHT9 dlight = this->ConvertD3DLight(light);

	// ���C�g����]��
	this->device->SetLight(index, &dlight);

}

void DirectDevice::UpdateLight(int index)
{

	// ���ɓ_������Ă��邩�𔻒肵�ăX�C�b�`�`���Ő؂�ւ�
	BOOL enable = TRUE;
	this->device->GetLightEnable(index, &enable);
	this->device->LightEnable(index, !enable);

}

void DirectDevice::EnableRenderState(RenderType type)
{
	switch (type)
	{

	case dream::RenderType::Lighting:
	{
		this->device->SetRenderState(
			D3DRENDERSTATETYPE::D3DRS_LIGHTING, TRUE);
	}
	break;

	}
}

void DirectDevice::DisableRenderState(RenderType type)
{
	switch (type)
	{

	case dream::RenderType::Lighting:
	{
		this->device->SetRenderState(
			D3DRENDERSTATETYPE::D3DRS_LIGHTING, FALSE);
	}
	break;

	}
}

std::shared_ptr<Texture> DirectDevice::LoadTextureFile(const char* src)
{
	LPDIRECT3DTEXTURE9 tex;

	D3DXCreateTextureFromFile(this->device, WindowStringConverter::GetConvertString(src).get(), &tex);

	auto dtex = std::shared_ptr<DirectTexture>(new DirectTexture(tex));

	this->GetFileTextureManager().RegisterTexture(src, dtex);

	return dtex;
}

LPD3DXVECTOR3 DirectDevice::ConvertD3DVector3(LPD3DXVECTOR3 vec, CRVector vector)
{
	vec->x = vector.GetX();
	vec->y = vector.GetY();
	vec->z = vector.GetZ();

	return vec;
}

DirectDevice::LPD3DXVERTEX DirectDevice::ConvertD3DVertex(
	DirectDevice::LPD3DXVERTEX vtx, CRVertex vt)
{

	// ���_�ʒu����ϊ�
	vtx->x = vt.pos.GetX();
	vtx->y = vt.pos.GetY();
	vtx->z = vt.pos.GetZ();

	// ���_�@���x�N�g������ϊ�
	vtx->nx = vt.normal.GetX();
	vtx->ny = vt.normal.GetY();
	vtx->nz = vt.normal.GetZ();

	// ���_�J���[����ϊ�
	vtx->color = D3DCOLOR_ARGB(vt.color.alpha, vt.color.red, vt.color.green, vt.color.blue);

	// ���_�e�N�X�`���}�b�v����ϊ�
	vtx->tu0 = vt.tex_tu[0];
	vtx->tv0 = vt.tex_tv[0];
	vtx->tu1 = vt.tex_tu[1];
	vtx->tv1 = vt.tex_tv[1];
	vtx->tu2 = vt.tex_tu[2];
	vtx->tv2 = vt.tex_tv[2];
	vtx->tu3 = vt.tex_tu[3];
	vtx->tv3 = vt.tex_tv[3];
	vtx->tu4 = vt.tex_tu[4];
	vtx->tv4 = vt.tex_tv[4];

	// �ϊ����I������A�h���X��ԋp
	return vtx;
}

D3DPRIMITIVETYPE DirectDevice::ConvertD3DPrimitiveType(PrimitiveType type)
{
	switch (type)
	{
	
	case dream::PrimitiveType::POINTS:
	{
		return D3DPRIMITIVETYPE::D3DPT_POINTLIST;
	}

	case dream::PrimitiveType::LINES:
	{
		return D3DPRIMITIVETYPE::D3DPT_LINELIST;
	}

	case dream::PrimitiveType::LINE_STRIP:
	{
		return D3DPRIMITIVETYPE::D3DPT_LINESTRIP;
	}

	case dream::PrimitiveType::TRIANGLE_FAN:
	{
		return D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN;
	}

	case dream::PrimitiveType::TRIANGLE_LIST:
	{
		return D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;
	}

	case dream::PrimitiveType::TRIANGLE_STRIP:
	{
		return D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP;
	}

	default:
	{
		return D3DPRIMITIVETYPE::D3DPT_POINTLIST;
	}

	}
}

D3DLIGHT9 DirectDevice::ConvertD3DLight(CRLight light)
{
	D3DLIGHT9 result = D3DLIGHT9();

	result.Type = this->ConvertD3DLightType(light.type);

	// �Ɩ��̐F��ϊ�
	result.Diffuse.r = light.diffuse.red;
	result.Diffuse.g = light.diffuse.green;
	result.Diffuse.b = light.diffuse.blue;
	result.Diffuse.a = light.diffuse.alpha;

	result.Specular.r = light.specular.red;
	result.Specular.g = light.specular.green;
	result.Specular.b = light.specular.blue;
	result.Specular.a = light.specular.alpha;

	result.Ambient.r = light.ambient.red;
	result.Ambient.g = light.ambient.green;
	result.Ambient.b = light.ambient.blue;
	result.Ambient.a = light.ambient.alpha;

	// ���C�g�̈ʒu��ϊ�
	result.Position.x = light.pos.GetX();
	result.Position.y = light.pos.GetY();
	result.Position.z = light.pos.GetZ();

	// ���C�g�̏Ǝː�ʒu��ϊ�
	result.Direction.x = light.direction.GetX();
	result.Direction.x = light.direction.GetY();
	result.Direction.x = light.direction.GetZ();

	return result;
}

D3DLIGHTTYPE DirectDevice::ConvertD3DLightType(LightType type)
{

	// ���C�g�̎�ނ�ϊ�
	switch (type)
	{

	case dream::LightType::Point:
	{
		return D3DLIGHTTYPE::D3DLIGHT_POINT;
	}

	case dream::LightType::Spot:
	{
		return D3DLIGHTTYPE::D3DLIGHT_SPOT;
	}

	case dream::LightType::Directional:
	default:
	{
		return D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
	}
	break;

	}
}

LPDIRECT3DTEXTURE9 DirectDevice::GetTexture(uint stage_num, CRPrimitive primitive)
{

	// �e�N�X�`���X�e�[�W�͈͓̔������`�F�b�N
	if (stage_num > 5)
	{
		return nullptr;
	}

	// �v���~�e�B�u�Ɋi�[���ꂽ�e�N�X�`�����擾
	PTexture tex = primitive.GetTexture(stage_num);

	// �e�N�X�`�����i�[����Ă��邩���`�F�b�N
	if (tex == nullptr)
	{
		return nullptr;
	}

	// �e�N�X�`�������̃f�o�C�X�N���X�ɑΉ�����`�������`�F�b�N
	if (dynamic_cast<PDirectTexture>(tex) == nullptr)
	{
		return nullptr;
	}

	return ((PDirectTexture) tex)->GetDirectTexture();
}

} // namespace dream

#endif // NM_USE_DIRECTX
