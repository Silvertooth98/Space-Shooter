#include "DebugManager.h"
#include "InputManager.h"
#include "PipelineManager.h"
#include "ScreenManager.h"
#include "MainState.h"
#include "EndState.h"
#include "Game.h"
#include "Planet.h"
#include "Moon.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Universe.h"
#include "Bullet.h"
#include <math.h>
#include <string>
#include <iostream>
#include <gtx\euler_angles.hpp>
#include <gtx\projection.hpp>
#include <gtc\matrix_transform.hpp>

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
MainState::MainState(GameState* state) : GameState(state)
{

	m_HUD = nullptr;
	m_HUDCamera = nullptr;
	m_mainCamera = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates the cameras and HUD objects
//------------------------------------------------------------------------------------------------------
bool MainState::OnEnter()
{
	//create the main camera to control the main view
	m_mainCamera = new MainCamera();

	//create the 2D camera for HUDs and sprite objects
	m_HUDCamera = new HUDCamera();

	//create a heads-up display object
	m_HUD = new HUD();
	m_HUD->Create();

	m_lives[HEART_1] = new Lives(glm::vec3(10, 650, 0));
	m_lives[HEART_2] = new Lives(glm::vec3(110, 650, 0));
	m_lives[HEART_3] = new Lives(glm::vec3(210, 650, 0));

	m_timerText = new TextBox(10, 600, 0, 20, "TIMER: ");
	m_scoreText = new TextBox(10, 575, 0, 20, "SCORE: ");

	//create the universe skybox
	m_universe = new Universe;

	//create the player
	m_player = new Player;

	//create the enemies and their individual properties
	m_enemy[ENEMY_1] = new Enemy("ENEMY ONE");
	m_enemy[ENEMY_1]->SetVelocity(0.05f);
	m_enemy[ENEMY_1]->SetPosition(-10, 0, -20);

	m_enemy[ENEMY_2] = new Enemy("ENEMY TWO");
	m_enemy[ENEMY_2]->SetVelocity(0.05f);
	m_enemy[ENEMY_2]->SetPosition(10, 0, -20);

	m_enemy[ENEMY_3] = new Enemy("ENEMY THREE");
	m_enemy[ENEMY_3]->SetVelocity(0.03f);
	m_enemy[ENEMY_3]->SetPosition(5, 0, -20);

	m_enemy[ENEMY_4] = new Enemy("ENEMY FOUR");
	m_enemy[ENEMY_4]->SetVelocity(0.03f);
	m_enemy[ENEMY_4]->SetPosition(-5, 0, -20);

	m_enemy[ENEMY_5] = new Enemy("ENEMY FIVE");
	m_enemy[ENEMY_5]->SetVelocity(0.05f);
	m_enemy[ENEMY_5]->SetPosition(-10, 0, -30);

	m_enemy[ENEMY_6] = new Enemy("ENEMY SIX");
	m_enemy[ENEMY_6]->SetVelocity(0.05f);
	m_enemy[ENEMY_6]->SetPosition(10, 0, -30);

	m_enemy[ENEMY_7] = new Enemy("ENEMY SEVEN");
	m_enemy[ENEMY_7]->SetVelocity(0.03f);
	m_enemy[ENEMY_7]->SetPosition(5, 0, -30);

	m_enemy[ENEMY_8] = new Enemy("ENEMY EIGHT");
	m_enemy[ENEMY_8]->SetVelocity(0.03f);
	m_enemy[ENEMY_8]->SetPosition(-5, 0, -30);

	m_enemy[ENEMY_9] = new Enemy("ENEMY NINE");
	m_enemy[ENEMY_9]->SetVelocity(0.05f);
	m_enemy[ENEMY_9]->SetPosition(-10, 0, -40);

	m_enemy[ENEMY_10] = new Enemy("ENEMY TEN");
	m_enemy[ENEMY_10]->SetVelocity(0.05f);
	m_enemy[ENEMY_10]->SetPosition(10, 0, -40);

	m_enemy[ENEMY_11] = new Enemy("ENEMY ELEVEN");
	m_enemy[ENEMY_11]->SetVelocity(0.03f);
	m_enemy[ENEMY_11]->SetPosition(5, 0, -40);

	m_enemy[ENEMY_12] = new Enemy("ENEMY TWELVE");
	m_enemy[ENEMY_12]->SetVelocity(0.03f);
	m_enemy[ENEMY_12]->SetPosition(-5, 0, -40);

	//create planets
	m_planet[MARS] = new Planet(-10, 10, -30);
	m_planet[JUPITER] = new Planet(10, 10, -30);

	//create moons
	m_moon[MOON_1] = new Moon(-10, 10, -30);
	m_moon[MOON_2] = new Moon(10, 10, -30);

	//create asteroids
	m_asteroid[ASTEROID_1] = new Asteroid(0, -10, -30);
	m_asteroid[ASTEROID_2] = new Asteroid(5, -10, -25);
	m_asteroid[ASTEROID_3] = new Asteroid(10, -10, -17);
	m_asteroid[ASTEROID_4] = new Asteroid(15, -10, -25);
	m_asteroid[ASTEROID_5] = new Asteroid(20, -10, -13);
	m_asteroid[ASTEROID_6] = new Asteroid(-5, -10, -22);
	m_asteroid[ASTEROID_7] = new Asteroid(-10, -10, -28);
	m_asteroid[ASTEROID_8] = new Asteroid(-15, -10, -12);
	m_asteroid[ASTEROID_9] = new Asteroid(-20, -10, -15);
	m_asteroid[ASTEROID_10] = new Asteroid(-7.5, 10, -12);
	m_asteroid[ASTEROID_11] = new Asteroid(-2.5, 10, -7);
	m_asteroid[ASTEROID_12] = new Asteroid(2.5, 10, -0);
	m_asteroid[ASTEROID_13] = new Asteroid(7.5, 10, -20);

	return true;
}

//------------------------------------------------------------------------------------------------------
//function that updates all active game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Update()
{
	//store keyboard key states in a temp variable for processing below
	const Uint8* keyState = TheInput::Instance()->GetKeyStates();

	//update main camera
	m_mainCamera->Update();

	//set the intial timer value
	static float timer = 0.0f;

	//increment the timer value by 0.016 which is 1 second in 60fps
	timer += 0.016f;

	//display the text in an int form - cast the float to an int
	m_timerText->SetText("TIMER: " + std::to_string((int)timer));

	//set initial score value
	static float score = 0.0f;

	m_scoreText->SetText("SCORE: " + std::to_string((int)score));

	//if ESCAPE key was pressed, return flag to end game 
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new EndState(this));
	}

	//Update the universe
	m_universe->Update();

	//Update our objects
	m_player->Update();

	if (m_player->getLives() == 0)
	{
		m_player->IsAlive() = false;
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new EndState(this));
	}
	if (m_player->getLives() == 1)
	{
		m_lives[HEART_1]->IsVisible() = true;
		m_lives[HEART_2]->IsVisible() = false;
		m_lives[HEART_3]->IsVisible() = false;
	}
	if (m_player->getLives() == 2)
	{
		m_lives[HEART_1]->IsVisible() = true;
		m_lives[HEART_2]->IsVisible() = true;
		m_lives[HEART_3]->IsVisible() = false;
	}

	if (m_player->getLives() == 3)
	{
		m_lives[HEART_1]->IsVisible() = true;
		m_lives[HEART_2]->IsVisible() = true;
		m_lives[HEART_3]->IsVisible() = true;
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (m_enemy[i])
		{
			m_enemy[i]->SetDirection(m_player);
			m_enemy[i]->Update();
		}
	}

	for (int i = 0; i < TOTAL_EXPLOSIONS; i++)
	{
		if (m_explosionAnim[i])
		{
			m_explosionAnim[i]->Update();

			if (!m_explosionAnim[i]->IsAlive())
			{
				delete m_explosionAnim[i];
				m_explosionAnim[i] = nullptr;
			}
		}
	}

	for (int i = 0; i < TOTAL_PLANETS; i++)
	{
		m_planet[i]->Update();
		m_moon[i]->Update();
	}

	for (int i = 0; i < TOTAL_ASTEROIDS; i++)
	{
		m_asteroid[i]->Update();
	}

	//OBB and OBB collision
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (m_enemy[i])
		{
			if (m_player->CheckCollision(m_enemy[i]))
			{
				std::cout << "Collision with Enemy" << std::endl;
				std::cout << m_player->getLives() << std::endl;

				if (!m_explosionAnim[i])
				{
					glm::vec3 tempPosition = m_enemy[i]->GetPos();
					m_explosionAnim[i] = new ExplosionAnim();
					m_explosionAnim[i]->SetPosition(tempPosition);
					m_enemy[i]->SetRespawn();
					score += 25.0f;
				}
			}

			if (m_player->getLaserbeamBox().isColliding(m_enemy[i]->GetBound()))
			{
				std::cout << "Player fires laser at enemy" << std::endl;

				if (!m_explosionAnim[i])
				{
					glm::vec3 tempPosition = m_enemy[i]->GetPos();
					m_explosionAnim[i] = new ExplosionAnim();
					m_explosionAnim[i]->SetPosition(tempPosition);
					m_enemy[i]->SetRespawn();
					score += 50.0f;
				}
			}
		}
	}

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that displays all active and visible game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Draw()
{
	//first set up camera which sets the view accordingly
	//make sure this is called BEFORE displaying the grid
	m_mainCamera->Draw();

#ifdef GAME_3D

	TheScreen::Instance()->Set3DScreen(60.0f, 0.1f, 1000.0f);

#ifdef DEBUG

	TheDebug::Instance()->DrawGrid3D();
	TheDebug::Instance()->DrawCoordSystem3D(15.0f);

#endif
	
#endif

#ifdef GAME_2D

	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

#ifdef DEBUG

	TheDebug::Instance()->DrawGrid2D();
	TheDebug::Instance()->DrawCoordSystem2D(15.0f);

#endif

#endif

	//Draw universe
	m_universe->Draw();

	//If the player is alive, draw him
	if (m_player->IsAlive())
	{
		m_player->Draw();
	}

	//Draw the amount of enemies that have been created
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (m_enemy[i])
		{
			m_enemy[i]->Draw();
		}
	}
	
	for (int i = 0; i < TOTAL_EXPLOSIONS; i++)
	{
		if (m_explosionAnim[i])
		{
			m_explosionAnim[i]->Draw();
		}
	}

	//Draw the amount of planets (with moons) that have been created
	for (int i = 0; i < TOTAL_PLANETS; i++)
	{
		m_planet[i]->Draw();
		m_moon[i]->Draw();
	}

	//Draw the amount of asteroids that have been created
	for (int i = 0; i < TOTAL_ASTEROIDS; i++)
	{
		m_asteroid[i]->Draw();
	}

	//set the 2D camera and render the heads-up display last
	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

	m_HUDCamera->Draw();

	for (size_t i = 0; i < TOTAL_HEARTS; i++)
	{
		if (m_lives[i]->IsVisible())
		{
			m_lives[i]->Draw();
		}
	}

	m_timerText->Draw();
	m_scoreText->Draw();

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that destroys all the game objects for the state
//------------------------------------------------------------------------------------------------------
void MainState::OnExit()
{
	for (int i = 0; i < TOTAL_HEARTS; i++)
	{
		m_lives[i]->~Lives();
	}

	for (int i = 0; i < TOTAL_ASTEROIDS; i++)
	{
		m_asteroid[i]->~Asteroid();
	}

	for (int i = 0; i < TOTAL_PLANETS; i++)
	{
		m_planet[i]->~Planet();
		m_moon[i]->~Moon();
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (m_enemy[i])
		{
			m_enemy[i]->~Enemy();
		}
	}

	//destroy the HUD, camera and grid objects
	m_HUD->Destroy();
	delete m_player;
	delete m_universe;
	delete m_HUD;
	delete m_HUDCamera;
	delete m_mainCamera;
}