#pragma once
#include <GLFW/glfw3.h>
#include <SOIL.h>

class CTexture
{
protected:
	GLuint texture_id;

public:
	CTexture(const char *filename, unsigned int options);
	~CTexture();

	void apply();
};

