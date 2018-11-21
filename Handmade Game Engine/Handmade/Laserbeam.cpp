#include "Laserbeam.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"

int Laserbeam::s_count = 0;

Laserbeam::Laserbeam(float x, float y, float z, glm::vec3 direction)
{
	m_position = glm::vec3(x, y, z);
	m_direction = direction;
	m_velocity = 0.5f;
	m_bound.SetDimension(0.6f, 0.6f, 1.2f);

	if (s_count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Bullet.obj", "LASERBEAM");
		m_model.LoadTexture("Assets\\Textures\\Bullet_Diffuse.png", "LASERBEAM");
	}

	else
	{
		m_model.SetBuffer("LASERBEAM");
		m_model.SetTexture("LASERBEAM");
	}

	s_count++;
}

Laserbeam::~Laserbeam()
{
}

void Laserbeam::Update()
{
	m_direction = m_rotationTotal * m_direction;

	m_position += m_direction * m_velocity;

	//Set the rotation and position of the collision box (m_bound)
	m_bound.SetRotation(m_rotationTotal);
	m_bound.SetPosition(m_position.x, m_position.y, m_position.z);

	//Update the collision box of the enemy so the box moves with it
	m_bound.Update();
}

void Laserbeam::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position);

	//scale it lower
	m_transform = glm::scale(m_transform, glm::vec3(0.3f, 0.3f, 20.0f));

	GameObject::setMatrix(m_transform);

	GameObject::SendToShader(false, true);
	m_model.Draw();

	m_bound.Draw();
}
