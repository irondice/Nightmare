
#include "primitive.h"

namespace dream
{

PrimitiveIndexed::PrimitiveIndexed(uint size, uint index_size) : 
	Primitive(size), index_size(index_size)
{
	this->indexes = std::shared_ptr<uint>(
		new uint[index_size], std::default_delete<uint[]>());
	for (uint i = 0; i < this->index_size; i++)
	{
		this->indexes.get()[i] = 0;
	}
}

} // namespace dream
