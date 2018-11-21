#ifndef SPHERE_H
#define SPHERE_H

#include <glm.hpp>

class Sphere
{
public:
	void SetRadius(float radius);
	void SetPosition(float x, float y, float z);

	glm::vec3 GetPosition() const { return m_position; }
	
	float GetRadius() { return m_radius; }

	bool isColliding(const Sphere& secondSphere) const;

	void Draw();

private:
	float m_radius;
	glm::vec3 m_position;
};

#endif
