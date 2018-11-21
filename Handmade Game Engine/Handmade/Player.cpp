#include "Player.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "Bullet.h"
#include "Laserbeam.h"
#include "AudioManager.h"

Player::Player()
{
	m_rigidbody.SetMass(100.0f);
	m_rigidbody.SetPosition(0.0f, 0.0f, 5.0f);
	m_turningAngle = 0.0f;
	m_bound.SetDimension(17.5f, 10.0f, 15.0f);
	m_lives = 3;
	m_hitsTaken = 0;

	//Load model for the player
	m_model.LoadModel("Assets\\Models\\Spaceship.obj", "SPACE_SHIP");
	m_model.LoadTexture("Assets\\Textures\\Spaceship_Diffuse.png", "SPACE_SHIP");

	TheAudio::Instance()->LoadFromFile("Assets\\Audio\\Hover.wav", AudioManager::MUSIC_AUDIO, "Movement");
	m_movementAudio.SetAudioData("Movement", AudioManager::MUSIC_AUDIO);
	m_movementAudio.Play();
	m_movementAudio.Volume() = 0.5f;
	m_movementAudio.SetLoopCount(Audio::ENDLESS_LOOP);

	TheAudio::Instance()->LoadFromFile("Assets\\Audio\\Laser_Player.wav", AudioManager::SFX_AUDIO, "BulletAudio");
	m_bulletAudio.SetAudioData("BulletAudio", AudioManager::SFX_AUDIO);

	TheAudio::Instance()->LoadFromFile("Assets\\Audio\\Laser_Enemy.wav", AudioManager::SFX_AUDIO, "LaserbeamAudio");
	m_laserbeamAudio.SetAudioData("LaserbeamAudio", AudioManager::SFX_AUDIO);
}

Player::~Player()
{
}

void Player::CheckBoundariesRightSide()
{
	if (m_position.x >= 12.0f)
	{
		m_rigidbody.SetVelocity(0.0f, 0.0f, 0.0f);
		m_rigidbody.SetAcceleration(0.0f, 0.0f, 0.0f);
		m_rigidbody.SetForce(0.0f, 0.0f, 0.0f);
	}
}

void Player::CheckBoundariesLeftSide()
{
	if (m_position.x <= -12.0f)
	{
		m_rigidbody.SetVelocity(0.0f, 0.0f, 0.0f);
		m_rigidbody.SetAcceleration(0.0f, 0.0f, 0.0f);
		m_rigidbody.SetForce(0.0f, 0.0f, 0.0f);
	}
}

bool Player::CheckCollision(Enemy* m_enemy)
{
	if (GetBound().isColliding(m_enemy->GetBound()))
	{
		m_hitsTaken++;
		m_hasCollided = true;
	}

	else
	{
		m_hasCollided = false;
	}

	for (int i = 0; i < TOTAL_BULLETS; i++)
	{
		if (m_bullet[i])
		{
			if (m_bullet[i]->getBound().isColliding(m_enemy->GetBound()))
			{
				m_bullet[i]->IsAlive() = false;
				m_hasCollided = true;
			}
		}
	}

	if (m_hitsTaken == 3)
	{
		takeDamage();
		m_hitsTaken = 0;
	}

	return m_hasCollided;
}

void Player::takeDamage()
{
	m_lives--;

	if (m_lives <= 0)
	{
		m_lives = 0;
	}
}

void Player::bulletAudio()
{
	m_bulletAudio.Stop();
	m_bulletAudio.Play();
	m_bulletAudio.Volume() = 0.5f;
}

void Player::laserbeamAudio()
{
	m_laserbeamAudio.Stop();
	m_laserbeamAudio.Play();
	m_laserbeamAudio.Volume() = 0.5f;
}

OBB& Player::getLaserbeamBox()
{
	if (m_hasFiredLaser)
	{
		return m_laserbeam->getBound();
	}
}

void Player::Shoot()
{
	for (int i = 0; i < TOTAL_BULLETS; i++)
	{
		if (m_bullet[i] == nullptr)
		{
			m_bullet[i] = new Bullet(m_position.x, m_position.y, m_position.z, m_lookAt);
			bulletAudio();
			std::cout << "Shoot Bullet" << std::endl;
			break;
		}
	}
}

void Player::fireLaser()
{
	m_laserbeam = new Laserbeam(m_position.x, m_position.y, m_position.z - 10.0f, m_lookAt);
	laserbeamAudio();
	std::cout << "Fire Laserbeam" << std::endl;
}

void Player::deleteBullet()
{
	for (int i = 0; i < TOTAL_BULLETS; i++)
	{
		if (m_bullet[i] && !(m_bullet[i]->IsAlive()) || m_bullet[i] && (m_bullet[i]->GetPos().z <= -50.0f))
		{
			delete m_bullet[i];
			m_bullet[i] = nullptr;
		}
	}
}

