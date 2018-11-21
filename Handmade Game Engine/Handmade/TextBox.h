#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "GameObject.h"
#include "Text.h"

class TextBox : public GameObject
{
public:
	TextBox(float x, float y, float z, float size, const std::string& ID);
	virtual ~TextBox() {};

	void SetText(const std::string text);

	virtual bool Create() { return true; }
	virtual void Update() {}
	virtual void Draw();
	virtual void Destroy() {}

private:

	Text m_text;
	float m_size;
	glm::vec3 m_position;
	glm::mat4 m_transform;
};
#endif