#include "Initialize.h"
#include "Utility.h"
using namespace Charis::Helper;
#include "Private.hpp"
using namespace Charis::PrivateGlobal;
#include <iostream>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    Charis::PrivateGlobal::Mouse::X = static_cast<float>(xPosIn);
    Charis::PrivateGlobal::Mouse::Y = static_cast<float>(yPosIn);
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Charis::PrivateGlobal::Mouse::Wheel += static_cast<float>(yoffset);
}

namespace Charis {

	void Initialize(unsigned int width, unsigned int height, const std::string& name)
	{
        // glfw: initialize and configure
		RuntimeAssert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW.");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		Window = glfwCreateWindow(width, height, name.data(), NULL, NULL);
		RuntimeAssert(Window != NULL, "Failed to create GLFW window.");
        glfwMakeContextCurrent(Window);
        glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
        glfwSetCursorPosCallback(Window, mouse_callback);
        glfwSetScrollCallback(Window, scroll_callback);
		
        // glad: load all OpenGL function pointers
        RuntimeAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");

        // configure global opengl state
        glEnable(GL_DEPTH_TEST);

	}

    void InitializeLoop()
    {
        glClearColor(BackgroundRGB[0], BackgroundRGB[1], BackgroundRGB[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    bool WindowIsOpen()
    {
        return !glfwWindowShouldClose(Window);
    }

    void CleanUp()
    {
        // glfw: terminate, clearing all previously allocated GLFW resources
        glfwTerminate();
    }

}