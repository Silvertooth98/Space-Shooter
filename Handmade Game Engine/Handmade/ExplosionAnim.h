#ifndef EXPLOSIONANIM_H
#define EXPLOSIONANIM_H

#include "GameObject.h"
#include "Animation.h"
#include "Audio.h"

class ExplosionAnim : public GameObject
{
public:
	ExplosionAnim();
	virtual ~ExplosionAnim() {};

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	void SetPosition(glm::vec3 position) { m_position = position; }

private:

	glm::vec3 m_position;
	glm::mat4 m_transform;
	Animation m_animation;

	static int s_totalEXP;

	Audio m_sfx;
};
#endif