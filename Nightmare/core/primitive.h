
#ifndef __NM_PRIMITIVE_H__
#define __NM_PRIMITIVE_H__

#include "vector.h"
#include "project.h"

namespace dream
{

// 
// カラー情報
// 
struct Color
{
public:

	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color White;
	const static Color Black;
	
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;

public:

	Color(u8 red, u8 green, u8 blue, u8 alpha) :
		red(red),
		green(green),
		blue(blue),
		alpha(alpha)
	{}

	Color(u8 red, u8 green, u8 blue) :
		Color(red, green, blue, 0x00)
	{}

	Color(void) :
		Color(0x00, 0x00, 0x00)
	{}

	Color(CRColor color) :
		Color(color.red, color.green, color.blue, color.alpha)
	{}

public:

	bool operator == (CRColor color)
	{
		
		// 赤色の比較
		if (color.red != color.red)
		{
			return false;
		}

		// 緑色の比較
		if (color.green != color.green)
		{
			return false;
		}

		// 青色の比較
		if (color.blue != color.blue)
		{
			return false;
		}

		// 透過色の比較
		if (color.alpha != color.alpha)
		{
			return false;
		}

		// 要素が全て一致した場合は true になります。
		return true;
	}

	bool operator != (CRColor color)
	{
		return !this->operator==(color);
	}

};

// 
// 頂点情報
// 
struct Vertex
{
public:

	Vector pos;
	Vector normal;
	Color color;
	float tex_tu[5];
	float tex_tv[5];

public:

	Vertex(void)
	{
		for (uint i = 0; i < 5; i++)
		{
			this->tex_tu[i] = 0;
			this->tex_tv[i] = 0;
		}
	}

	Vertex(CRVertex vtx)
	{
		this->pos.Copy(vtx.pos);
		this->normal.Copy(vtx.normal);
		this->color = vtx.color;
		for (uint i = 0; i < 5; i++)
		{
			this->tex_tu[i] = vtx.tex_tu[i];
			this->tex_tv[i] = vtx.tex_tv[i];
		}
	}

	~Vertex(void)
	{}

};

// 
// 描写するプリミティブの種類を指定
// 
enum class PrimitiveType
{
	POINTS,				// 単一の点
	LINES,				// 二点を繋いだ線
	LINE_STRIP,			// 複数の点を繋いだ線
	TRIANGLE_FAN,		// ３つ以上の点を繋いだ三角形 (起点連結)
	TRIANGLE_LIST,		// ３つの点を繋いだ三角形
	TRIANGLE_STRIP,		// ３つ以上の点を繋いだ三角形 (連番配置)
};

// 
// 描写するプリミティブを設定
// 
class Primitive
{
protected:

	uint size;
	uint count;
	std::shared_ptr<Vertex> vertexs;
	PTexture tex[5];
	PrimitiveType type;

public:

	explicit Primitive(uint size);
	virtual ~Primitive(void);

public:

	// 
	// 描写するプリミティブの種類を設定
	// 
	void SetType(PrimitiveType type)
	{
		this->type = type;
	}

	// 
	// 描写する頂点情報を設定
	// params:
	//   index - 頂点番号
	//   vtx   - 頂点情報
	// 
	void SetVertex(uint index, CRVertex vtx)
	{
		this->vertexs.get()[index] = vtx;
	}

	// 
	// 描写するポリゴンの数を設定
	// 
	void SetCount(uint count)
	{
		this->count = count;
	}

	// 
	// 指定したテクスチャステージにテクスチャ情報を設定します。
	// 
	void SetTexture(uint stage, PTexture tex)
	{
		this->tex[stage] = tex;
	}

public:

	// 
	// 頂点の数を返します。
	// 
	uint GetMaxVertexSize(void) const
	{
		return this->size;
	}

	// 
	// ポリゴンの数を返します。
	// 
	uint GetCount(void) const
	{
		return this->count;
	}

	// 
	// 頂点の数を返します。
	// 
	PVertex GetVertexs(void) const
	{
		return this->vertexs.get();
	}

	// 
	// プリミティブの種類を返します。
	// 
	PrimitiveType GetType(void) const
	{
		return this->type;
	}

	PTexture GetTexture(uint index)
	{
		return this->tex[index];
	}

};

// 
// インデックスバッファを使用したバージョン
// 
class PrimitiveIndexed : public Primitive
{
private:

	uint index_size;
	std::shared_ptr<uint> indexes;

public:

	explicit PrimitiveIndexed(uint size, uint index_size);

	~PrimitiveIndexed(void)
	{
		this->indexes.reset();
	}

public:

	void SetIndex(uint index, uint index_num)
	{
		this->indexes.get()[index] = index_num;
	}

public:

	uint GetIndexSize(void) const
	{
		return this->index_size;
	}

	uint GetIndex(uint index)
	{
		return this->indexes.get()[index];
	}

};

} // namespace dream

#endif // __NM_PRIMITIVE_H__
