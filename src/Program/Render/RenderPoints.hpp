#ifndef RENDER_POINTS_HPP
#define RENDER_POINTS_HPP

#include "../../Helper/Program.hpp"
#include "../../Helper/VertexArray.hpp"

#include <glm/vec3.hpp>

class SimulationState;

class RenderPoints
{
private:
	SimulationState& state;

	GL::Program renderProgram;

	GL::VertexArray va;

 	void CompileShaders();
public:
	RenderPoints(SimulationState& _state);

	~RenderPoints() = default;

	/**
	 * @brief 在屏幕平面上渲染所有粒子点。
	 * @param eye 相机位置。
	 * @param planeOrigin 屏幕平面原点。
	 * @param planeAxisX 屏幕平面 X 轴向量。
	 * @param planeAxisY 屏幕平面 Y 轴向量。
	 * @param boundaryType 边界类型（0: 立方体，1: 球体）。
	 * @param boundaryRadius 球体半径（归一化）。
	 */
	void Render(const glm::vec3& eye, const glm::vec3& planeOrigin, const glm::vec3& planeAxisX, const glm::vec3& planeAxisY,
		int boundaryType, float boundaryRadius);
};

#endif
