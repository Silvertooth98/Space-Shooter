#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm.hpp>

class Rigidbody
{
public:

	Rigidbody();
	virtual ~Rigidbody();

	void SetVelocity(float x, float y, float z);
	glm::vec3 GetVelocity() { return m_velocity; }

	void SetForce(float x, float y, float z);
	void AddForce(float x, float y, float z);
	glm::vec3 GetForce() { return m_force; }

	void SetMass(float mass);
	float GetMass() { return m_mass; }

	void SetAcceleration(float x, float y, float z);
	glm::vec3 GetAcceleration() { return m_acceleration; }

	void SetPosition(float x, float y, float z);
	glm::vec3 GetPosition() { return m_position; }

	virtual void Update();

private:

	float m_mass;
	glm::vec3 m_force;
	glm::vec3 m_acceleration;
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_direction;
};
#endif