#version 450

layout(std430, binding = 0) restrict readonly buffer positionBuffer
{
    vec3 position[];
};

struct gridIndex
{
    uint id;
    uint localOffset;
};

layout(std430) restrict readonly buffer indexBuffer
{
	gridIndex particleGridIndex[];
};

layout(std430) restrict readonly buffer pressureBuffer
{
    float pressure[];
};

layout(std430) restrict readonly buffer velocityBuffer
{
    vec3 velocity[];
};

layout(std430) restrict readonly buffer forceBuffer
{
    vec3 force[];
};

layout(std430) restrict readonly buffer densityBuffer
{
    float density[];
};

out gl_PerVertex
{
	vec4 gl_Position;
    float gl_PointSize;
};

out VertexData
{
	vec3 out_pos;
};

layout(location = 0) uniform vec3 Eye;
layout(location = 1) uniform vec3 PlaneOrigin;
layout(location = 2) uniform vec3 PlaneAxisX;
layout(location = 3) uniform vec3 PlaneAxisY;
layout(location = 4) uniform int BoundaryType;
layout(location = 5) uniform float BoundaryRadius;

bool inCube(vec3 p)
{
	return all(lessThan(p, vec3(1.0))) && all(greaterThanEqual(p, vec3(0.0)));
}

bool inSphere(vec3 p)
{
	vec3 c = vec3(0.5, 0.5, 0.5);
	return distance(p, c) <= BoundaryRadius;
}

bool inBoundary(vec3 p)
{
	return (BoundaryType == 0) ? inCube(p) : inSphere(p);
}

void main()
{
    /*uint id = gl_VertexID;

    vec3 pos = position[id];
    vec3 toTarget = -1.0 * pos;
    float l = length(toTarget);
    float strength = l * l - 1.0;

    position[id] = pos + strength * toTarget * 0.01;*/

    vec3 pos = position[gl_VertexID];
    //gridIndex grid = particleGridIndex[gl_VertexID];

    float pr = density[gl_VertexID] / 400;
	//out_pos = mix(vec3(0, 1, 0), vec3(1,0,0), vec3(grid.id / 15600.0));
    out_pos = /*vec3(0, .3, .7);//velocity[gl_VertexID];//force[gl_VertexID];//*/vec3(pr, 1 - pr, 0);

	const float scale = 1.0 / 2.2;
	const float offset = 1.0 / 2.2 + 0.05;
	vec3 cubePos = pos * scale + vec3(offset);

	if(!inBoundary(cubePos))
	{
		gl_Position = vec4(2, 2, 2, 1);
		gl_PointSize = 1;
		return;
	}

	vec3 ray = cubePos - Eye;
	vec3 n = cross(PlaneAxisX, PlaneAxisY);
	float denom = dot(ray, n);
	if(abs(denom) < 1e-6)
	{
		gl_Position = vec4(2, 2, 2, 1);
		gl_PointSize = 1;
		return;
	}

	float t = dot(PlaneOrigin - Eye, n) / denom;
	if(t <= 0)
	{
		gl_Position = vec4(2, 2, 2, 1);
		gl_PointSize = 1;
		return;
	}

	vec3 hit = Eye + t * ray;
	vec3 rel = hit - PlaneOrigin;

	float aa = dot(PlaneAxisX, PlaneAxisX);
	float ab = dot(PlaneAxisX, PlaneAxisY);
	float bb = dot(PlaneAxisY, PlaneAxisY);
	float ra = dot(rel, PlaneAxisX);
	float rb = dot(rel, PlaneAxisY);
	float det = aa * bb - ab * ab;

	float u = (ra * bb - rb * ab) / det;
	float v = (rb * aa - ra * ab) / det;

	vec2 ndc = vec2(u * 2.0 - 1.0, v * 2.0 - 1.0);

	vec3 planeCenter = PlaneOrigin + 0.5 * PlaneAxisX + 0.5 * PlaneAxisY;
	vec3 forward = normalize(planeCenter - Eye);
	float depth = dot(cubePos - Eye, forward);
	float z = clamp((depth - 0.01) / (10.0 - 0.01), 0.0, 1.0) * 2.0 - 1.0;

    gl_Position = vec4(ndc, z, 1);

    gl_PointSize = 1;//100 - 2 * gl_Position[3];
}
