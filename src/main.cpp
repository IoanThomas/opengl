#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "opengl/shader.h"

#include "model_loader.h"
#include "camera.h"
#include "opengl/vertex_array.h"
#include "opengl/vertex_buffer.h"

#include "renderer.h"
#include "texture_cache.h"

static camera cam(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f);
static float last_x = 640;
static float last_y = 360;
bool first_mouse = true;

static float delta_time = 0.0f;
static float last_frame = 0.0f;

void glfw_error_callback(const int error, const char* description)
{
	std::cerr << "GLFW error " << error << ": " << description << '\n';
}

void glfw_resize_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void glfw_mouse_callback(GLFWwindow* window, const double pos_x, const double pos_y)
{
	if (first_mouse)
	{
		last_x = pos_x;
		last_y = pos_y;

		first_mouse = false;
	}

	const auto offset_x = pos_x - last_x;
	const auto offset_y = last_y - pos_y;

	last_x = pos_x;
	last_y = pos_y;

	cam.process_mouse_movement(offset_x, offset_y);
}

void glfw_scroll_callback(GLFWwindow* window, const double offset_x, const double offset_y)
{
	cam.process_mouse_scroll(offset_y);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.process_keyboard(camera_movement::forward, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.process_keyboard(camera_movement::backward, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.process_keyboard(camera_movement::left, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.process_keyboard(camera_movement::right, delta_time);
	}
}

int main()
{
	constexpr int width = 1280;
	constexpr int height = 720;

	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
	{
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 2;
	}

	glfwSetFramebufferSizeCallback(window, glfw_resize_callback);
	glfwSetCursorPosCallback(window, glfw_mouse_callback);
	glfwSetScrollCallback(window, glfw_scroll_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialise GLAD!\n";

		glfwTerminate();
		return 3;
	}

	glViewport(0, 0, width, height);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << '\n';
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << '\n';

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	renderer renderer;
	renderer.load_model("sword");

	while (!glfwWindowShouldClose(window))
	{
		const float current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;

		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.set(cam);
		renderer.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
