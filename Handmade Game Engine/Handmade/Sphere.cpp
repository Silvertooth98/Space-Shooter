#include "Sphere.h"
#include "DebugManager.h"

void Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

void Sphere::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

bool Sphere::isColliding(const Sphere & secondSphere) const
{
	float distance = glm::length(m_position - secondSphere.m_position);

	float sumOfRadii = m_radius + secondSphere.m_radius;

	return (distance <= sumOfRadii);
}

void Sphere::Draw()
{
	TheDebug::Instance()->DrawSphere3D(m_radius, 0, 1, 0, 0.4f);
}
