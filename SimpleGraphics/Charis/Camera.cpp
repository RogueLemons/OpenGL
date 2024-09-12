#include "Camera.h"
#include "Utility.h"

// Libraries
#include <glm/gtc/matrix_transform.hpp>

namespace Charis {

	Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch, float fov)
		: Position(position)
		, Yaw(yaw)
		, Pitch(pitch)
		, Options{}
		, m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
		, m_Fov(fov)
	{
		ProcessZoom(0.0f);
		UpdateCameraCoordinateSystem();
	}

	Camera::Camera(CameraOptions options, glm::vec3 position, float yaw, float pitch, float fov)
		: Options(options)
		, Position(position)
		, Yaw(yaw)
		, Pitch(pitch)
		, m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
		, m_Fov(fov)
	{
		ProcessZoom(0.0f);
		UpdateCameraCoordinateSystem();
	}

	glm::mat4 Camera::ViewMatrix() const
	{
		return glm::lookAt(Position, Position + m_Front, m_Up);
	}

	glm::mat4 Camera::ProjectionMatrix() const
	{
		float aspectRatio = static_cast<float>(Utility::GetWindowDimensions().Width) / static_cast<float>(Utility::GetWindowDimensions().Height);
		return glm::perspective(glm::radians(m_Fov), aspectRatio, Options.CutoffNear, Options.CutoffFar);
	}

	void Camera::ProcessMovement(const Movement& moving, float deltaTime)
	{
		auto direction = glm::vec3(0.0f, 0.0f, 0.0f);

		if (moving.forward)
			direction += glm::normalize(glm::cross(Options.WorldUp, m_Right));
		if (moving.backward)
			direction -= glm::normalize(glm::cross(Options.WorldUp, m_Right));
		if (moving.right)
			direction += m_Right;
		if (moving.left)
			direction -= m_Right;
		if (moving.up)
			direction += Options.WorldUp;
		if (moving.down)
			direction -= Options.WorldUp;

		if (direction == glm::vec3(0.0f, 0.0f, 0.0f))
			return;

		const auto distance = Options.MovementSpeed * deltaTime;
		Position += glm::normalize(direction) * distance;
	}

	void Camera::ProcessRotation(float xOffset, float yOffset, bool constrainPitch)
	{
		xOffset *= Options.LookSensitivity;
		yOffset *= Options.LookSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateCameraCoordinateSystem();
	}

	void Camera::ProcessZoom(float offset)
	{
		m_Fov -= offset;
		if (m_Fov < Options.FovMin)
			m_Fov = Options.FovMin;
		if (m_Fov > Options.FovMax)
			m_Fov = Options.FovMax;
	}

	void Camera::UpdateCameraCoordinateSystem() {
		// Calculate the new Front vector
		glm::vec3 front{};
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		m_Front = glm::normalize(front);

		// Re-calculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, Options.WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

}