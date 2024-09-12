#pragma once

// Libraries
#include <glm/glm.hpp>

namespace Charis {

	/// <summary>
	/// A class made for managing view and projection matrices for a given position and rotation, 
	/// as well as functions to handle movement, rotation, and zoom of the camera.
	/// </summary>
	class Camera
	{
	public:
		/// <summary>Contains settings and options for how the camera works.</summary>
		struct CameraOptions {
			glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			float MovementSpeed = 2.5f;
			float LookSensitivity = 0.1f;
			float CutoffNear = 0.1f;
			float CutoffFar = 100.0f;
			float FovMin = 1.0f;
			float FovMax = 45.0f;
		};
		CameraOptions Options{};
		glm::vec3 Position{};
		float Yaw{};
		float Pitch{};

		/// <summary>
		/// Constructor for a Camera.
		/// </summary>
		/// <param name="position">The starting position for the camera.</param>
		/// <param name="worldUp">A vector pointing in the up-direction for the world coordinate system.</param>
		/// <param name="yaw">The starting yaw angle.</param>
		/// <param name="pitch">The starting pitch angle.</param>
		/// <param name="fov">The starting field-of-view angle.</param>
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f, float fov = 45.0f);
		/// <summary>
		/// Constructor for a Camera.
		/// </summary>
		/// <param name="options">Provides settings and options used for the camera.</param>
		/// <param name="position">The starting position for the camera.</param>
		/// <param name="yaw">The starting yaw angle.</param>
		/// <param name="pitch">The starting pitch angle.</param>
		Camera(CameraOptions options, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f, float fov = 45.0f);

		/// <summary>Provides the a view matrix based on the position and angles of the camera.</summary>
		glm::mat4 ViewMatrix() const;
		/// <summary>Provides a projection matrix based on the camera zoom, camera options, and aspect ratio of the window.</summary>
		glm::mat4 ProjectionMatrix() const;

		/// <summary>A struct containing booleans for which directions the camera should move in.</summary>
		struct Movement {
			bool forward{};
			bool backward{};
			bool right{};
			bool left{};
			bool up{};
			bool down{};
		};
		/// <summary>
		/// Moves the position of the camera, based on on the movement speed.
		/// </summary>
		/// <param name="moving">A struct object containing which directions the camera is moving in.</param>
		/// <param name="deltaTime">Time since last frame.</param>
		void ProcessMovement(const Movement& moving, float deltaTime);
		/// <summary>
		/// Updates the yaw and pitch angles based on input (e.g. mouse movement).
		/// </summary>
		/// <param name="xOffset">Difference in yaw-rotation between current and new angle.</param>
		/// <param name="yOffset">Difference in pitch-rotation between current and new angle.</param>
		/// <param name="constrainPitch">If true, will limit pitch to not be able to look further than straight up or straight down.</param>
		void ProcessRotation(float xOffset, float yOffset, bool constrainPitch = true);
		/// <summary>
		/// Updates the zoom based on input (e.g. mouse wheel).
		/// </summary>
		/// <param name="offset">Difference in zoom (or fov) between current and new value.</param>
		void ProcessZoom(float offset);

	private:
		void UpdateCameraCoordinateSystem();
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		float m_Fov{};
	};

}


