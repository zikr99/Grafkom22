#include "CObjMesh.h"

CObjMesh::CObjMesh(const char *filename) : data(NULL)
{
	if (filename != NULL)
		load(filename);
}

CObjMesh::~CObjMesh()
{
	if (data != NULL)
		fast_obj_destroy(data);
}
