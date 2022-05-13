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
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 mattransform;
	glm::mat4 invmattransform;
	void calcmat();

	void setLookDirection(glm::vec3 lookdir);
	void setUpVector(glm::vec3 upvec);

	CCameraObject();
	~CCameraObject();
};

extern CCameraObject default_camera;

