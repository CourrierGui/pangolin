#include <pangolin/camera.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <vector>

Camera::Camera(glm::vec3 position,
               glm::vec3 up,
               float yaw, float pitch)
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

Camera::Camera(
  float posX, float posY, float posZ,
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

glm::mat4 Camera::get_matrix_view() {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::process_keyboard(Camera_Movement direction, float deltaTime) {
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

void Camera::process_mouse_movement(
  float xoffset, float yoffset,
  GLboolean constrainPitch)
{
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

void Camera::process_mouse_scroll(float yoffset) {
  m_zoom -= yoffset;
  if (m_zoom <= 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >= 45.0f)
    m_zoom = 45.0f;
}

void Camera::update_camera_vectors() {
  // Calculate the new m_front vector
  glm::vec3 front;
  front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
  front.y = std::sin(glm::radians(m_pitch));
  front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);
  // Also re-calculate the m_right and Up vector

  // Normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement.
  m_right = glm::normalize(glm::cross(m_front, m_world_up));
  m_up    = glm::normalize(glm::cross(m_right, m_front));
}
