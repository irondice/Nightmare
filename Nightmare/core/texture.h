
#ifndef __NM_TEXTURE_H__
#define __NM_TEXTURE_H__

#include "types.h"
#include "project.h"

namespace dream
{

class TextureManager
{
private:

	std::map<std::string, std::shared_ptr<Texture>> textures;

public:

	explicit TextureManager(void)
	{}

	~TextureManager(void)
	{
		this->textures.clear();
	}

public:

	bool RegisterTexture(const char* id, std::shared_ptr<Texture> tex)
	{
		auto it = this->textures.find(id);

		if (it == this->textures.end())
		{
			this->textures[id] = tex;

			return true;
		}

		return false;
	}

	bool UnRegisterTexture(const char* id)
	{
		auto it = this->textures.find(id);

		if (it != this->textures.end())
		{
			this->textures.erase(it++);

			return true;
		}

		return false;
	}

public:

	bool IsEmpty(void) const
	{
		return this->textures.empty();
	}

	PTexture GetTexture(const char* id)
	{
		auto it = this->textures.find(std::string(id));

		if (it != this->textures.end())
		{
			return it->second.get();
		}

		return nullptr;
	}

};

class Texture abstract
{
protected:

	ushort width;
	ushort height;

public:

	explicit Texture(ushort width, ushort height) : width(width), height(height) {}
	virtual ~Texture(void) {}

};

#ifdef NM_USE_DIRECTX

class DirectTexture : public Texture
{
private:

	LPDIRECT3DTEXTURE9 tex;

public:

	explicit DirectTexture(LPDIRECT3DTEXTURE9 tex);
	~DirectTexture(void);

public:

	LPDIRECT3DTEXTURE9 GetDirectTexture(void)
	{
		return this->tex;
	}

private:

	short GetWidth(LPDIRECT3DTEXTURE9 tex)
	{
		D3DSURFACE_DESC surfaceDesc;
		tex->GetLevelDesc(0, &surfaceDesc);
		return surfaceDesc.Width;
	}

	short GetHeight(LPDIRECT3DTEXTURE9 tex)
	{
		D3DSURFACE_DESC surfaceDesc;
		tex->GetLevelDesc(0, &surfaceDesc);
		return surfaceDesc.Height;
	}

};

#endif // NM_USE_DIRECTX

} // namespace dream

#endif // __NM_TEXTURE_H__
