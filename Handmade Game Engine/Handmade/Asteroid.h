#ifndef ASTEROID_H
#define ASTEROID_H

#include <glm.hpp>
#include "GameObject.h"
#include "Quaternion.h"
#include "Sphere.h"

class Asteroid : public GameObject
{
public:
	Asteroid(float x = 0, float y = 0, float z = 0);
	virtual ~Asteroid();

public:
	void SetVelocity(float vel) { m_velocity = vel; }
	glm::vec3 GetPos() { return m_position; }

	const Sphere& GetCollisionSphere() { return m_collisionSphere; }

	void SetDirection(float x, float y, float z);

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:
	float m_velocity;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::mat4 m_transform;
	std::string m_tag;
	Quaternion rotationTotal;

	static int count;
	Model m_model;

	Sphere m_collisionSphere;
};
#endif