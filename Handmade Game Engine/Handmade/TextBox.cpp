#include "TextBox.h"

TextBox::TextBox(float x, float y, float z, float size, const std::string & ID)
{
	m_position = glm::vec3(x, y, z);
	m_size = size;
	m_text.Create(ID);

	static bool s_isFontLoaded = false;

	if (!s_isFontLoaded)
	{
		m_text.LoadTexture("Assets\\Font\\Calibri.png", "FONT");
		s_isFontLoaded = true;
	}

	else
	{
		m_text.SetTexture("FONT");
	}

}

void TextBox::SetText(const std::string text)
{
	m_text.SetText(text);
}

void TextBox::Draw()
{
	//reset the transformation
	m_transform = glm::mat4(1.0f);

	//do the position and scale
	m_transform = glm::translate(m_transform, m_position);
	m_transform = glm::scale(m_transform, glm::vec3(m_size));

	//set the engine matrix and render
	GameObject::setMatrix(m_transform);
	GameObject::SendToShader(false, true);
	m_text.Draw();
}
