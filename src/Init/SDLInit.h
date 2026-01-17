/**
 * @file SDLInit.h
 * @brief 声明 SDL 初始化相关的工具结构体。
 */

#ifndef SDL_INIT_H
#define SDL_INIT_H

/**
 * @brief 提供 SDL 初始化的静态接口。
 */
struct SDLInit
{
	/**
	 * @brief 初始化 SDL 子系统（事件与视频）。
	 * @return 初始化成功返回 true，否则返回 false。
	 */
	static bool Init();
};

#endif //SDL_INIT_H
