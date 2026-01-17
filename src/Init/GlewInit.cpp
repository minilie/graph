/**
 * @file GlewInit.cpp
 * @brief 实现 OpenGL 上下文和 GLEW 初始化的功能。
 */

#include "GlewInit.h"

#include "../Log/Logger.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

/**
 * @brief 配置 SDL 的 OpenGL 上下文属性，例如版本、颜色缓冲和深度缓冲等。
 * @return 始终返回 true，表示属性设置已完成。
 */
bool GlewInit::InitContext()
{
	// Setting up SDL_OPENGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Color buffers size
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Double-buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Depth-buffer size
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Anti-aliasing
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// V-sync on
	SDL_GL_SetSwapInterval(1);

	return true;
}

/**
 * @brief 初始化 GLEW，并输出 OpenGL 版本信息。
 * @return 初始化成功返回 true，失败时记录错误信息并返回 false。
 */
bool GlewInit::InitGlew()
{
	// Starting Glew
	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		Logger::Error() << "Glew Init failed: " << glewGetErrorString(error) << '\n';
		return false;
	}

	Logger::Info() << "Opengl version: " << glGetString(GL_VERSION) << '\n';

	return true;
}
