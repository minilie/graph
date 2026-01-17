/**
 * @file Game.h
 * @brief 声明 Game 类，用于管理游戏主循环、场景和窗口。
 */

#include "ScaledDeltaTimer.h"
#include "../Manager/SceneManager.h"
#include "../Manager/WindowManager.h"

class Game
{
public:
	Game();
	void Run();

	bool running;
protected:
private:
	bool Init();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();
	void DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS);

	SceneManager sceneManager;
	WindowManager windowManager;
	ScaledDeltaTimer timer;
	unsigned short targetFPS = 60;
};
