#include <pangolin/camera.hpp>
#include <pgl-math/utils.hpp>
#include <pgl-math/algorithms.hpp>

#include <glad/glad.h>
#include <cmath>

#include <vector>

namespace pgl {

	Camera::Camera(
		pgl::float3 position,
		pgl::float3 up,
		float yaw, float pitch)
		: _position{position},
			_front{pgl::float3(0.0f, 0.0f, -1.0f)},
			_up{}, _right{}, _world_up{up},
			_yaw{yaw}, _pitch{pitch},
			_movement_speed{SPEED},
			_mouse_sensitivity{SENSITIVITY},
			_zoom{ZOOM}
	{
		update_camera_vectors();
	}

	Camera::Camera(
		float posX, float posY, float posZ,
		float upX, float upY, float upZ,
		float yaw, float pitch)
		: _position{posX, posY, posZ},
			_front{pgl::float3(0.0f, 0.0f, -1.0f)},
			_up{}, _right{}, _world_up{upX, upY, upZ},
			_yaw{yaw}, _pitch{pitch},
			_movement_speed{SPEED},
			_mouse_sensitivity{SENSITIVITY},
			_zoom{ZOOM}
	{
		update_camera_vectors();
	}

	pgl::float44 Camera::get_matrix_view() {
		return pgl::look_at(_position, _position + _front, _up);
	}

	void Camera::process_keyboard(CameraMovement direction, float deltaTime) {
		float velocity = _movement_speed * deltaTime;
		if (direction == CameraMovement::FORWARD)
			_position += _front * velocity;
		if (direction == CameraMovement::BACKWARD)
			_position -= _front * velocity;
		if (direction == CameraMovement::LEFT)
			_position -= _right * velocity;
		if (direction == CameraMovement::RIGHT)
			_position += _right * velocity;
	}

	void Camera::process_mouse_movement(
		float xoffset, float yoffset,
		bool constrainPitch)
	{
		xoffset *= _mouse_sensitivity;
		yoffset *= _mouse_sensitivity;

		_yaw   += xoffset;
		_pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch) {
			if (_pitch > 89.0f)
				_pitch = 89.0f;
			if (_pitch < -89.0f)
				_pitch = -89.0f;
		}

		// Update _front, _right and Up Vectors using the updated Euler angles
		update_camera_vectors();
	}

	void Camera::process_mouse_scroll(float yoffset) {
		_zoom -= yoffset;
		if (_zoom <= 1.0f)
			_zoom = 1.0f;
		if (_zoom >= 45.0f)
			_zoom = 45.0f;
	}

	void Camera::update_camera_vectors() {
		// Calculate the new m_front vector
		pgl::float3 front;
		front.x = std::cos(pgl::radians(_yaw)) * std::cos(pgl::radians(_pitch));
		front.y = std::sin(pgl::radians(_pitch));
		front.z = std::sin(pgl::radians(_yaw)) * std::cos(pgl::radians(_pitch));
		_front = pgl::normalize(front);
		// Also re-calculate the _right and Up vector

		// Normalize the vectors, because their length gets closer to 0 the more you
		// look up or down which results in slower movement.
		_right = pgl::normalize(pgl::cross(_front, _world_up));
		_up    = pgl::normalize(pgl::cross(_right, _front));
	}

} /* end of namespace pgl */
