#version 450

layout(std430) restrict buffer edgeBuffer
{
    uint count;
    vec3 position[];
} edgeParticles;

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

void main()
{
	vec3 pos = gl_VertexID < edgeParticles.count ? edgeParticles.position[gl_VertexID] : vec3(-2, -2, -2);
    out_pos = vec3(0, .4, 1);

	const float scale = 1.0 / 2.2;
	const float offset = 1.0 / 2.2 + 0.05;
	vec3 cubePos = pos * scale + vec3(offset);

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
	gl_PointSize = 1;
}
