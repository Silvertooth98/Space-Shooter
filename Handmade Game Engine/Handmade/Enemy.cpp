#include "Enemy.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"
#include "Player.h"
#include <gtx\vector_angle.hpp>

int Enemy::count = 0;

Enemy::Enemy(std::string tag)
{
	m_velocity = 0.01f;
	m_position = glm::vec3(0, 0, 0);
	m_spawnPoint = glm::vec3(0, 0, 0);
	m_direction = glm::vec3(0, 0, 1);
	m_bound.SetDimension(17.5f, 6.0f, 6.0f);

	m_tag = tag;

	if (count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Enemy.obj", "ENEMY_SHIP");
		m_model.LoadTexture("Assets\\Textures\\Enemy_Diffuse.png", "ENEMY_SHIP");
	}
	else
	{
		m_model.SetBuffer("ENEMY_SHIP");
		m_model.SetTexture("ENEMY_SHIP");
	}

	count++;
}

Enemy::~Enemy()
{
}

glm::vec3 Enemy::SetDirection(Player* player)
{
	m_oldEnemyDir = m_direction;
	m_newEnemyDir = player->GetPos() - GetPos();
	m_direction = glm::normalize(m_newEnemyDir);
	
	return m_direction;
}

void Enemy::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);

	m_spawnPoint = m_position;
}

void Enemy::SetRespawn()
{
	SetPosition(m_spawnPoint.x, m_spawnPoint.y, m_spawnPoint.z);

	m_direction = glm::vec3(0, 0, 1);

	m_rotationTotal.SetRotation(0, glm::vec3(0, 1, 0));
}

void Enemy::Update()
{
	Quaternion rotation;

	if (m_newEnemyDir.z > 15.0f)
	{
		m_direction = glm::vec3(0, 0, 1);

		m_position += m_direction * m_velocity;
	}
	else if (m_newEnemyDir.z < 15.0f)
	{
		m_direction = glm::normalize(m_newEnemyDir);

		m_position += m_direction * m_velocity;

		//Enemy rotation angle depending on the old enemy direction and the new one
		m_enemyRot = glm::degrees(glm::angle(glm::normalize(m_oldEnemyDir), m_direction));
				
		if (m_oldEnemyDir.x < m_direction.x) //Turn right situation
		{
			rotation.SetRotation(m_enemyRot, glm::vec3(0, 1, 0));
			m_rotationTotal = rotation * m_rotationTotal;
		}
		else if (m_oldEnemyDir.x > m_direction.x) //Turn left situation
		{
			rotation.SetRotation(m_enemyRot, glm::vec3(0, -1, 0));
			m_rotationTotal = rotation * m_rotationTotal;
		}
	}

	//m_position += m_direction * m_velocity;

	////Enemy rotation angle depending on the old enemy direction and the new one
	//m_enemyRot = glm::degrees(glm::angle(glm::normalize(m_oldEnemyDir), m_direction));
	//
	//Quaternion rotation;
	//
	//if (m_oldEnemyDir.x < m_direction.x) //Turn right situation
	//{
	//	rotation.SetRotation(m_enemyRot, glm::vec3(0, 1, 0));
	//	m_rotationTotal = rotation * m_rotationTotal;
	//}
	//else if (m_oldEnemyDir.x > m_direction.x) //Turn left situation
	//{
	//	rotation.SetRotation(m_enemyRot, glm::vec3(0, -1, 0));
	//	m_rotationTotal = rotation * m_rotationTotal;
	//}

	//Set the scale, rotation and position of the collision box (m_bound)
	m_bound.SetScale(0.2f, 0.2f, 0.2f);
	m_bound.SetRotation(m_rotationTotal);
	m_bound.SetPosition(m_position.x, m_position.y, m_position.z);

	//Update the collision box of the enemy so the box moves with it
	m_bound.Update();
}

void Enemy::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position);

	m_transform = glm::scale(m_transform, glm::vec3(0.2f, 0.2f, 0.2f));

	//Rotation
	m_transform *= m_rotationTotal.ConvertToMatrix();

	GameObject::setMatrix(m_transform);

	//render enemy ship
	GameObject::SendToShader(false, true);
	m_model.Draw();
	m_bound.Draw();
	//reset transformation
	m_transform = glm::mat4(1.0f);
	GameObject::setMatrix(m_transform);

	//render enemy direction line
	glm::vec3 finalPos;
	finalPos = m_position + (m_direction * 5.0f);
	TheDebug::Instance()->DrawLine3D(m_position.x, m_position.y, m_position.z,
									 finalPos.x, finalPos.y, finalPos.z, 6, 1, 0, 0);
}