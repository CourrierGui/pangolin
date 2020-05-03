#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
  public:
    // Camera Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;

    // Euler Angles
    float m_yaw;
    float m_pitch;

    // Camera options
    float m_movement_speed;
    float m_mouse_sensitivity;
    float m_zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw          = YAW,
           float pitch        = PITCH)
      : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(SPEED),
      m_mouse_sensitivity(SENSITIVITY),
      m_zoom(ZOOM)
    {
      m_position = position;
      m_world_up = up;
      m_yaw      = yaw;
      m_pitch    = pitch;
      update_camera_vectors();
    }

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw, float pitch)
      : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(SPEED),
      m_mouse_sensitivity(SENSITIVITY),
      m_zoom(ZOOM) 
    {
        m_position = glm::vec3(posX, posY, posZ);
        m_world_up = glm::vec3(upX, upY, upZ);
        m_yaw = yaw;
        m_pitch = pitch;
        update_camera_vectors();
      }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 get_matrix_view() {
      return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void process_keyboard(Camera_Movement direction, float deltaTime) {
      float velocity = m_movement_speed * deltaTime;
      if (direction == FORWARD)
        m_position += m_front * velocity;
      if (direction == BACKWARD)
        m_position -= m_front * velocity;
      if (direction == LEFT)
        m_position -= m_right * velocity;
      if (direction == RIGHT)
        m_position += m_right * velocity;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
      xoffset *= m_mouse_sensitivity;
      yoffset *= m_mouse_sensitivity;

      m_yaw   += xoffset;
      m_pitch += yoffset;

      // Make sure that when pitch is out of bounds, screen doesn't get flipped
      if (constrainPitch) {
        if (m_pitch > 89.0f)
          m_pitch = 89.0f;
        if (m_pitch < -89.0f)
          m_pitch = -89.0f;
      }

      // Update m_front, m_right and Up Vectors using the updated Euler angles
      update_camera_vectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void process_mouse_scroll(float yoffset) {
      m_zoom -= yoffset;
      if (m_zoom <= 1.0f)
        m_zoom = 1.0f;
      if (m_zoom >= 45.0f)
        m_zoom = 45.0f;
    }

  private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors() {
      // Calculate the new m_front vector
      glm::vec3 front;
      front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
      front.y = std::sin(glm::radians(m_pitch));
      front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
      m_front = glm::normalize(front);
      // Also re-calculate the m_right and Up vector
      m_right = glm::normalize(glm::cross(m_front, m_world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
      m_up    = glm::normalize(glm::cross(m_right, m_front));
    }
};
