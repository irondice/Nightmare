
#ifndef __NM_CAMERA_H__
#define __NM_CAMERA_H__

#include "vector.h"
#include "project.h"

namespace dream
{

enum class ProjectionType
{
	Perspective,
	Ortho
};

struct Projection
{
public:

	float width;
	float height;
	float zn;
	float zf;

	ProjectionType type;

public:

	Projection(void)
	{
		width = 0.0f;
		height = 0.0f;
		zn = 0.0f;
		zf = 0.0f;
		type = ProjectionType::Ortho;
	}

	~Projection(void) {}

};

struct Camera
{
public:

	Vector pos;
	Vector target;
	Vector up;

public:

	Camera(void) {}
	~Camera(void) {}

};

} // namespace dream

#endif // __NM_CAMERA_H__
