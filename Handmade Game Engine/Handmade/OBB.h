#ifndef OBB_H
#define OBB_H

#include <glm.hpp>
#include "Quaternion.h"

class OBB
{
public:

	OBB();

	void SetRotation(Quaternion rotation);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetDimension(float width, float height, float depth);

	bool isColliding(const OBB& secondBox) const;

	void Update();
	void Draw();

private:

	glm::vec3 m_upAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_forwardAxis;
	glm::vec3 m_corners[8];

	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::vec3 m_halfdimension;
	glm::vec3 m_scale;

	Quaternion m_rotation;
};
#endif