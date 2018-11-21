#include "Rigidbody.h"
#include "Game.h"

Rigidbody::Rigidbody()
{
	m_mass = 0.0f;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::SetVelocity(float x, float y, float z)
{
	m_velocity = glm::vec3(x, y, z);
}

void Rigidbody::SetForce(float x, float y, float z)
{
	m_force = glm::vec3(x, y, z);
}

void Rigidbody::AddForce(float x, float y, float z)
{
	m_force += glm::vec3(x, y, z);
}

void Rigidbody::SetMass(float mass)
{
	m_mass = mass;
}

void Rigidbody::SetAcceleration(float x, float y, float z)
{
	m_acceleration = glm::vec3(x, y, z);
}

void Rigidbody::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Rigidbody::Update()
{
	float deltaTime = TheGame::Instance()->GetElapsedTime() / 1000.0f;

	//Work out acceleration
	if (m_mass >= 0.0f)
	{
		m_acceleration = m_force / m_mass;
	}

	glm::vec3 oldVel = m_velocity;
	m_velocity += m_acceleration * deltaTime;
	m_position += 0.5f * (m_velocity + oldVel) * deltaTime;
}