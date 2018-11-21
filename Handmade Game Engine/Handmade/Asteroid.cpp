#include "Asteroid.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"

int Asteroid::count = 0;

Asteroid::Asteroid(float x, float y, float z)
{
	m_velocity = 0.05f;
	m_position = glm::vec3(x, y, z);
	m_direction = glm::vec3(0, 0, 1);
	m_collisionSphere.SetRadius(0.5f);

	if (count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Asteroid_1.obj", "ASTEROID");
		m_model.LoadTexture("Assets\\Textures\\Asteroid_1_Diffuse.png", "ASTEROID");
	}
	
	else
	{
		m_model.SetBuffer("ASTEROID");
		m_model.SetTexture("ASTEROID");
	}

	count++;
}

Asteroid::~Asteroid()
{
}

void Asteroid::SetDirection(float x, float y, float z)
{
	m_direction = glm::vec3(x, y, z);
}

void Asteroid::Update()
{
	m_position += m_direction * m_velocity;

	Quaternion rotation;

	rotation.SetRotation(1.0f, glm::vec3(0, 1, 0));

	rotationTotal = rotation * rotationTotal;

	m_collisionSphere.SetPosition(m_position.x, m_position.y, m_position.z);

	if (m_position.z >= 17.5f)
	{
		m_position.z = -25.0f;
	}
}

void Asteroid::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position);
	m_transform = glm::scale(m_transform, glm::vec3(0.3f, 0.3f, 0.3f));
	m_transform *= rotationTotal.ConvertToMatrix();

	GameObject::setMatrix(m_transform);

	GameObject::SendToShader(false, true);
	m_model.Draw();

	//render asteroid
	TheDebug::Instance()->DrawVector3D(0, 0, 3, 6, 1, 0, 0);
	m_collisionSphere.Draw();
}