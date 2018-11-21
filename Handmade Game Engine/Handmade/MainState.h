/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : December 2017

  -----------------------------------------------------------------------------------------------

- This game state controls the main state of the game. It consists of a main camera for the main
  view, and a debug grid object for orientation in the game world. Other game objects can be added
  to the vector as needed. The HUD, grid and main camera are treated as separate game objects and 
  not added to the game object vector. The grid is only drawn in debug mode and the camera needs 
  to be updated and drawn before any other game object so that the camera view is correct, therefore
  they need to be managed on their own. The camera also checks for when the game ends, and the HUD
  is manually drawn after all other game objects in the vector, because GUI objects are best drawn 
  last, which means it's better to have them treated as separate objects.

- The Update() function will update the main camera and all the game objects in the vector, as long
  as they are active. 

- The Draw() routine draws all the game objects in the vector, as long as they are active and 
  visible. It also draws the main camera before each game object in the loop. This is done because
  the camera sets up the view matrix and this needs to be done before each game object is drawn on
  screen. Based on if the game is in 2D or 3D mode, the Draw() function also sets up the projection
  to orthographic or perspective respectively. This is because in 3D mode the projection temporarily
  changes to 2D for the HUD, so it needs to be reset to perspective. In 2D mode it just remains 
  orthographic.

*/

#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "GameState.h"
#include "HUD.h"
#include "HUDCamera.h"
#include "MainCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Planet.h"
#include "Moon.h"
#include "Asteroid.h"
#include "Universe.h"
#include "Bullet.h"
#include "ExplosionAnim.h"
#include "TextBox.h"
#include "Lives.h"

class MainState : public GameState
{

public:
	MainState(GameState* state);
	virtual ~MainState() {}

public:
	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();

public:
	enum { EXPLOSION_1, EXPLOSION_2, EXPLOSION_3, EXPLOSION_4, EXPLOSION_5, EXPLOSION_6, EXPLOSION_7,
		   EXPLOSION_8, EXPLOSION_9, EXPLOSION_10, EXPLOSION_11, EXPLOSION_12, TOTAL_EXPLOSIONS };
	enum { ENEMY_1, ENEMY_2, ENEMY_3, ENEMY_4, ENEMY_5, ENEMY_6, ENEMY_7, ENEMY_8, ENEMY_9, ENEMY_10,
		   ENEMY_11, ENEMY_12, TOTAL_ENEMIES };
	enum { MARS, JUPITER, TOTAL_PLANETS };
	enum { MOON_1, MOON_2, TOTAL_MOONS };
	enum { ASTEROID_1, ASTEROID_2, ASTEROID_3, ASTEROID_4, ASTEROID_5, ASTEROID_6, ASTEROID_7,
		   ASTEROID_8, ASTEROID_9, ASTEROID_10, ASTEROID_11, ASTEROID_12, ASTEROID_13, TOTAL_ASTEROIDS };
	enum { HEART_1, HEART_2, HEART_3, TOTAL_HEARTS };

private:
	HUD* m_HUD;
	HUDCamera* m_HUDCamera;
	MainCamera* m_mainCamera;

	TextBox* m_scoreText;
	TextBox* m_timerText;
	Player* m_player;
	Rigidbody* m_rigidbody;
	Bullet* m_bullet;
	Universe* m_universe;

	ExplosionAnim* m_explosionAnim[TOTAL_EXPLOSIONS];
	Lives* m_lives[TOTAL_HEARTS];
	Enemy* m_enemy[TOTAL_ENEMIES];
	Planet* m_planet[TOTAL_PLANETS];
	Moon* m_moon[TOTAL_MOONS];
	Asteroid* m_asteroid[TOTAL_ASTEROIDS];
};
#endif