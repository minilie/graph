/**
 * @file main.cpp
 * @brief 程序入口，负责初始化日志等级并启动游戏主循环。
 */

#include "Game.h"

#include <SDL2/SDL_main.h>

#include "../Log/Logger.h"

/**
 * @brief 程序入口函数，根据命令行参数设置日志等级并运行游戏。
 * @param argc 命令行参数数量。
 * @param args 命令行参数数组。
 * @return 程序退出码，正常运行返回 0。
 */
int main(int argc, char* args[])
{

	if(argc > 1 && std::string(args[1]) == "-d")
		Logging::Settings::SetLevel(Logging::Level::Debug);
	else
		Logging::Settings::SetLevel(Logging::Level::Error);

	Game game;
	game.Run();

	return 0;
}
