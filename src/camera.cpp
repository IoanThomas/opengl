#include "camera.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

camera::camera(const glm::vec3& position, const float yaw, const float pitch)
	: m_position(position), m_yaw(yaw), m_pitch(pitch)
{
	update_vectors();
}

void camera::process_keyboard(const camera_movement direction, const float delta_time)
{
	const auto velocity = m_speed * delta_time;

	switch (direction)
	{
	case camera_movement::forward:
		m_position += m_front * velocity;
		break;
	case camera_movement::backward:
		m_position -= m_front * velocity;
		break;
	case camera_movement::left:
		m_position -= m_right * velocity;
		break;
	case camera_movement::right:
		m_position += m_right * velocity;
		break;
	}
}

void camera::process_mouse_movement(const float offset_x, const float offset_y, const bool constrain_pitch)
{
	const auto offset_x_relative = offset_x * m_sensitivity;
	const auto offset_y_relative = offset_y * m_sensitivity;

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
	m_zoom -= offset_y;

	if (m_zoom < 1.0f)
	{
		m_zoom = 1.0f;
	}
	else if (m_zoom > 45.0f)
	{
		m_zoom = 45.0f;
	}
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
