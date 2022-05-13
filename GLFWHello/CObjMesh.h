#pragma once
#include "fast_obj.h"

class CObjMesh
{
protected:
	void load(const char *filename)
	{
		if (data != NULL)
			fast_obj_destroy(data);

		data = fast_obj_read(filename);
	}

public:
	fastObjMesh *data;

	CObjMesh(const char *filename);
	~CObjMesh();
};

