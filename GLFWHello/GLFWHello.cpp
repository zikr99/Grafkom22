#include <stdio.h>
#include "CCameraObject.h"
#include "CObjObject.h"

CCameraObject default_camera;

double last_xpos, last_ypos;
double xoffset, yoffset;
bool first_iteration = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
		default_camera.position.z = default_camera.position.z - 1.0f;
	/*else if (key == GLFW_KEY_A && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
		move camera to the left
	else if (key == GLFW_KEY_D && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
		move camera to the right */
	else if (key == GLFW_KEY_S && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
		default_camera.position.z = default_camera.position.z + 1.0f;

	
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1200, 800, "Grafkom 22b", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	CObjMesh *mesh_skull = new CObjMesh("D:\\Skull\\12140_Skull_v3_L2.obj");
	CTexture *texture_skull = new CTexture("D:\\Skull\\Skull.jpg",
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	CObjObject *object_skull = new CObjObject(mesh_skull, texture_skull);
	object_skull->position.y = -20.0f;
	object_skull->position.z = -40.0f;
	object_skull->rotation.x = glm::radians(-90.0f);
	object_skull->scale = glm::vec3(1.5f, 1.2f, 1.2f);

	float ry = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos); //polling

		if (first_iteration)
		{
			last_xpos = xpos;
			last_ypos = ypos;

			first_iteration = false;
		}
		else
		{
			xoffset = xpos - last_xpos;
			yoffset = ypos - last_ypos;

			default_camera.rotation.y = default_camera.rotation.y - glm::radians(xoffset*0.1f);
			default_camera.rotation.x = default_camera.rotation.x - glm::radians(yoffset*0.1f);

			last_xpos = xpos;
			last_ypos = ypos;
		}

		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Requires opengl32.lib

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.5f, 1.5f, -1.0f, 1.0f, 1.0f, 1000.0f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//Update
		default_camera.calcmat();

		//And then draw
		object_skull->rotation.y = ry;
		ry += glm::radians(1.0f);

		object_skull->calcmat();
		object_skull->texture->apply();
		object_skull->draw(); // the inverse of the transf. matrix of the camera has to be applied here somehow

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete object_skull;
	delete mesh_skull;
	delete texture_skull;

	glfwTerminate();
	return 0;
}