#include "RenderEdgePoints.hpp"

#include "../../SPHSimulation/SimulationState.hpp"
#include "../../Log/Logger.h"

#include <glm/vec3.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

static constexpr const char* VertexSource = "../shaders/Render/edgeOnly.vert";
static constexpr const char* FragmentSource = "../shaders/Render/passthrough.frag";

static constexpr const char* EdgeBufferName = "edgeBuffer";

static constexpr const unsigned EyeLocation = 0;
static constexpr const unsigned PlaneOriginLocation = 1;
static constexpr const unsigned PlaneAxisXLocation = 2;
static constexpr const unsigned PlaneAxisYLocation = 3;

RenderEdgePoints::RenderEdgePoints(SimulationState& _state) :
	state(_state)
{
	CompileShaders();

	state.AttachEdge(renderProgram, EdgeBufferName);
}

void RenderEdgePoints::CompileShaders()
{
	if(!renderProgram.VsFsProgram(VertexSource, FragmentSource))
	{
		Logger::Error() << "Render Program linking failed: " << renderProgram.GetInfoLog() <<  '\n';
	}
}

void RenderEdgePoints::Render(const glm::vec3& eye, const glm::vec3& planeOrigin, const glm::vec3& planeAxisX, const glm::vec3& planeAxisY)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unsigned edgeCount = state.GetEdgeCount();

	renderProgram.Use();
	va.Bind();

	glUniform3fv(EyeLocation, 1, reinterpret_cast<const GLfloat*>(&eye[0]));
	glUniform3fv(PlaneOriginLocation, 1, reinterpret_cast<const GLfloat*>(&planeOrigin[0]));
	glUniform3fv(PlaneAxisXLocation, 1, reinterpret_cast<const GLfloat*>(&planeAxisX[0]));
	glUniform3fv(PlaneAxisYLocation, 1, reinterpret_cast<const GLfloat*>(&planeAxisY[0]));

	glDrawArrays(GL_POINTS, 0, edgeCount);
}
