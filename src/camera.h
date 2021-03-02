#pragma once

#include <glm/glm.hpp>

class camera
{
public:
	enum class movement
	{
		forward,
		backward,
		left,
		right,
		up,
		down
	};

	static constexpr auto near_plane = 0.1f;
	static constexpr auto far_plane = 100.0f;
	static constexpr auto speed = 2.5f;
	static constexpr auto sensitivity = 0.1f;
	static constexpr auto max_fov = 90.0f;
	static constexpr auto min_fov = 30.0f;

	camera(const glm::vec3& position, const unsigned int window_width, const unsigned int window_height, const float fov = 45.0f);

	void process_keyboard(const movement direction, const float delta_time);
	void process_mouse_movement(const float offset_x, const float offset_y, const bool constrain_pitch = true);
	void process_mouse_scroll(const float offset_y);
	void process_window_resized(const unsigned int window_width, const unsigned int window_height);

	glm::mat4 get_view_matrix() const;
	glm::mat4 get_projection_matrix() const { return m_projection; };

	glm::vec3 get_position() const { return m_position; }
	float get_fov() const { return m_fov; }

private:
	glm::mat4 m_projection;
	unsigned int m_window_width;
	unsigned int m_window_height;

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_fov;
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

	void update_vectors();
	void update_projection();
};
