
#include "primitive.h"

namespace dream
{

const Color Color::Red =	Color(255, 0,   0  );
const Color Color::Green =	Color(0,   255, 0  );
const Color Color::Blue =	Color(0,   0,   255);
const Color Color::Black =	Color(0,   0,   0  );
const Color Color::White =	Color(255, 255, 255);

Primitive::Primitive(uint size) :
	size(size),
	count(1)
{
	this->vertexs = std::shared_ptr<Vertex>(
		new Vertex[size], std::default_delete<Vertex[]>());
	this->type = PrimitiveType::POINTS;
	for (uint i = 0; i < 5; i++)
	{
		this->tex[i] = nullptr;
	}
}

Primitive::~Primitive(void)
{
	this->vertexs.reset();
}

} // namespace dream
