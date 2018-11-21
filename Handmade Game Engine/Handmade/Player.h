#ifndef PLAYER_H
#define PLAYER_H

#include <glm.hpp>
#include "GameObject.h"
#include "Bullet.h"
#include "Laserbeam.h"
#include "Asteroid.h"
#include "Quaternion.h"
#include "AABB.h"
#include "OBB.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "Audio.h"

class Player : public GameObject
{
public:
	enum { BULLET_1, BULLET_2, BULLET_3, BULLET_4, TOTAL_BULLETS };
	Player();
	virtual ~Player();

	void CheckBoundariesRightSide();
	void CheckBoundariesLeftSide();

	glm::vec3 GetPos() { return m_position; }
	bool CheckCollision(Enemy* m_enemy);

	void takeDamage();
	int getLives() { return  m_lives; }

	void bulletAudio();
	void laserbeamAudio();
	
	OBB& getLaserbeamBox();
	OBB& GetBound() { return m_bound; }

	virtual void Shoot();
	virtual void fireLaser();
	virtual void deleteBullet();
	
	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:
	float m_angle;
	float m_turningAngle;
	float m_timer;

	int m_hitsTaken;
	int m_lives;

	glm::vec3 m_position;
	glm::vec3 m_direction;
	
	glm::vec3 m_bulletDirection;
	glm::mat4 m_transform;
	glm::vec3 m_lookAt;

	bool m_hasCollided = false;
	bool m_hasFiredLaser = false;
	bool m_wasMovingLeft = false;
	bool m_wasMovingRight = false;

	Quaternion m_rotationTotal;

	Model m_model;
	Audio m_movementAudio;
	Audio m_bulletAudio;
	Audio m_laserbeamAudio;

	Bullet* m_bullet[TOTAL_BULLETS];
	Laserbeam* m_laserbeam;
	Enemy* m_enemy;

	OBB m_bound;
	Rigidbody m_rigidbody;
};
#endif