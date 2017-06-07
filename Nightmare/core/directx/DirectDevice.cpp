
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
	// DirextXを取得
	this->directx = Direct3DCreate9(D3D_SDK_VERSION);

	// デバイスの取得
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

	// 描写を開始
	// デバイス情報をクリア
	this->device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(50, 100, 255),
		1.0f, 
		0);

	// 転送情報を受取るように命令
	if (this->device->BeginScene())
	{

		// アプリケーションの描写処理へ
		app->Draw(*this);

		// 描写を終了
		this->device->EndScene();

	}

	// 転送する為の情報を送信
	this->device->Present(NULL, NULL, NULL, NULL);

}

void DirectDevice::Release(void)
{
	// デバイスを開放
	if (this->device != nullptr)
	{
		this->device->Release();
		this->device = nullptr;
	}

	// DirectX本体を開放
	if (this->directx != nullptr)
	{
		this->directx->Release();
		this->directx = nullptr;
	}
}

void DirectDevice::DrawPrimitive(CRPrimitive primitive)
{

	// デバイスに転送する為の構造体情報を確保
	LPD3DXVERTEX dx_vtx = new D3DXVERTEX[primitive.GetMaxVertexSize()];

	// 頂点情報の変換
	for (uint i = 0; i < primitive.GetMaxVertexSize(); i++)
	{
		this->ConvertD3DVertex(&dx_vtx[i], primitive.GetVertexs()[i]);
	}

	// D3DXVERTEXの構造体に合わせる
	this->device->SetFVF(
		D3DFVF_XYZ | 
		D3DFVF_NORMAL | 
		D3DFVF_DIFFUSE | 
		D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 | D3DFVF_TEX4 | D3DFVF_TEX5);

	// テクスチャステージの配置
	for (uint i = 0; i < 5; i++)
	{
		LPDIRECT3DTEXTURE9 tex = this->GetTexture(i, primitive);
		
		if (tex != nullptr)
		{
			this->device->SetTexture(i, tex);
		}
	}

	// 頂点情報をデバイスへ転送
	this->device->DrawPrimitiveUP(
		this->ConvertD3DPrimitiveType(primitive.GetType()),
		primitive.GetCount(),
		dx_vtx,
		sizeof(D3DXVERTEX));

	// 転送が終わったので構造体情報を開放
	delete[] dx_vtx;
}

void DirectDevice::DrawPrimitiveIndexed(CRPrimitiveIndexed primitive)
{

	// デバイスに転送する為の構造体情報を確保
	LPD3DXVERTEX dx_vtx = new D3DXVERTEX[primitive.GetMaxVertexSize()];
	DWORD * indexes = new DWORD[primitive.GetIndexSize()];

	// 頂点情報の変換
	for (uint i = 0; i < primitive.GetMaxVertexSize(); i++)
	{
		this->ConvertD3DVertex(&dx_vtx[i], primitive.GetVertexs()[i]);
	}

	// インデックス配列の変換
	for (uint i = 0; i < primitive.GetIndexSize(); i++)
	{
		indexes[i] = primitive.GetIndex(i);
	}

	// D3DXVERTEXの構造体に合わせる
	this->device->SetFVF(
		D3DFVF_XYZ |
		D3DFVF_NORMAL |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 | D3DFVF_TEX4 | D3DFVF_TEX5);

	// テクスチャステージの設定
	for (uint i = 0; i < 5; i++)
	{
		this->device->SetTexture(i, this->GetTexture(i, primitive));
	}

	// 頂点情報をデバイスへ転送
	this->device->DrawIndexedPrimitiveUP(
		this->ConvertD3DPrimitiveType(primitive.GetType()),
		0,
		primitive.GetMaxVertexSize(),
		primitive.GetCount(),
		indexes,
		D3DFORMAT::D3DFMT_INDEX32,
		dx_vtx,
		sizeof(D3DXVERTEX));
	
	// 転送が終わったので構造体情報を開放
	delete[] indexes;
	delete[] dx_vtx;
}

void DirectDevice::UpdateProjection(CRProjection projection)
{
	D3DXMATRIX mxProj;

	switch (projection.type)
	{

	// パースペクティブ変換
	case ProjectionType::Perspective:
	{
		D3DXMatrixPerspectiveLH(&mxProj,
			projection.width, projection.height,
			projection.zn, projection.zf);
	}
	break;

	// オルソ変換
	case ProjectionType::Ortho:
	{
		D3DXMatrixOrthoLH(&mxProj,
			projection.width, projection.height,
			projection.zn, projection.zf);
	}
	break;

	}

	// プロジェクションパイプラインを設定
	this->device->SetTransform(D3DTS_PROJECTION, &mxProj);
}

void DirectDevice::UpdateCamera(CRCamera camera)
{
	D3DXMATRIX mxView;
	D3DXVECTOR3 eye, at, up;

	// 位置情報を変換
	ConvertD3DVector3(&eye, camera.pos);
	ConvertD3DVector3(&at, camera.target);
	ConvertD3DVector3(&up, camera.up);

	// DirectXの補助関数を使って制御
	::D3DXMatrixLookAtLH(&mxView, &eye, &at, &up);

	// ビューイングパイプラインを設定
	this->device->SetTransform(D3DTS_VIEW, &mxView);
}

void DirectDevice::SetLight(int index, CRLight light)
{

	// ライト情報をデバイス用に変換
	D3DLIGHT9 dlight = this->ConvertD3DLight(light);

	// ライト情報を転送
	this->device->SetLight(index, &dlight);

}

void DirectDevice::UpdateLight(int index)
{

	// 既に点灯されているかを判定してスイッチ形式で切り替え
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

	// 頂点位置情報を変換
	vtx->x = vt.pos.GetX();
	vtx->y = vt.pos.GetY();
	vtx->z = vt.pos.GetZ();

	// 頂点法線ベクトル情報を変換
	vtx->nx = vt.normal.GetX();
	vtx->ny = vt.normal.GetY();
	vtx->nz = vt.normal.GetZ();

	// 頂点カラー情報を変換
	vtx->color = D3DCOLOR_ARGB(vt.color.alpha, vt.color.red, vt.color.green, vt.color.blue);

	// 頂点テクスチャマップ情報を変換
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

	// 変換が終わったアドレスを返却
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

	// 照明の色を変換
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

	// ライトの位置を変換
	result.Position.x = light.pos.GetX();
	result.Position.y = light.pos.GetY();
	result.Position.z = light.pos.GetZ();

	// ライトの照射先位置を変換
	result.Direction.x = light.direction.GetX();
	result.Direction.x = light.direction.GetY();
	result.Direction.x = light.direction.GetZ();

	return result;
}

D3DLIGHTTYPE DirectDevice::ConvertD3DLightType(LightType type)
{

	// ライトの種類を変換
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

	// テクスチャステージの範囲内かをチェック
	if (stage_num > 5)
	{
		return nullptr;
	}

	// プリミティブに格納されたテクスチャを取得
	PTexture tex = primitive.GetTexture(stage_num);

	// テクスチャが格納されているかをチェック
	if (tex == nullptr)
	{
		return nullptr;
	}

	// テクスチャがこのデバイスクラスに対応する形式かをチェック
	if (dynamic_cast<PDirectTexture>(tex) == nullptr)
	{
		return nullptr;
	}

	return ((PDirectTexture) tex)->GetDirectTexture();
}

} // namespace dream

#endif // NM_USE_DIRECTX
