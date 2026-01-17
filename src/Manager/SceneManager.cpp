/**
 * @file SceneManager.cpp
 * @brief 实现场景栈的管理逻辑，包括推入、弹出和切换场景。
 */

#include "SceneManager.h"
#include "../Scene/Scene.h"

/**
 * @brief 将新场景压入场景栈，并暂停之前的场景。
 * @param ptr 指向新场景的智能指针。
 */
void SceneManager::PushScene(std::unique_ptr<Scene> ptr)
{
	if(!sceneStack.empty())
	{
		sceneStack.top()->Pause();
	}

	sceneStack.push(std::move(ptr));
	sceneStack.top()->AttachGame(game);
	sceneStack.top()->Begin();
}

/**
 * @brief 弹出当前场景并恢复下一个场景。
 */
void SceneManager::PopScene()
{
	sceneStack.top()->End();
	sceneStack.pop();

	sceneStack.top()->AttachGame(game);
	sceneStack.top()->Begin();
}

/**
 * @brief 替换当前场景为新的场景，销毁旧场景。
 * @param ptr 指向新场景的智能指针。
 * @return 新场景 Begin 成功返回 true，否则返回 false。
 */
bool SceneManager::ChangeScene(std::unique_ptr<Scene> ptr)
{
	if(!sceneStack.empty())
	{
		sceneStack.top()->End();
		sceneStack.pop();
	}

	sceneStack.push(std::move(ptr));
	sceneStack.top()->AttachGame(game);
	return sceneStack.top()->Begin();
}

/**
 * @brief 获取当前栈顶场景指针。
 * @return 指向当前场景的裸指针。
 */
Scene* SceneManager::currentScene() const
{
	return sceneStack.top().get();
}

/**
 * @brief 通过操作符重载便捷访问当前场景成员。
 * @return 当前场景的指针。
 */
Scene* SceneManager::operator->() const
{
	return currentScene();
}

/**
 * @brief 析构函数，在退出时依次结束并弹出所有场景。
 */
SceneManager::~SceneManager()
{
	while(!sceneStack.empty())
	{
		sceneStack.top()->End();
		sceneStack.pop();
	}
}
