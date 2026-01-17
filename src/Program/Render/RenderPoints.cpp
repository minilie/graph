#include "RenderPoints.hpp"

#include "../../SPHSimulation/SimulationState.hpp"
#include "../../Log/Logger.h"

#include <glm/vec3.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

static constexpr const char* VertexSource = "../shaders/Render/passthrough.vert";
static constexpr const char* FragmentSource = "../shaders/Render/passthrough.frag";

static constexpr const char* PositionBufferName = "positionBuffer";
static constexpr const char* VelocityBufferName = "velocityBuffer";
static constexpr const char* PressureBufferName = "pressureBuffer";
static constexpr const char* ForceBufferName = "forceBuffer";

static constexpr const unsigned EyeLocation = 0;
static constexpr const unsigned PlaneOriginLocation = 1;
static constexpr const unsigned PlaneAxisXLocation = 2;
static constexpr const unsigned PlaneAxisYLocation = 3;
static constexpr const unsigned BoundaryTypeLocation = 4;
static constexpr const unsigned BoundaryRadiusLocation = 5;

RenderPoints::RenderPoints(SimulationState& _state) :
	state(_state)
{
	CompileShaders();

	state.AttachPressure(renderProgram, PressureBufferName);
	state.AttachParticleIndex(renderProgram, "indexBuffer");
	state.AttachForce(renderProgram, ForceBufferName);
	state.AttachDensity(renderProgram, "densityBuffer");
}

void RenderPoints::CompileShaders()
{
	if(!renderProgram.VsFsProgram(VertexSource, FragmentSource))
	{
		Logger::Error() << "Render Program linking failed: " << renderProgram.GetInfoLog() <<  '\n';
	}
}

void RenderPoints::Render(const glm::vec3& eye, const glm::vec3& planeOrigin, const glm::vec3& planeAxisX, const glm::vec3& planeAxisY,
	int boundaryType, float boundaryRadius)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderProgram.Use();
	va.Bind();

	state.AttachPosition(renderProgram, PositionBufferName);
	state.AttachVelocity(renderProgram, VelocityBufferName);

	glUniform3fv(EyeLocation, 1, reinterpret_cast<const GLfloat*>(&eye[0]));
	glUniform3fv(PlaneOriginLocation, 1, reinterpret_cast<const GLfloat*>(&planeOrigin[0]));
	glUniform3fv(PlaneAxisXLocation, 1, reinterpret_cast<const GLfloat*>(&planeAxisX[0]));
	glUniform3fv(PlaneAxisYLocation, 1, reinterpret_cast<const GLfloat*>(&planeAxisY[0]));
	glUniform1i(BoundaryTypeLocation, boundaryType);
	glUniform1f(BoundaryRadiusLocation, boundaryRadius);

	glDrawArrays(GL_POINTS, 0, state.ResX() * state.ResY() * state.ResZ());
}
