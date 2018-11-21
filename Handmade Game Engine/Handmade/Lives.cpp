#include "Lives.h"

int Lives::s_total = 0;

Lives::Lives(glm::vec3 position)
{
	if (s_total == 0)
	{
		m_sprite.Create("Heart");
		m_sprite.LoadTexture("Assets\\Sprites\\Heart.png", "LivesHeart");
	}
	else
	{
		m_sprite.SetBuffer("Heart");
		m_sprite.SetTexture("LivesHeart");
	}

	s_total++;

	m_position = position;
}

Lives::~Lives()
{
}

void Lives::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position);
	m_transform = glm::scale(m_transform, glm::vec3(100.0f, 100.0f, 0.0f));
	GameObject::setMatrix(m_transform);

	GameObject::SendToShader(false, true);

	m_sprite.Draw();
}

void Lives::updatePos()
{
	m_position.y = -600;
}

glm::vec3 Lives::setPos(glm::vec3 position)
{
	m_position = position;

	return position;
}
