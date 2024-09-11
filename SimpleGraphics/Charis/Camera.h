#pragma once

// Libraries
#include <glm/glm.hpp>

namespace Charis {

	class Camera
	{
	public:
		struct CameraOptions {
			glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			float MovementSpeed = 2.5f;
			float MouseSensitivity = 0.1f;
			float CutoffNear = 0.1f;
			float CutoffFar = 100.0f;
		};
		CameraOptions Options{};
		glm::vec3 Position{};
		float Yaw{};
		float Pitch{};

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		Camera(CameraOptions options, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

		glm::mat4 ViewMatrix() const;
		glm::mat4 ProjectionMatrix() const;

		struct Movement {
			bool forward{};
			bool backward{};
			bool right{};
			bool left{};
			bool up{};
			bool down{};
		};
		void ProcessMovement(const Movement& moving, float deltaTime);
		void ProcessDirection(float xOffset, float yOffset, bool constrainPitch = true);
		void ProcessZoom(float yOffset);

	private:
		void UpdateCameraCoordinateSystem();
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		float Zoom;
	};

}


