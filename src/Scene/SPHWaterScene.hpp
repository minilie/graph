/**
 * @file SPHWaterScene.hpp
 * @brief 声明基于 SPH 的水体模拟场景。
 */

#ifndef SPH_WATER_SCENE_HPP
#define SPH_WATER_SCENE_HPP

#include "Scene.h"

#include "../Helper/Program.hpp"
#include "../Helper/ShaderStorage.hpp"

#include "../SPHSimulation/SimulationState.hpp"

#include "../Program/GridProgram.hpp"
#include "../Program/SimulationProgram.hpp"

#include "../Program/Render/RenderSurface.hpp"
#include "../Program/Render/RenderPoints.hpp"
#include "../Program/Render/RenderEdgePoints.hpp"

#include <GL/glew.h>

/**
 * @brief 负责驱动基于 SPH 的水模拟，并进行不同模式的渲染展示的场景。
 */
class SPHWaterScene : public Scene
{
public:
	/**
	 * @brief 渲染模式，控制是渲染表面还是粒子。
	 */
	enum class RenderMode
	{
		Surface,
		Points,
		EdgePoints,
	};

private:
	GL::Program gravityProgram;

	GLint targetLocation;
	GLint dtLocation;

	SimulationState state;
	GridProgram grid;
	SimulationProgram simulation;
	RenderSurface renderSurface;
	RenderPoints renderPoints;
	RenderEdgePoints renderEdgePoints;

	RenderMode renderMode;
	bool distanceFieldDirty;

	float time;
	float timeRemainder;

	bool paused;

	static constexpr float stepTime = 0.016666666666;
public:
	/**
	 * @brief 构造函数，初始化模拟状态和各种渲染、计算模块。
	 */
	SPHWaterScene() :
		state(32, 64, 64, 20),
		grid(state),
		simulation(state),
		renderSurface(state),
		renderPoints(state),
		renderEdgePoints(state),
		renderMode(RenderMode::Surface),
		distanceFieldDirty(true),
		time(0),
		timeRemainder(0),
		paused(false)
	{
	}

	virtual bool Begin() override;
	virtual void End() override;
	virtual void Pause() override;
	virtual void Update(const double) override;

	virtual void PrepareRender() override;
	virtual void Render() override;

	virtual void OnQuit(SDL_QuitEvent& event) override;

	virtual void OnWindow(SDL_WindowEvent& event) override;
	void OnKeyboard(SDL_KeyboardEvent& event) override;

	virtual ~SPHWaterScene() override;
};

#endif //SPH_WATER_SCENE_HPP
