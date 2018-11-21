#ifndef MOON_H
#define MOON_H

#include "GameObject.h"
#include <glm.hpp>

class Moon : public GameObject
{
public:
	Moon(float x, float y, float z);
	virtual ~Moon();

public:
	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:
	float m_angle;

	glm::vec3 m_moonPosition;
	glm::vec3 m_orbitPosition;

	glm::mat4 m_transform;

	static int count;
	Model m_model;
};
#endif