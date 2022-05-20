#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CCameraObject
{
public:
	glm::vec3 position;
	glm::vec3 scale; // will not be used, just for compatibility with other 3D objects
	glm::vec3 rotation;

	glm::mat4 mattransform;
	glm::mat4 invmattransform;
	void calcmat();

	void setLookTowards(glm::vec3 lookdir, glm::vec3 upvec);
	glm::vec3 getLookDirection();

	CCameraObject();
	~CCameraObject();
};

extern CCameraObject default_camera;

