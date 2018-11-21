#ifndef PLANET_H
#define PLANET_H

#include "GameObject.h"
#include <glm.hpp>

class Planet : public GameObject
{
public:
	Planet(float x, float y, float z);
	virtual ~Planet();

public:
	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:
	float m_angle;

	glm::vec3 m_planetPosition;

	glm::mat4 m_transform;

	static int count;
	Model m_model;
};
#endif