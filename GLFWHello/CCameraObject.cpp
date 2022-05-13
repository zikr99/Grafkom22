#include "CCameraObject.h"

CCameraObject::CCameraObject()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

CCameraObject::~CCameraObject()
{
}

void CCameraObject::calcmat()
{
	glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 Rr = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Rp = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 R = Ry*(Rp*Rr);
	mattransform = T*R;

	invmattransform = glm::inverse(mattransform);
}

void CCameraObject::setLookDirection(glm::vec3 lookdir)
{
}

void CCameraObject::setUpVector(glm::vec3 upvec)
{
}
