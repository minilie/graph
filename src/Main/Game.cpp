/**
 * @file Game.cpp
 * @brief 实现 Game 类的主要逻辑，包括初始化、主循环、事件处理、渲染和销毁。
 */

#include "Game.h"

#include "../Scene/InGameScene.h"
#include "../Scene/SPHWaterScene.hpp"

#include "../Log/Logger.h"
#include "../Init/SDLInit.h"
#include "../Model/WindowInfo.h"

#include "../Helper/StaticCounter.hpp"

#include <SDL2/SDL.h>
#include <iostream>

/**
 * @brief 构造 Game 对象，初始化运行标志等成员。
 */
Game::Game() :
	running(true)
{
}

/**
 * @brief 进入游戏主循环，负责初始化并在循环中依次处理事件、更新和渲染。
 */
void Game::Run()
{
	// If something fails at init we quit
	if(Init())
	{
		//Main loop
		while(running)
		{
			HandleEvents();
			Update();
			Render();
			DelayFrameTime(timer.GetFrameStart(), targetFPS);
		}
	}
	Destroy();
}

/**
 * @brief OpenGL 调试输出回调，将调试信息写入日志系统。
 * @param source 消息来源。
 * @param type 消息类型。
 * @param id 消息 ID。
 * @param severity 消息严重程度。
 * @param length 消息长度。
 * @param message 调试信息内容。
 * @param userParam 用户自定义指针，未使用。
 */
void LogGLDebug(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			Logger::Error() << "Opengl: " << message << '\n';
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			Logger::Warning() << "Opengl: " << message << '\n';
			break;
		case GL_DEBUG_SEVERITY_LOW:
			Logger::Warning() << "Opengl low warning: " << message << '\n';
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			Logger::Info() << "Opengl notification: " << message << '\n';
			break;
	}
}

/**
 * @brief 初始化 SDL、窗口管理器和初始场景，并注册 OpenGL 调试回调。
 * @return 初始化成功返回 true，失败返回 false。
 */
bool Game::Init()
{
	if (!SDLInit::Init())
		return false;

	if(!windowManager.Init())
		return false;

	WindowInfo info;
	info.SetTitle("SPH Water Simulation");
	windowManager.SpawnWindow(info);

	//Enable opengl debug output
	glDebugMessageCallback(LogGLDebug, nullptr);

	//Starting main Scene
	sceneManager.AttachGame(this);
	if(!sceneManager.ChangeScene(std::make_unique<SPHWaterScene>()))
	{
		Logger::Error() << "Failed initializing first scene. Exiting\n";
		return false;
	}

	//Starting delta timer
	timer.SetScaleFactor(1);
	timer.Start();

	return true;
}

/**
 * @brief 处理 SDL 事件并将其转发给当前场景。
 */
void Game::HandleEvents()
{
	//This function is dipatching events to the actual scene
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_AUDIODEVICEADDED:
			case SDL_AUDIODEVICEREMOVED:
				sceneManager->OnAudioDevice(event.adevice);
				break;
			case SDL_CONTROLLERAXISMOTION:
				sceneManager->OnControllerAxis(event.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				sceneManager->OnControllerButton(event.cbutton);
				break;
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
				sceneManager->OnControllerDevice(event.cdevice);
				break;
			case SDL_DROPFILE:
			case SDL_DROPTEXT:
			case SDL_DROPBEGIN:
			case SDL_DROPCOMPLETE:
				sceneManager->OnDrop(event.drop);
				break;
			case SDL_FINGERMOTION:
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				sceneManager->OnTouchFinger(event.tfinger);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				sceneManager->OnKeyboard(event.key);
				break;
			case SDL_JOYAXISMOTION:
				sceneManager->OnJoyAxis(event.jaxis);
				break;
			case SDL_JOYBALLMOTION:
				sceneManager->OnJoyBall(event.jball);
				break;
			case SDL_JOYHATMOTION:
				sceneManager->OnJoyHat(event.jhat);
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				sceneManager->OnJoyButton(event.jbutton);
				break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				sceneManager->OnJoyDevice(event.jdevice);
				break;
			case SDL_MOUSEMOTION:
				sceneManager->OnMouseMotion(event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				sceneManager->OnMouseButton(event.button);
				break;
			case SDL_MOUSEWHEEL:
				sceneManager->OnMouseWheel(event.wheel);
				break;
			case SDL_QUIT:
				sceneManager->OnQuit(event.quit);
				break;
			case SDL_USEREVENT:
				sceneManager->OnUser(event.user);
				break;
			case SDL_WINDOWEVENT:
				sceneManager->OnWindow(event.window);
				break;
			default:
				break;
		}
	}
}

/**
 * @brief 更新计时器并驱动当前场景的逻辑更新。
 */
void Game::Update()
{
	timer.Update();
	sceneManager->Update(timer.GetScaledTime());
}

/**
 * @brief 执行当前帧的渲染流程并在窗口上呈现结果。
 */
void Game::Render()
{
	sceneManager->PrepareRender();
	sceneManager->Render();
	windowManager.PresentWindow();
}

/**
 * @brief 根据目标帧率控制每帧的延迟时间，使帧率尽量稳定。
 * @param frameStart 当前帧开始时的时间戳（毫秒）。
 * @param targetFPS 目标帧率。
 */
void Game::DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS)
{
	const unsigned targetLength = 1000 / targetFPS;
	const unsigned frameLenght = SDL_GetTicks() - frameStart;
	int delay = targetLength - frameLenght;
	if(delay > 0)
	{
		SDL_Delay(delay);
	}
}

/**
 * @brief 销毁游戏环境并退出 SDL。
 */
void Game::Destroy()
{
	SDL_Quit();
}
