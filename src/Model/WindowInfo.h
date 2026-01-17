/**
 * @file WindowInfo.h
 * @brief 声明描述 SDL 窗口参数的结构体。
 */

#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

#include <string>
#include <cstdint>

/**
 * @brief 存储窗口标题、位置、大小和标志位等信息的结构体。
 */
struct WindowInfo
{
	/**
	 * @brief 通过完整参数初始化窗口信息。
	 * @param t 窗口标题。
	 * @param X 窗口左上角 X 坐标。
	 * @param Y 窗口左上角 Y 坐标。
	 * @param W 窗口宽度。
	 * @param H 窗口高度。
	 * @param f SDL 窗口标志位。
	 */
	WindowInfo(const std::string& t, int X, int Y, int W, int H, std::uint32_t f) :
		title(t),
		x(X),
		y(Y),
		w(W),
		h(H),
		flags(f)
	{
	}
	
	WindowInfo();
	
	void SetTitle(const std::string&);
	void SetPos(int, int);
	void SetSize(int, int);
	void SetOpenGL(bool);
	void SetVisible(bool);
	void SetResizable(bool);
	
	WindowInfo(const WindowInfo&) = default;
	WindowInfo& operator=(const WindowInfo&) = default;
	
	WindowInfo(WindowInfo&&) = default;
	WindowInfo& operator=(WindowInfo&&) = default;
	
	std::string title;
	int x, y, w, h;
	std::uint32_t flags;
};

#endif //WINDOW_INFO_H
