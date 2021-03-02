#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "opengl/shader.h"

#include "model_cache.h"
#include "camera.h"
#include "opengl/vertex_array.h"
#include "opengl/vertex_buffer.h"

#include "entity_renderer.h"
#include "texture_cache.h"

static camera cam(glm::vec3(0.0f, 0.0f, 3.0f), 1280, 720);
static auto last_x = 640.0f;
static auto last_y = 360.0f;
static auto first_mouse = true;

static auto delta_time = 0.0f;
static auto last_frame = 0.0f;

void glfw_error_callback(const int error, const char* description)
{
	std::cerr << "GLFW error " << error << ": " << description << '\n';
}

void glfw_resize_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);

	cam.process_window_resized(width, height);
}

void glfw_mouse_callback(GLFWwindow* window, const double pos_x, const double pos_y)
{
	if (first_mouse)
	{
		last_x = static_cast<float>(pos_x);
		last_y = static_cast<float>(pos_y);

		first_mouse = false;
	}

	const auto offset_x = static_cast<float>(pos_x) - last_x;
	const auto offset_y = last_y - static_cast<float>(pos_y);

	last_x = static_cast<float>(pos_x);
	last_y = static_cast<float>(pos_y);

	cam.process_mouse_movement(offset_x, offset_y);
}

void glfw_scroll_callback(GLFWwindow* window, const double offset_x, const double offset_y)
{
	cam.process_mouse_scroll(static_cast<float>(offset_y));
}

void process_input(GLFWwindow* window)
{
	const float modifier = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 10.0f : 1.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::forward, modifier, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::backward, modifier, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::left, modifier, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::right, modifier, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::up, modifier, delta_time);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		cam.process_keyboard(camera::movement::down, modifier, delta_time);
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
	//glClearColor(0.03f, 0.03f, 0.03f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	light sun({0.0f, 10.0f, 0.0f});
	std::vector<light> lights;

	entity_renderer renderer;
	auto& sword_entity = renderer.create_entity("sword", glm::vec3(-1.0f, 0.0f, 0.0f));
	auto& phone_entity = renderer.create_entity("phone", glm::vec3(0.0f, 0.0f, 0.0f));
	auto& lantern_entity = renderer.create_entity("lantern", glm::vec3(1.0f, 0.0f, 0.0f));
	auto& plane_entity = renderer.create_entity("plane", glm::vec3(0.0f, 0.0f, -1.0f));
	auto& ball_entity = renderer.create_entity("ball", glm::vec3(1.5f, 0.0f, 1.0f));

	sword_entity.scale = glm::vec3(0.1f);

	phone_entity.scale = glm::vec3(0.25f);
	phone_entity.rotation.x = 90.0f;

	lantern_entity.scale = glm::vec3(0.5f);

	plane_entity.scale = glm::vec3(10.0f);
	plane_entity.rotation.x = 90.0f;

	ball_entity.scale = glm::vec3(0.5f);

	while (!glfwWindowShouldClose(window))
	{
		const auto current_time = static_cast<float>(glfwGetTime());
		delta_time = current_time - last_frame;
		last_frame = current_time;

		static auto total_time = 0.0f;
		total_time += delta_time;
		if (total_time >= 1.0f)
		{
			std::cout << "FPS: " << (1.0f / delta_time) << '\n';
			total_time = 0.0f;
		}

		process_input(window);

		sword_entity.rotation.x += (delta_time * 100.0f);
		lantern_entity.rotation.y += (delta_time * 50.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render(cam, sun, lights);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
