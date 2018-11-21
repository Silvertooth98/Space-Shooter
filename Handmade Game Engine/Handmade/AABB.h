#ifndef AABB_H
#define AABB_H

#include <glm.hpp>
#include "Sphere.h"

class AABB
{
public:
	AABB();

	bool isColliding(const AABB& secondBox) const;
	bool isSphereColliding(Sphere& secondSphere) const;

	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetDimension(float x, float y, float z);

	void Update();
	void Draw();

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::vec3 m_dimension;
};
#endif