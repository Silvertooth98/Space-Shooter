#include "Moon.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "DebugManager.h"
#include "InputManager.h"
#include "GameObject.h"

int Moon::count = 0;

Moon::Moon(float x, float y, float z)
{
	m_angle = 0.0f;
	m_moonPosition = glm::vec3(x, y, z);

	if (count == 0)
	{
		m_model.LoadModel("Assets\\Models\\Planet.obj", "MOON");
		m_model.LoadTexture("Assets\\Textures\\Planet_Diffuse.png", "MOON");
	}

	else
	{
		m_model.SetBuffer("MOON");
		m_model.SetTexture("MOON");
	}

	count++;
}

Moon::~Moon()
{
}

void Moon::Update()
{
	m_angle += 0.01f;

	m_orbitPosition.x = cos(m_angle) * 6;
	m_orbitPosition.y = sin(m_angle) * 6;
	m_orbitPosition.z = -cos(m_angle) * 6;
}

void Moon::Draw()
{
	//Reset
	m_transform = glm::mat4(1.0f);

	//Move
	glm::vec3 finalPos = m_moonPosition + m_orbitPosition;
	m_transform = glm::translate(m_transform, finalPos);
	m_transform = glm::scale(m_transform, glm::vec3(0.2f, 0.2f, 0.2f));

	//Render
	GameObject::setMatrix(m_transform);
	GameObject::SendToShader(false, true);
	m_model.Draw();
}