#pragma once

#include <glm/glm.hpp>

#include "camera_movement.h"

class camera
{
public:
	camera(const glm::vec3& position = glm::vec3(0.0f), const float yaw = -90.0f, const float pitch = 0.0f);

	void process_keyboard(const camera_movement direction, const float delta_time);
	void process_mouse_movement(const float offset_x, const float offset_y, const bool constrain_pitch = true);
	void process_mouse_scroll(const float offset_y);

	glm::mat4 get_view_matrix() const;

	glm::vec3 get_position() const { return m_position; }
	float get_zoom() const { return m_zoom; }

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_yaw;
	float m_pitch;

	float m_speed = 2.5f;
	float m_sensitivity = 0.1f;
	float m_zoom = 45.0f;

	void update_vectors();
};
