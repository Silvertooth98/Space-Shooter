#ifndef LIVES_H
#define LIVES_H

#include "GameObject.h"
#include "Text.h"

class Lives : public GameObject
{
public:
	Lives(glm::vec3 position);
	virtual ~Lives();

	virtual bool Create() { return true; }
	virtual void Update() {}
	virtual void Draw();
	virtual void Destroy() {}

	void updatePos();
	glm::vec3 setPos(glm::vec3 position);

private:

	Sprite m_sprite;

	static int s_total;

	Text m_text;
	float m_size;
	glm::vec3 m_position;
	glm::mat4 m_transform;
};
#endif