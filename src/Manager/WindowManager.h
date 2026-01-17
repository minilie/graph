/**
 * @file WindowManager.h
 * @brief 声明窗口与 OpenGL 上下文管理类。
 */

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "../Model/WindowInfo.h"

#include <SDL2/SDL.h>

/**
 * @brief 负责创建、呈现和销毁主窗口及其 OpenGL 上下文的管理类。
 */
class WindowManager
{
public:
	bool Init();
	bool SpawnWindow(const WindowInfo&);
	void DestroyWindow();
	
	/**
	 * @brief 交换前后缓冲区，将当前帧呈现到屏幕上。
	 */
	void PresentWindow()
	{
		SDL_GL_SwapWindow(mainWindow);
	}
	
	/**
	 * @brief 析构函数，确保窗口和上下文被正确销毁。
	 */
	~WindowManager()
	{
		DestroyWindow();
	}
private:
	SDL_Window* mainWindow;
	SDL_GLContext oContext;
};

#endif //WINDOW_MANAGER_H
