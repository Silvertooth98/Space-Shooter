#include "Bullet.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"

int Bullet::s_count = 0;

Bullet::Bullet(float x, float y, float z, glm::vec3 direction)
{
	m_position = glm::vec3(x, y, z);
	m_direction = direction;
	m_velocity = 0.5f;
	m_bound.SetDimension(0.6f, 0.6f, 1.1f);

	if (s_count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Bullet.obj", "BULLET");
		m_model.LoadTexture("Assets\\Textures\\Bullet_Diffuse.png", "BULLET");
	}

	else
	{
		m_model.SetBuffer("BULLET");
		m_model.SetTexture("BULLET");
	}

	s_count++;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_direction = m_rotationTotal * m_direction;

	m_position += m_direction * m_velocity;

	//Set the rotation and position of the collision box (m_bound)
	m_bound.SetRotation(m_rotationTotal);
	m_bound.SetPosition(m_position.x, m_position.y, m_position.z);

	//Update the collision box of the enemy so the box moves with it
	m_bound.Update();
}

void Bullet::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position);

	GameObject::setMatrix(m_transform);

	GameObject::SendToShader(false, true);
	m_model.Draw();

	m_bound.Draw();
}