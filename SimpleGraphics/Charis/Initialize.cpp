#include "Initialize.h"
#include "Helper.hpp"
#include "Private.hpp"
#include <iostream>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Charis {

    // TODO
    static void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);*/
    }
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    static void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn)
    {
        PrivateGlobal::Mouse::X = static_cast<float>(xPosIn);
        PrivateGlobal::Mouse::Y = static_cast<float>(yPosIn);
    }
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        PrivateGlobal::Mouse::Wheel = static_cast<float>(yoffset);
    }

	void Initialize(const std::string& name, unsigned int width, unsigned int height)
	{
		// glfw: initialize and configure
		DynamicAssert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW.");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		PrivateGlobal::Window = glfwCreateWindow(width, height, name.data(), NULL, NULL);
		DynamicAssert(PrivateGlobal::Window != NULL, "Failed to create GLFW window.");
        glfwMakeContextCurrent(PrivateGlobal::Window);
        glfwSetFramebufferSizeCallback(PrivateGlobal::Window, framebuffer_size_callback);
        glfwSetCursorPosCallback(PrivateGlobal::Window, mouse_callback);
        glfwSetScrollCallback(PrivateGlobal::Window, scroll_callback);
		
        // glad: load all OpenGL function pointers
        DynamicAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");

        // configure global opengl state
        glEnable(GL_DEPTH_TEST);

	}

    void InitializeLoop()
    {
        if (glfwGetKey(Charis::PrivateGlobal::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Charis::PrivateGlobal::Window, true);

        glfwSwapBuffers(Charis::PrivateGlobal::Window);
        glfwPollEvents();
    }

    bool WindowIsOpen()
    {
        return !glfwWindowShouldClose(Charis::PrivateGlobal::Window);
    }

}