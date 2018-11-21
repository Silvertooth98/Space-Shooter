#ifndef QUATERNION_H
#define QUATERNION_H

#include <glm.hpp>

class Quaternion
{
public:
	Quaternion();
	~Quaternion();

	double GetAngle();
	glm::vec3 GetAxis();

	void SetRotation(double angle, const glm::vec3& axis);
	void SetRotation(double angleX, double angleY, double angleZ);

	Quaternion operator*(const Quaternion& righthandside);
	glm::vec3 operator*(const glm::vec3& rhs);

	glm::mat4 ConvertToMatrix();

	double Length();
	double LengthSquared();

	Quaternion Congugate();
	Quaternion Normalize();

public:
	double w;
	double x;
	double y;
	double z;
};
#endif