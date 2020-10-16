#pragma once

#include <glad/glad.h>
#include <cmath>
#include <pgl-math/vector.hpp>
#include <pgl-math/impl/matrix.hpp>

#include <vector>

/*
 * Defines several possible options for camera movement. Used as abstraction to
 * stay away from window-system specific input methods.
 */
enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
constexpr float YAW         = -90.0f;
constexpr float PITCH       =  0.0f;
constexpr float SPEED       =  2.5f;
constexpr float SENSITIVITY =  0.1f;
constexpr float ZOOM        =  45.0f;

namespace pgl {

	/*
	 * An abstract camera class that processes input and calculates the
	 * corresponding Euler Angles, Vectors and Matrices for use in OpenGL.
	 */
	class Camera {
			/*
			 * Constructor with vectors
			 */
			Camera(
				pgl::float3 position = pgl::float3(0.0f, 0.0f, 0.0f),
				pgl::float3 up       = pgl::float3(0.0f, 1.0f, 0.0f),
				float yaw            = YAW,
				float pitch          = PITCH
			);

			/*
			 * Constructor with scalar values
			 */
			Camera(
				float posX, float posY, float posZ,
				float upX,  float upY,  float upZ,
				float yaw,  float pitch
			);

			/*
			 * Returns the view matrix calculated using Euler Angles and the LookAt
			 * Matrix
			 */
			pgl::float44 get_matrix_view();

			/*
			 * Processes input received from any keyboard-like input system. Accepts
			 * input parameter in the form of camera defined ENUM (to abstract it from
			 * windowing systems)
			 */
			void process_keyboard(CameraMovement direction, float deltaTime);

			/*
			 * Processes input received from a mouse input system. Expects the offset
			 * value in both the x and y direction.
			 */
			void process_mouse_movement(
				float xoffset, float yoffset,
				bool constrainPitch=true
			);

			/*
			 * Processes input received from a mouse scroll-wheel event. Only requires
			 * input on the vertical wheel-axis
			 */
			void process_mouse_scroll(float yoffset);

		private:
			/*
			 * Calculates the front vector from the Camera's (updated) Euler Angles
			 */
			void update_camera_vectors();

		public:
			// Camera Attributes
			pgl::float3 _position;
			pgl::float3 _front;
			pgl::float3 _up;
			pgl::float3 _right;
			pgl::float3 _world_up;

			// Euler Angles
			float _yaw;
			float _pitch;

			// Camera options
			float _movement_speed;
			float _mouse_sensitivity;
			float _zoom;
	};

} /* end of namespace pgl */
