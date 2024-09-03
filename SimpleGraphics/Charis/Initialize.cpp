#include "Initialize.h"
#include "Utility.h"
#include "Private/CharisGlobals.hpp"
#include "External/stb_image.h"
#include <iostream>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    // Set global variables
    Charis::PrivateGlobal::Window::Width = static_cast<unsigned int>(width);
    Charis::PrivateGlobal::Window::Height = static_cast<unsigned int>(height);
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
		Helper::RuntimeAssert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW.");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        // Set global variables
        PrivateGlobal::Window::Width = width;
        PrivateGlobal::Window::Height = height;
		// glfw window creation
		PrivateGlobal::Window = glfwCreateWindow(width, height, name.data(), NULL, NULL);
		Helper::RuntimeAssert(PrivateGlobal::Window != NULL, "Failed to create GLFW window.");
        glfwMakeContextCurrent(PrivateGlobal::Window);
        glfwSetFramebufferSizeCallback(PrivateGlobal::Window, framebuffer_size_callback);
        glfwSetCursorPosCallback(PrivateGlobal::Window, mouse_callback);
        glfwSetScrollCallback(PrivateGlobal::Window, scroll_callback);
		
        // glad: load all OpenGL function pointers
        Helper::RuntimeAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");

        // configure global opengl state
        glEnable(GL_DEPTH_TEST);

        // tell stb_image.h to flip loaded texture's on the y-axis
        stbi_set_flip_vertically_on_load(true);
	}

    void StartFrame()
    {
        glClearColor(PrivateGlobal::BackgroundRGB[0], PrivateGlobal::BackgroundRGB[1], PrivateGlobal::BackgroundRGB[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void EndFrame()
    {
        glfwSwapBuffers(PrivateGlobal::Window);
        glfwPollEvents();
    }

    bool WindowIsOpen()
    {
        return !glfwWindowShouldClose(PrivateGlobal::Window);
    }

    void CleanUp()
    {
        // glfw: terminate, clearing all previously allocated GLFW resources
        glfwTerminate();
    }

}