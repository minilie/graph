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

	void SetHorizontalDirection(Direction dir)
	{
		camera.SetHorizontalDirection(dir);
	}

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

	glm::vec3 GetGravity()
	{
		return glm::vec3(camera.GetView() * glm::vec4(0, -1, 0, 0));
	}

	void SetBoundaryMode(BoundaryMode mode)
	{
		boundaryMode = mode;
	}

	void ToggleBoundaryMode()
	{
		boundaryMode = (boundaryMode == BoundaryMode::Cube) ? BoundaryMode::Sphere : BoundaryMode::Cube;
	}

	BoundaryMode GetBoundaryMode() const
	{
		return boundaryMode;
	}

	bool IsSphere() const
	{
		return boundaryMode == BoundaryMode::Sphere;
	}

	void SetBoundaryRadius(float r)
	{
		boundaryRadius = r;
		if(boundaryRadius < 0.1f) boundaryRadius = 0.1f;
		if(boundaryRadius > 0.9f) boundaryRadius = 0.9f;
	}

	float GetBoundaryRadius() const { return boundaryRadius; }
};

#endif
