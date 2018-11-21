#ifndef ENEMY_H
#define ENEMY_H

#include <glm.hpp>
#include "GameObject.h"
#include "OBB.h"

class Player;

class Enemy : public GameObject
{
public:
	Enemy(std::string tag);
	virtual ~Enemy();	

public:
	void SetVelocity(float vel) { m_velocity = vel; }

	glm::vec3 SetDirection(Player* player);

	void SetPosition(float x, float y, float z);
	void SetRespawn();
	glm::vec3 GetPos() { return m_position; }
	glm::vec3 GetSpawnPoint() { return m_spawnPoint; }

	OBB& GetBound() { return m_bound; }

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:
	float m_velocity;
	float m_enemyRot;

	glm::vec3 m_oldEnemyDir;
	glm::vec3 m_newEnemyDir;
	glm::vec3 m_position;
	glm::vec3 m_spawnPoint;
	glm::vec3 m_direction;
	glm::mat4 m_transform;

	std::string m_tag;

	static int count;

	Model m_model;

	Quaternion m_rotationTotal;

	OBB m_bound;
};
#endif