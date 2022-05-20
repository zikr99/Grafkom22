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

void CCameraObject::setLookTowards(glm::vec3 lookdir, glm::vec3 upvec)
{
	float rxz = sqrt(lookdir.x*lookdir.x + lookdir.z*lookdir.z);
	rotation.x = atan2(lookdir.y, rxz);

	float alpha = atan2(lookdir.z, lookdir.x);
	rotation.y = glm::radians(-90.0f) - alpha;

	glm::vec3 yvec = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 t = glm::cross(glm::cross(lookdir, yvec), lookdir);
	
	float magl = glm::length(lookdir);
	float magt = glm::length(t);
	float magu = glm::length(upvec);

	glm::vec3 c = glm::cross(t, upvec)/(magt*magu);

	double cdotl = glm::dot(c, lookdir);
	
	rotation.z = asin(cdotl/magl);
}

glm::vec3 CCameraObject::getLookDirection()
{
	glm::vec4 defdir = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

	glm::mat4 Rp = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 R = Ry*Rp;
	
	glm::vec4 lookdir = R*defdir;
	return glm::vec3(lookdir.x, lookdir.y, lookdir.z);
}
