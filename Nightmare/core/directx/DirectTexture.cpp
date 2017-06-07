
#include "../texture.h"

namespace dream
{

DirectTexture::DirectTexture(LPDIRECT3DTEXTURE9 tex) : tex(tex), Texture(GetWidth(tex), GetHeight(tex))
{}

DirectTexture::~DirectTexture(void)
{
	this->tex->Release();
}

} // namespace dream
