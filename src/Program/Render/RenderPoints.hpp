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

	void Render(const glm::vec3& eye, const glm::vec3& planeOrigin, const glm::vec3& planeAxisX, const glm::vec3& planeAxisY);
};

#endif
