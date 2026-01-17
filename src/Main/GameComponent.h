/**
 * @file GameComponent.h
 * @brief 声明游戏组件基类，提供访问 Game 对象的能力。
 */

#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

class Game;

/**
 * @brief 所有需要访问 Game 上下文的组件基类。
 */
class GameComponent
{
public:
	/**
	 * @brief 绑定所属的 Game 对象，便于组件访问全局游戏状态。
	 * @param g 指向 Game 实例的指针。
	 */
	void AttachGame(Game* g)
	{
		game = g;
	}
protected:
	Game* game;
private:
};

#endif //GAME_COMPONENT_H
