/**
 * @file EventListener.h
 * @brief 声明事件监听基类，封装 SDL 各种事件回调接口。
 */

#ifndef Event_Listener_H
#define Event_Listener_H

#include "../Main/GameComponent.h"

#include <SDL2/SDL.h>

/**
 * @brief SDL 事件监听基类，派生类可按需重写对应回调函数。
 */
class EventListener :
	public GameComponent
{
public:
	/**
	 * @brief 处理音频设备相关事件。
	 * @param event SDL 音频设备事件。
	 */
	virtual void OnAudioDevice(SDL_AudioDeviceEvent&){}
	
	/**
	 * @brief 处理手柄轴运动事件。
	 * @param event SDL 控制器轴事件。
	 */
	virtual void OnControllerAxis(SDL_ControllerAxisEvent&){}
	
	/**
	 * @brief 处理手柄按键事件。
	 * @param event SDL 控制器按键事件。
	 */
	virtual void OnControllerButton(SDL_ControllerButtonEvent&){}
	
	/**
	 * @brief 处理控制器设备插拔等事件。
	 * @param event SDL 控制器设备事件。
	 */
	virtual void OnControllerDevice(SDL_ControllerDeviceEvent&){}
	
	/**
	 * @brief 处理拖放相关事件（文件、文本等）。
	 * @param event SDL 拖放事件。
	 */
	virtual void OnDrop(SDL_DropEvent&){}
	
	/**
	 * @brief 处理触摸屏手指事件。
	 * @param event SDL 触摸手指事件。
	 */
	virtual void OnTouchFinger(SDL_TouchFingerEvent&){}
	
	/**
	 * @brief 处理键盘按键事件。
	 * @param event SDL 键盘事件。
	 */
	virtual void OnKeyboard(SDL_KeyboardEvent&){}
	
	/**
	 * @brief 处理摇杆轴移动事件。
	 * @param event SDL 摇杆轴事件。
	 */
	virtual void OnJoyAxis(SDL_JoyAxisEvent&){}
	
	/**
	 * @brief 处理摇杆球事件。
	 * @param event SDL 摇杆球事件。
	 */
	virtual void OnJoyBall(SDL_JoyBallEvent&){}

	/**
	 * @brief 处理摇杆帽（方向帽）事件。
	 * @param event SDL 摇杆帽事件。
	 */
	virtual void OnJoyHat(SDL_JoyHatEvent&){}
	
	/**
	 * @brief 处理摇杆按键事件。
	 * @param event SDL 摇杆按键事件。
	 */
	virtual void OnJoyButton(SDL_JoyButtonEvent&){}
	
	/**
	 * @brief 处理摇杆设备插拔事件。
	 * @param event SDL 摇杆设备事件。
	 */
	virtual void OnJoyDevice(SDL_JoyDeviceEvent&){}
	
	/**
	 * @brief 处理鼠标移动事件。
	 * @param event SDL 鼠标移动事件。
	 */
	virtual void OnMouseMotion(SDL_MouseMotionEvent&){}
	
	/**
	 * @brief 处理鼠标按键事件。
	 * @param event SDL 鼠标按键事件。
	 */
	virtual void OnMouseButton(SDL_MouseButtonEvent&){}

	/**
	 * @brief 处理鼠标滚轮事件。
	 * @param event SDL 鼠标滚轮事件。
	 */
	virtual void OnMouseWheel(SDL_MouseWheelEvent&){}
	
	/**
	 * @brief 处理全局退出事件。
	 * @param event SDL 退出事件。
	 */
	virtual void OnQuit(SDL_QuitEvent&){}
	
 	// virtual void OnTextInput(SDL_TextInputEvent&){}
	
	/**
	 * @brief 处理用户自定义事件。
	 * @param event SDL 用户事件。
	 */
	virtual void OnUser(SDL_UserEvent&){}
	
	/**
	 * @brief 处理窗口相关事件。
	 * @param event SDL 窗口事件。
	 */
	virtual void OnWindow(SDL_WindowEvent&){}
	
protected:
private:
};

#endif //Event_Listener_H
