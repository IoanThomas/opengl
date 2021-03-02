#include "camera.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

camera::camera(const glm::vec3& position, const unsigned int window_width, const unsigned int window_height, const float fov)
	: m_window_width(window_width), m_window_height(window_height), m_position(position), m_fov(fov)
{
	update_vectors();
	update_projection();
}

void camera::process_keyboard(const movement direction, const float delta_time)
{
	const auto velocity = speed * delta_time;

	switch (direction)
	{
	case movement::forward:
		m_position += m_front * velocity;
		break;
	case movement::backward:
		m_position -= m_front * velocity;
		break;
	case movement::left:
		m_position -= m_right * velocity;
		break;
	case movement::right:
		m_position += m_right * velocity;
		break;
	case movement::up:
		m_position += m_up * velocity;
		break;
	case movement::down:
		m_position -= m_up * velocity;
		break;
	}
}

void camera::process_mouse_movement(const float offset_x, const float offset_y, const bool constrain_pitch)
{
	const auto offset_x_relative = offset_x * sensitivity;
	const auto offset_y_relative = offset_y * sensitivity;

	m_yaw = std::fmod(m_yaw + offset_x_relative, 360.0f);
	m_pitch += offset_y_relative;

	if (constrain_pitch)
	{
		if (m_pitch > 89.0f)
		{
			m_pitch = 89.0f;
		}
		else if (m_pitch < -89.0f)
		{
			m_pitch = -89.0f;
		}
	}

	update_vectors();
}

void camera::process_mouse_scroll(const float offset_y)
{
	m_fov -= offset_y;

	if (m_fov < min_fov)
	{
		m_fov = min_fov;
	}
	else if (m_fov > max_fov)
	{
		m_fov = max_fov;
	}

	update_projection();
}

void camera::process_window_resized(const unsigned int window_width, const unsigned int window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;

	update_projection();
}

glm::mat4 camera::get_view_matrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void camera::update_vectors()
{
	glm::vec3 front;
	front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	front.y = std::sin(glm::radians(m_pitch));
	front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));

	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void camera::update_projection()
{
	const auto aspect_ratio = static_cast<float>(m_window_width) / m_window_height;

	m_projection = glm::perspective(glm::radians(m_fov), aspect_ratio, near_plane, far_plane);
}
