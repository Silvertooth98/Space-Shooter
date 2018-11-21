#ifndef LASERBEAM_H
#define LASERBEAM_H

#include <glm.hpp>
#include "Quaternion.h"
#include "GameObject.h"
#include "OBB.h"

class Laserbeam : public GameObject
{
public:
	Laserbeam(float x, float y, float z, glm::vec3 direction);
	virtual ~Laserbeam();

	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

	OBB& getBound() { return m_bound; }
	glm::vec3 GetPos() { return m_position; }

private:
	float m_velocity;

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::mat4 m_transform;

	Quaternion m_rotationTotal;

	static int s_count;
	Model m_model;

	OBB m_bound;
};
#endif