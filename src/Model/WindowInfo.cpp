/**
 * @file WindowInfo.cpp
 * @brief 实现 WindowInfo 的默认构造与属性设置接口。
 */

#include "WindowInfo.h"

#include <SDL2/SDL.h>

/**
 * @brief 默认构造函数，创建一个带 OpenGL 和可调整大小标志的方形窗口配置。
 */
WindowInfo::WindowInfo() :
	title(""),
	x(SDL_WINDOWPOS_UNDEFINED),
	y(SDL_WINDOWPOS_UNDEFINED),
	w(1000),
	h(1000),
	flags(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)
{
}

/**
 * @brief 设置窗口标题。
 * @param t 新的窗口标题。
 */

void WindowInfo::SetTitle(const std::string& t)
{
	title = t;
}

/**
 * @brief 设置窗口位置。
 * @param X 左上角 X 坐标。
 * @param Y 左上角 Y 坐标。
 */
void WindowInfo::SetPos(int X, int Y)
{
	x = X;
	y = Y;
}

/**
 * @brief 设置窗口大小。
 * @param W 宽度。
 * @param H 高度。
 */
void WindowInfo::SetSize(int W, int H)
{
	w = W;
	h = H;
}

/**
 * @brief 控制窗口是否启用 OpenGL 标志。
 * @param val 为 true 时启用 OpenGL，为 false 时关闭。
 */
void WindowInfo::SetOpenGL(bool val)
{
	if(val)
	{
		flags |= SDL_WINDOW_OPENGL;
	} else {
		flags &= SDL_WINDOW_OPENGL ^ 1;
	}
}

/**
 * @brief 控制窗口的可见性。
 * @param val 为 true 时窗口可见，为 false 时隐藏。
 */
void WindowInfo::SetVisible(bool val)
{
	if(val)
	{
		flags &= SDL_WINDOW_HIDDEN ^ 1;
	} else {
		flags |= SDL_WINDOW_HIDDEN;
	}
}

/**
 * @brief 控制窗口是否可以调整大小。
 * @param val 为 true 时窗口可调整大小，为 false 时固定大小。
 */
void WindowInfo::SetResizable(bool val)
{
	if(val)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	} else {
		flags &= SDL_WINDOW_RESIZABLE ^ 1;
	}
}