void Player::Update()
{
	m_timer += 0.016f;

	deleteBullet();

	if (m_timer >= 3.0f)
	{
		m_hasFiredLaser = false;
	}

	//read keys from keyboard
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	//rotation quaternion to create temp transformations below
	Quaternion rotation;

	//keypresses with functions for movement and firing
	if (keys[SDL_SCANCODE_LEFT])
	{
		m_rigidbody.SetForce(-150.0f, 0.0f, 0.0f);
		m_wasMovingLeft = true;
		m_wasMovingRight = false;
		m_turningAngle -= 1.0f;

		if (m_turningAngle <= -30.0f)
		{
			m_turningAngle = -30.0f;
		}

		if (m_position.x >= 12.0f)
		{
			m_rigidbody.SetVelocity(0.0f, 0.0f, 0.0f);
			m_rigidbody.SetAcceleration(0.0f, 0.0f, 0.0f);
		}

		CheckBoundariesLeftSide();
	}

	else if (keys[SDL_SCANCODE_RIGHT])
	{
		m_rigidbody.SetForce(150.0f, 0.0f, 0.0f);
		m_wasMovingRight = true;
		m_wasMovingLeft = false;
		m_turningAngle += 1.0f;

		if (m_turningAngle >= 30.0f)
		{
			m_turningAngle = 30.0f;
		}

		if (m_position.x <= -12.0f)
		{
			m_rigidbody.SetVelocity(0.0f, 0.0f, 0.0f);
			m_rigidbody.SetAcceleration(0.0f, 0.0f, 0.0f);
		}

		CheckBoundariesRightSide();
	}

	else if (keys[SDL_SCANCODE_SPACE])
	{
		Shoot();
	}

	else if (keys[SDL_SCANCODE_F] && m_hasFiredLaser == false)
	{
		fireLaser();
		m_hasFiredLaser = true;
		m_timer = 0.0f;
	}

	else
	{
		CheckBoundariesLeftSide();
		CheckBoundariesRightSide();

		if (m_turningAngle > 0) //Right
		{
			m_turningAngle -= 0.5f;
		}

		else if (m_turningAngle < 0) //Left
		{
			m_turningAngle += 0.5f;
		}

		if (m_wasMovingLeft == true)
		{
			m_rigidbody.SetForce(125.0f, 0.0f, 0.0f);

			if (m_rigidbody.GetVelocity().x >= 0.0f)
			{
				m_rigidbody.SetForce(0.0f, 0.0f, 0.0f);
				CheckBoundariesLeftSide();
				CheckBoundariesRightSide();
			}
		}

		if (m_wasMovingRight == true)
		{
			m_rigidbody.SetForce(-125.0f, 0.0f, 0.0f);

			if (m_rigidbody.GetVelocity().x <= 0.0f)
			{
				m_rigidbody.SetForce(0.0f, 0.0f, 0.0f);
				CheckBoundariesLeftSide();
				CheckBoundariesRightSide();
			}
		}
	}

	//calculate new position of player using Euler Integration
	m_rigidbody.Update();
	m_position = m_rigidbody.GetPosition();

	//Quaternion multiplication for the rotation of the direction the ship is looking at
	//will be used for the bullet system, what the ship is aiming at
	m_lookAt = glm::vec3(0, 0, -1);
	m_lookAt = m_rotationTotal * m_lookAt;

	m_bound.SetScale(0.3f, 0.3f, 0.3f);
	m_bound.SetRotation(m_rotationTotal);
	m_bound.SetPosition(m_position.x, m_position.y, m_position.z);
	m_bound.Update();

	for (int i = 0; i < TOTAL_BULLETS; i++)
	{
		if (m_bullet[i])
		{
			m_bullet[i]->Update();
		}
	}

	if (m_laserbeam)
	{
		m_laserbeam->Update();
	}
}

void Player::Draw()
{
	//reset transformation
	m_transform = glm::mat4(1.0f);

	//position and rotate player based on key actions
	m_transform = glm::translate(m_transform, m_position);

	m_transform = glm::rotate(m_transform, glm::radians(180.0f), glm::vec3(0, 1, 0));

	//apply current rotation to current transformation
	m_transform *= m_rotationTotal.ConvertToMatrix();

	m_transform = glm::rotate(m_transform, glm::radians(m_turningAngle), glm::vec3(0, 0, 1));

	//scale it lower
	m_transform = glm::scale(m_transform, glm::vec3(0.3f, 0.3f, 0.3f));

	//set engine matrix and render player
	GameObject::setMatrix(m_transform);

	//render player ship and reset transformation
	GameObject::SendToShader(false, true);
	m_model.Draw();
	m_bound.Draw();
	m_transform = glm::mat4(1.0f);
	GameObject::setMatrix(m_transform);

	for (int i = 0; i < TOTAL_BULLETS; i++)
	{
		if (m_bullet[i])
		{
			m_bullet[i]->Draw();
		}
	}

	if (m_laserbeam)
	{
		m_laserbeam->Draw();
	}

	m_transform = glm::mat4(1.0f);
	GameObject::setMatrix(m_transform);

	//render player direction line
	glm::vec3 finalPos;
	finalPos = m_position + (m_lookAt * 4.0f);
	TheDebug::Instance()->DrawLine3D(m_position.x, m_position.y, m_position.z,
						         finalPos.x, finalPos.y, finalPos.z, 6, 1, 0, 0);
}