
#ifndef __NM_RENDER_H__
#define __NM_RENDER_H__

#include "primitive.h"
#include "vector.h"
#include "types.h"
#include "project.h"

namespace dream
{

enum class LightType
{
	Point,
	Spot,
	Directional,
};

struct Light
{
	LightType type;
	Color diffuse;
	Color specular;
	Color ambient;
	Vector pos;
	Vector direction;
};

enum class RenderType
{
	Lighting
};

} // namespace dream

#endif // __NM_RENDER_H__
