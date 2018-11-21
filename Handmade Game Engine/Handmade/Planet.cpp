#include "Planet.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"
#include "GameObject.h"

int Planet::count = 0;

Planet::Planet(float x, float y, float z)
{
	//m_angle = 0.0f;
	m_planetPosition = glm::vec3(x, y, z);

	if (count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Planet.obj", "PLANET");
		m_model.LoadTexture("Assets\\Textures\\Planet_Diffuse.png", "PLANET");
	}
	
	else
	{
	m_model.SetBuffer("PLANET");
	m_model.SetTexture("PLANET");
	}

	count++;
}

Planet::~Planet()
{
}

void Planet::Update()
{
	/*m_angle += 0.01f;

	m_planetPosition.x = cos(m_angle) * 1.5;
	m_planetPosition.z = sin(m_angle) * 1.5;*/
}

void Planet::Draw()
{
	//Reset
	m_transform = glm::mat4(1.0f);

	//Move
	m_transform = glm::translate(m_transform, m_planetPosition);

	//Render
	GameObject::setMatrix(m_transform);
	GameObject::SendToShader(false, true);
	m_model.Draw();
}