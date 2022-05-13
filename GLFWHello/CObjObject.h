#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include "CCameraObject.h"
#include "CObjMesh.h"
#include "CTexture.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CObjObject
{
public:
	CObjMesh *mesh;
	CTexture *texture;
	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 mattransform;
	void calcmat();

	CObjObject(CObjMesh *m, CTexture *t);
	~CObjObject();

	void drawGroup(int n);
	void draw();

};

