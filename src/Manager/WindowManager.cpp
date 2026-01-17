/**
 * @file WindowManager.cpp
 * @brief 实现主窗口及 OpenGL 上下文的创建与销毁逻辑。
 */

#include "WindowManager.h"

#include "../Log/Logger.h"
#include "../Init/GlewInit.h"

#include <SDL2/SDL.h>

/**
 * @brief 初始化窗口管理器，目前不做额外工作。
 * @return 始终返回 true。
 */
bool WindowManager::Init()
{
	return true;
}

/**
 * @brief 根据给定窗口信息创建主窗口和 OpenGL 上下文，并初始化 GLEW。
 * @param info 窗口配置信息。
 * @return 初始化成功返回 true，失败时记录错误并返回 false。
 */
bool WindowManager::SpawnWindow(const WindowInfo& info)
{
	if(!GlewInit::InitContext())
		return false;
	
	//Spawning Main Window
	mainWindow = SDL_CreateWindow(info.title.c_str(), info.x, info.y, info.w, info.h, info.flags);
	if(mainWindow == nullptr)
	{
		Logger::Error() << "Couldn't create window: " << SDL_GetError() << '\n';
		return false;
	}
	
	// Creating OpenGL context
	oContext = SDL_GL_CreateContext(mainWindow);
    if (!oContext)
	{
		Logger::Error() << "Couldn't create openGL context: " << SDL_GetError() << '\n';
        return false;
    }
	
	if(!GlewInit::InitGlew())
		return false;
	
	return true;
}

/**
 * @brief 销毁主窗口和其关联的 OpenGL 上下文。
 */
void WindowManager::DestroyWindow()
{
	SDL_DestroyWindow(mainWindow);
	SDL_GL_DeleteContext(oContext);
}
