
#ifndef __NM_PRIMITIVE_H__
#define __NM_PRIMITIVE_H__

#include "vector.h"
#include "project.h"

namespace dream
{

// 
// �J���[���
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
		
		// �ԐF�̔�r
		if (color.red != color.red)
		{
			return false;
		}

		// �ΐF�̔�r
		if (color.green != color.green)
		{
			return false;
		}

		// �F�̔�r
		if (color.blue != color.blue)
		{
			return false;
		}

		// ���ߐF�̔�r
		if (color.alpha != color.alpha)
		{
			return false;
		}

		// �v�f���S�Ĉ�v�����ꍇ�� true �ɂȂ�܂��B
		return true;
	}

	bool operator != (CRColor color)
	{
		return !this->operator==(color);
	}

};

// 
// ���_���
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
// �`�ʂ���v���~�e�B�u�̎�ނ��w��
// 
enum class PrimitiveType
{
	POINTS,				// �P��̓_
	LINES,				// ��_���q������
	LINE_STRIP,			// �����̓_���q������
	TRIANGLE_FAN,		// �R�ȏ�̓_���q�����O�p�` (�N�_�A��)
	TRIANGLE_LIST,		// �R�̓_���q�����O�p�`
	TRIANGLE_STRIP,		// �R�ȏ�̓_���q�����O�p�` (�A�Ԕz�u)
};

// 
// �`�ʂ���v���~�e�B�u��ݒ�
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
	// �`�ʂ���v���~�e�B�u�̎�ނ�ݒ�
	// 
	void SetType(PrimitiveType type)
	{
		this->type = type;
	}

	// 
	// �`�ʂ��钸�_����ݒ�
	// params:
	//   index - ���_�ԍ�
	//   vtx   - ���_���
	// 
	void SetVertex(uint index, CRVertex vtx)
	{
		this->vertexs.get()[index] = vtx;
	}

	// 
	// �`�ʂ���|���S���̐���ݒ�
	// 
	void SetCount(uint count)
	{
		this->count = count;
	}

	// 
	// �w�肵���e�N�X�`���X�e�[�W�Ƀe�N�X�`������ݒ肵�܂��B
	// 
	void SetTexture(uint stage, PTexture tex)
	{
		this->tex[stage] = tex;
	}

public:

	// 
	// ���_�̐���Ԃ��܂��B
	// 
	uint GetMaxVertexSize(void) const
	{
		return this->size;
	}

	// 
	// �|���S���̐���Ԃ��܂��B
	// 
	uint GetCount(void) const
	{
		return this->count;
	}

	// 
	// ���_�̐���Ԃ��܂��B
	// 
	PVertex GetVertexs(void) const
	{
		return this->vertexs.get();
	}

	// 
	// �v���~�e�B�u�̎�ނ�Ԃ��܂��B
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
// �C���f�b�N�X�o�b�t�@���g�p�����o�[�W����
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
