#include "CTexture.h"

CTexture::CTexture(const char *filename, unsigned int options)
{
	texture_id = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		options
	);
}


CTexture::~CTexture()
{
	glDeleteTextures(1, &texture_id);
}

void CTexture::apply()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}
