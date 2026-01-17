/**
 * @file Scene.h
 * @brief 声明所有场景的抽象基类接口。
 */

#ifndef SCENE_H
#define SCENE_H

#include "../Event/EventListener.h"

/**
 * @brief 场景基类，定义生命周期与渲染相关接口。
 */
struct Scene :
	public EventListener
{
	/**
	 * @brief 场景开始时调用，用于初始化资源。
	 * @return 初始化成功返回 true，否则返回 false。
	 */
	virtual bool Begin(){ return false; }

	/**
	 * @brief 场景结束时调用，用于释放资源。
	 */
	virtual void End(){}

	/**
	 * @brief 场景被暂停时调用。
	 */
	virtual void Pause(){}

	/**
	 * @brief 每帧更新逻辑。
	 * @param delta 距上一帧的时间（秒）。
	 */
	virtual void Update(const double){}

	/**
	 * @brief 渲染前的准备工作，例如更新摄像机或缓冲。
	 */
	virtual void PrepareRender(){}

	/**
	 * @brief 执行具体渲染操作。
	 */
	virtual void Render(){}

	/**
	 * @brief 虚析构函数，保证派生类正确析构。
	 */
	virtual ~Scene(){}
};

#endif //SCENE_H
