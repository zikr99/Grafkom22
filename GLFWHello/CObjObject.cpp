#include "CObjObject.h"

CObjObject::CObjObject(CObjMesh *m, CTexture *t)
{
	mesh = m;
	texture = t;

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

CObjObject::~CObjObject()
{
}

void CObjObject::drawGroup(int n)
{
	
	glm::mat4 overalltransform = default_camera.invmattransform*mattransform;

	// apply transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(overalltransform));    

	const fastObjGroup& grp = mesh->data->groups[n];

	int ii = 0;

	for (int i = 0; i < grp.face_count; i++)
	{
		int num_vertices = mesh->data->face_vertices[i + grp.face_offset];
		//printf("%d\n", num_vertices);

		if (num_vertices == 3)
			glBegin(GL_TRIANGLES);
		else if (num_vertices == 4)
			glBegin(GL_QUADS);

		for (int v = 0; v < num_vertices; v++)
		{
			fastObjIndex ind = mesh->data->indices[ii + grp.index_offset];

			float x = mesh->data->positions[3*ind.p];
			float y = mesh->data->positions[3 * ind.p + 1];
			float z = mesh->data->positions[3*ind.p + 2];

			float s = mesh->data->texcoords[2*ind.t];
			float t = mesh->data->texcoords[2*ind.t + 1];

			glTexCoord2f(s, t); glVertex3f(x, y, z);

			ii++;
		}

		glEnd();
	}
}

void CObjObject::draw()
{
	int num_groups = mesh->data->group_count;

	for (int i = 0; i < num_groups; i++)
		drawGroup(i);
}

void CObjObject::calcmat()
{
	glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 Rr = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Rp = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 R = Ry*(Rp*Rr);
	glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);
	mattransform = T*(R*S);
}
