#include <algorithm>
#include "OBB.h"
#include "DebugManager.h"
#include <gtx\projection.hpp>

OBB::OBB()
{
	//Set right, up and forward axis up to defaults
	m_upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	m_rightAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forwardAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	//Set scale to 1 unit
	m_scale = glm::vec3(1.0f);
}

void OBB::SetRotation(Quaternion rotation)
{
	m_rotation = rotation;
}

void OBB::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void OBB::SetScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void OBB::SetDimension(float width, float height, float depth)
{
	m_dimension = glm::vec3(width, height, depth);
}

bool OBB::isColliding(const OBB& secondBox) const
{
	//Temporary array to make looping easier
	OBB boxes[2];
	float projectionValue = 0.0f;

	glm::vec2 extents[2];
	glm::vec3 tempAxes[15];
	glm::vec3 normalizedAxis;

	//Place both boxes' axes into the tempAxes array
	//First box axes
	tempAxes[0] = m_upAxis;
	tempAxes[1] = m_rightAxis;
	tempAxes[2] = m_forwardAxis;

	//Second box axes
	tempAxes[3] = secondBox.m_upAxis;
	tempAxes[4] = secondBox.m_rightAxis;
	tempAxes[5] = secondBox.m_forwardAxis;

	tempAxes[6] = glm::cross(m_upAxis, secondBox.m_upAxis);
	tempAxes[7] = glm::cross(m_upAxis, secondBox.m_rightAxis);
	tempAxes[8] = glm::cross(m_upAxis, secondBox.m_forwardAxis);

	tempAxes[9] = glm::cross(m_rightAxis, secondBox.m_upAxis);
	tempAxes[10] = glm::cross(m_rightAxis, secondBox.m_rightAxis);
	tempAxes[11] = glm::cross(m_rightAxis, secondBox.m_forwardAxis);

	tempAxes[12] = glm::cross(m_forwardAxis, secondBox.m_upAxis);
	tempAxes[13] = glm::cross(m_forwardAxis, secondBox.m_rightAxis);
	tempAxes[14] = glm::cross(m_forwardAxis, secondBox.m_forwardAxis);


	//Loop through all 15 axes
	for (int i = 0; i < 15; i++)
	{
		//If any of the cross product results in a 0 axis, skip to next iteration
		if (tempAxes[i] == glm::vec3(0.0f)) continue;

		//First normalize the axis
		//Normalized first boxes temp axes
		normalizedAxis = glm::normalize(tempAxes[i]);

		//Reset the min and max extent values each time a new axis is tested
		//Set both min and max to the first projected corner of each box
		extents[0].x = extents[0].y = glm::dot(m_corners[0], normalizedAxis);
		extents[1].x = extents[1].y = glm::dot(secondBox.m_corners[0], normalizedAxis);

		//Assign both boxes into the boxes array
		boxes[0] = *this;
		boxes[1] = secondBox;

		//Loop through each box
		for (int j = 0; j < 2; j++)
		{
			//Loop through all 8 corners
			for (int k = 0; k < 8; k++)
			{
				//Project each corner onto the normalized axis
				projectionValue = glm::dot(boxes[j].m_corners[k], normalizedAxis);

				//Find the min and max values (std::min / std::max)
				//and store them in the extent's min and max array
				extents[j].x = std::min(projectionValue, extents[j].x);
				extents[j].y = std::max(projectionValue, extents[j].y);
			}
		}

		//If we find an SAT - return false
		if (!(extents[0].y > extents[1].x && extents[1].y > extents[0].x))
		{
			return false;
		}
	}

	//Otherwise we have collision!
	return true;
}

void OBB::Update()
{
	//Calculate half dimension
	m_halfdimension = (m_dimension * m_scale) / 2.0f;

	//Set right, up and forward axis up to defaults
	m_upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	m_rightAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forwardAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	//Adjust axes
	m_upAxis = m_rotation * m_upAxis * m_halfdimension.y;
	m_rightAxis = m_rotation * m_rightAxis * m_halfdimension.x;
	m_forwardAxis = m_rotation * m_forwardAxis * m_halfdimension.z;

	//Calculate corners (all clockwise)
	//Front face corners
	m_corners[0] = m_position + m_upAxis - m_rightAxis - m_forwardAxis;
	m_corners[1] = m_position + m_upAxis + m_rightAxis - m_forwardAxis;
	m_corners[2] = m_position - m_upAxis + m_rightAxis - m_forwardAxis;
	m_corners[3] = m_position - m_upAxis - m_rightAxis - m_forwardAxis;

	//Back face corners
	m_corners[4] = m_position + m_upAxis - m_rightAxis + m_forwardAxis;
	m_corners[5] = m_position + m_upAxis + m_rightAxis + m_forwardAxis;
	m_corners[6] = m_position - m_upAxis + m_rightAxis + m_forwardAxis;
	m_corners[7] = m_position - m_upAxis - m_rightAxis + m_forwardAxis;
}

void OBB::Draw()
{
	TheDebug::Instance()->DrawCube3D(m_dimension.x,
									 m_dimension.y,
									 m_dimension.z, 1.0f, 0.5f, 0.5f, 0.7f);
}
