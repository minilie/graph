#ifndef RENDER_EDGE_POINTS_HPP
#define RENDER_EDGE_POINTS_HPP

#include "../../Helper/Program.hpp"
#include "../../Helper/VertexArray.hpp"

#include <glm/vec3.hpp>

class SimulationState;

class RenderEdgePoints
{
private:
	SimulationState& state;

	GL::Program renderProgram;

	GL::VertexArray va;

 	void CompileShaders();
public:
	RenderEdgePoints(SimulationState& _state);

	~RenderEdgePoints() = default;

	void Render(const glm::vec3& eye, const glm::vec3& planeOrigin, const glm::vec3& planeAxisX, const glm::vec3& planeAxisY,
		int boundaryType, float boundaryRadius);
};

#endif
