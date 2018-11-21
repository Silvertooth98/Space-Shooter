#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "GameObject.h"
#include <glm.hpp>
#include "Audio.h"

class Universe : public GameObject
{
public:
	Universe();
	~Universe();

	virtual bool Create() { return true; }
	virtual void Update() {};
	virtual void Draw();
	virtual void Destroy() {};

private:

	Model m_model;
	Audio m_music;

	glm::mat4 m_transform;
};
#endif