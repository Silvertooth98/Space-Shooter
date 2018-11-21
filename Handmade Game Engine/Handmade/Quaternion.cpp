#include "Quaternion.h"
#include <iostream>
#include <math.h>
#include <iomanip>

//constructor that assigns our quaternion to identity
Quaternion::Quaternion()
{
	w = 1.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Quaternion::~Quaternion()
{
}

double Quaternion::GetAngle()
{
	return glm::degrees(acos(w) * 2);
}

glm::vec3 Quaternion::GetAxis()
{
	return glm::normalize(glm::vec3(x, y, z));
}

void Quaternion::SetRotation(double angle, const glm::vec3 & axis)
{
	//w = cos(angle/2)
	//x = axisX * sin(angle/2)
	//y = axisY * sin(angle/2)
	//z = axisZ * sin(angle/2)

	//first normalize the axis of rotation
	glm::vec3 normAxis = glm::normalize(axis);

	//assign the quaternion components based on a formula
	w = cos(glm::radians(angle) / 2);
	x = normAxis.x * sin(glm::radians(angle) / 2);
	y = normAxis.y * sin(glm::radians(angle) / 2);
	z = normAxis.z * sin(glm::radians(angle) / 2);
}

void Quaternion::SetRotation(double angleX, double angleY, double angleZ)
{
	double COS_X = cos(glm::radians(angleX) / 2);
	double COS_Y = cos(glm::radians(angleY) / 2);
	double COS_Z = cos(glm::radians(angleZ) / 2);

	double SIN_X = sin(glm::radians(angleX) / 2);
	double SIN_Y = sin(glm::radians(angleY) / 2);
	double SIN_Z = sin(glm::radians(angleZ) / 2);

	//taking 3 Euler angles and converting them into quaternions
	w = COS_Z * COS_X * COS_Y + SIN_Z * SIN_X * SIN_Y;
	x = COS_Z * SIN_X * COS_Y + SIN_Z * COS_X * SIN_Y;
	y = COS_Z * COS_X * SIN_Y - SIN_Z * SIN_X * COS_Y;
	z = SIN_Z * COS_X * COS_Y - COS_Z * SIN_X * SIN_Y;

}

Quaternion Quaternion::operator*(const Quaternion & righthandside)
{
	Quaternion result;

	result.w = ((w * righthandside.w) - (x * righthandside.x) - (y * righthandside.y) - (z * righthandside.z));
	result.x = ((w * righthandside.x) + (x * righthandside.w) + (y * righthandside.z) - (z * righthandside.y));
	result.y = ((w * righthandside.y) + (y * righthandside.w) + (z * righthandside.x) - (x * righthandside.z));
	result.z = ((w * righthandside.z) + (z * righthandside.w) + (x * righthandside.y) - (y * righthandside.x));

	return result;
}

glm::vec3 Quaternion::operator*(const glm::vec3& rhs)
{
	//check if vector is null and return passed vector if null
	if (rhs == glm::vec3(0.0f))
	{
		return rhs;
	}
	
	//normalize the passed vector and store that in a temp vector
	glm::vec3 normVec = glm::normalize(rhs);

	//create a temp quaternion out of passed vector
	Quaternion vecQuat;
	vecQuat.w = 0.0f;
	vecQuat.x = normVec.x;;
	vecQuat.y = normVec.y;
	vecQuat.z = normVec.z;

	//create a result vector to perform calculations using a specific algorithm
	//Congugate is the inverse of the (x, y, z)
	Quaternion result = (*this) * vecQuat * Congugate();

	//turn result quaternion back into a vector
	return glm::vec3(result.x, result.y, result.z);
}

glm::mat4 Quaternion::ConvertToMatrix()
{
	glm::mat4 result;

	result[0][0] = 1.0f - 2.0f * (y * y + z * z);
	result[0][1] = 2.0f * (x * y + z * w);
	result[0][2] = 2.0f * (x * z - y * w);
	result[0][3] = 0.0f;

	result[1][0] = 2.0f * (x * y - z * w);
	result[1][1] = 1.0f - 2.0f * (x * x + z * z);
	result[1][2] = 2.0f * (z * y + x * w);
	result[1][3] = 0.0f;

	result[2][0] = 2.0f * (x * z + y * w);
	result[2][1] = 2.0f * (y * z - x * w);
	result[2][2] = 1.0f - 2.0f * (x * x + y * y);
	result[2][3] = 0.0f;

	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = 0.0f;
	result[3][3] = 1.0f;

	return result;
}

double Quaternion::Length()
{
	return sqrt(LengthSquared());
}

double Quaternion::LengthSquared()
{
	return ((w * w) + (x * x) + (y * y) + (z * z));
}

Quaternion Quaternion::Congugate()
{
	Quaternion result;

	result.w = w;
	result.x = -x;
	result.y = -y;
	result.z = -z;

	return result;
}

Quaternion Quaternion::Normalize()
{
	Quaternion result;

	double length = Length();
	
	result.w /= length;
	result.x /= length;
	result.y /= length;
	result.z /= length;

	return result;
}