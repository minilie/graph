/**
 * @file SDLInit.cpp
 * @brief 实现 SDL 初始化函数。
 */

#include "SDLInit.h"

#include "../Log/Logger.h"

#include <SDL2/SDL.h>

/**
 * @brief 初始化 SDL 事件和视频子系统，并在失败时记录错误日志。
 * @return SDL 初始化成功返回 true，失败返回 false。
 */
bool SDLInit::Init()
{
	//Initializing SDL
	if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
	{
		Logger::Error() << "Couldn't initialize SDL: " << SDL_GetError() << '\n';
		return false;
	}
	
	return true;
}
