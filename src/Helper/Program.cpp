/**
 * @file Program.cpp
 * @brief 实现 Program 组合顶点/片段着色器的便捷创建接口。
 */

#include "Program.hpp"

#include "Shader.hpp"

#include "../Log/Logger.h"

#include <fstream>

namespace GL {

/**
 * @brief 从文件加载顶点和片段着色器并构建、链接程序。
 * @param vertexShaderName 顶点着色器文件名。
 * @param fragmentShaderName 片段着色器文件名。
 * @return 创建和链接成功返回 true，失败返回 false。
 */
bool Program::VsFsProgram( const std::string& vertexShaderName,
	const std::string& fragmentShaderName)
{
	Shader vertexShader(GL_VERTEX_SHADER);
	Shader fragmentShader(GL_FRAGMENT_SHADER);

	bool valid = true;
	if(!vertexShader.FromFile(vertexShaderName))
	{
		Logger::Error() << "Vertex Shader Compilation failed:\n"
			<< vertexShader.GetInfoLog() << '\n';
		valid = false;
	}

	if(!fragmentShader.FromFile(fragmentShaderName))
	{
		Logger::Error() << "Fragment Shader Compilation failed:\n"
			<< fragmentShader.GetInfoLog() << '\n';
		valid = false;
	}

	if(!valid)
	{
		Logger::Error() << "Vertex Fragment program creation failed: Shader compilation failed\n";
		return false;
	}

	AttachShader(vertexShader);
	AttachShader(fragmentShader);
	if(!Link())
	{
		Logger::Error() << "Vertex Fragment program creation failed: Linking failed:\n"
			<< GetInfoLog() << '\n';
	}

	return true;
}

}// namespace GL
