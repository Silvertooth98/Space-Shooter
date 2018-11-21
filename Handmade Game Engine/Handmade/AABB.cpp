#include "AABB.h"
#include "DebugManager.h"
#include <math.h>
#include <iostream>

AABB::AABB()
{
	m_scale = glm::vec3(1, 1, 1);
	m_dimension = glm::vec3(1, 1, 1);
}

bool AABB::isColliding(const AABB& secondBox) const
{
	return ((m_max.x >= secondBox.m_min.x && secondBox.m_max.x >= m_min.x) &&
		    (m_max.y >= secondBox.m_min.y && secondBox.m_max.y >= m_min.y) &&
		    (m_max.z >= secondBox.m_min.z && secondBox.m_max.z >= m_min.z));
}

bool AABB::isSphereColliding(Sphere& secondSphere) const
{
	glm::vec3 m_dv = m_position - secondSphere.GetPosition();

	glm::vec3 clampValue = glm::clamp(m_dv, -m_dimension, m_dimension);

	glm::vec3 pointOnEdge = m_position - clampValue;

	glm::vec3 SphereFromBox = secondSphere.GetPosition() - pointOnEdge;

	float SphereRadii = secondSphere.GetRadius();

	if ((SphereFromBox.x <= SphereRadii) && (SphereFromBox.y <= SphereRadii) && (SphereFromBox.z <= SphereRadii))
	{
		std::cout << "COLLISION WITH SPHERE!" << std::endl;
	}
	else
	{
		std::cout << "NO COLLISION" << std::endl;
	}

	return false;
}

void AABB::SetScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void AABB::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void AABB::SetDimension(float x, float y, float z)
{
	m_dimension = glm::vec3(x, y, z);
}

void AABB::Update()
{
	glm::vec3 halfDim = (m_dimension * m_scale) / 2.0f;

	m_min.x = m_position.x - halfDim.x;
	m_max.x = m_position.x + halfDim.x;

	m_min.y = m_position.y - halfDim.y;
	m_max.y = m_position.y + halfDim.y;

	m_min.z = m_position.z - halfDim.z;
	m_max.z = m_position.z + halfDim.z;
}

void AABB::Draw()
{
	TheDebug::Instance()->DrawCube3D(m_dimension.x,
									 m_dimension.y,
									 m_dimension.z, 1, 0, 0, 0.4f);
}