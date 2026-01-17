#ifndef RENDER_SURFACE_HPP
#define RENDER_SURFACE_HPP

#include "../../Helper/Texture.h"
#include "../../Helper/Program.hpp"
#include "../../Helper/VertexArray.hpp"

#include "OrbiterCamera.hpp"
#include "Direction.hpp"

#include <memory>

class SimulationState;

class RenderSurface
{
private:
	SimulationState& state;
	std::unique_ptr<GL::Texture> distanceFieldTexture;

	GL::Program distanceFieldProgram;
	GL::Program raycastProgram;

	GL::VertexArray va;

	OrbiterCamera camera;
	/**
	 * @brief 边界模式类型。
	 * 用于在渲染阶段选择容器为立方体或球体。
	 */
	enum class BoundaryMode { Cube = 0, Sphere = 1 };
	BoundaryMode boundaryMode = BoundaryMode::Cube;
	float boundaryRadius = 0.5f;

 	void CompileShaders();
	void DistanceField();
	void Raycast();
public:
	RenderSurface(SimulationState& _state);

	~RenderSurface() = default;

	void Update(float time);

	void UpdateParticles();

	void Render();

	void SetDistanceTextureSize(unsigned length);

	/**
	 * @brief 设置相机水平移动方向。
	 * @param dir 前进/后退/停止。
	 */
	void SetHorizontalDirection(Direction dir)
	{
		camera.SetHorizontalDirection(dir);
	}

	/**
	 * @brief 设置相机垂直移动方向。
	 * @param dir 前进/后退/停止。
	 */
	void SetVerticalDirection(Direction dir)
	{
		camera.SetVerticalDirection(dir);
	}

	const glm::mat4& GetWorld() const
	{
		return camera.GetView();
	}

	const glm::vec3& GetEye() const
	{
		return camera.GetEye();
	}

	/**
	 * @brief 获取当前视图下的重力方向向量。
	 */
	glm::vec3 GetGravity()
	{
		return glm::vec3(camera.GetView() * glm::vec4(0, -1, 0, 0));
	}

	/**
	 * @brief 设置边界模式。
	 * @param mode 立方体或球体。
	 */
	void SetBoundaryMode(BoundaryMode mode)
	{
		boundaryMode = mode;
	}

	/**
	 * @brief 切换边界模式（立方体/球体）。
	 */
	void ToggleBoundaryMode()
	{
		boundaryMode = (boundaryMode == BoundaryMode::Cube) ? BoundaryMode::Sphere : BoundaryMode::Cube;
	}

	/**
	 * @brief 获取当前边界模式。
	 */
	BoundaryMode GetBoundaryMode() const
	{
		return boundaryMode;
	}

	/**
	 * @brief 当前边界是否为球体。
	 */
	bool IsSphere() const
	{
		return boundaryMode == BoundaryMode::Sphere;
	}

	/**
	 * @brief 设置球体边界半径（归一化到 [0,1]）。
	 * @param r 半径，范围建议在 0.1~0.9 之间。
	 */
	void SetBoundaryRadius(float r)
	{
		boundaryRadius = r;
		if(boundaryRadius < 0.1f) boundaryRadius = 0.1f;
		if(boundaryRadius > 0.9f) boundaryRadius = 0.9f;
	}

	/**
	 * @brief 获取当前球体边界半径。
	 */
	float GetBoundaryRadius() const { return boundaryRadius; }
};

#endif
