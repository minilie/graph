/**
 * @file SceneManager.h
 * @brief 声明场景管理器，用于管理场景栈与当前活动场景。
 */

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <stack>

#include "../Main/GameComponent.h"

struct Scene;

/**
 * @brief 负责维护场景栈，支持切换、压栈与弹出场景的管理器。
 */
class SceneManager :
	public GameComponent
{
public:
	void PushScene(std::unique_ptr<Scene> ptr);
	void PopScene();
	bool ChangeScene(std::unique_ptr<Scene> ptr);
	Scene* currentScene() const;

	Scene* operator->() const;

	~SceneManager();
protected:
private:
	std::stack< std::unique_ptr<Scene> > sceneStack;
};

#endif //SCENE_MANAGER_H
