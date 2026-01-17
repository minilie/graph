/**
 * @file Shader.cpp
 * @brief 实现 Shader 的编译与日志查询等功能。
 */

#include "Shader.hpp"

#include "../Log/Logger.h"

#include <fstream>
#include <filesystem>
#include <memory>

#include <SDL2/SDL.h>

/**
 * @brief 从文件中读取着色器源代码。
 * @param fileName 着色器文件路径。
 * @return 读取到的源代码字符串，失败时返回空字符串。
 */
std::string ReadShader(const std::string& fileName)
{
	std::ifstream shaderStream(fileName);
	if (!shaderStream.is_open())
	{
		std::string resolvedPath = fileName;
		if(!std::filesystem::path(fileName).is_absolute())
		{
			char* basePath = SDL_GetBasePath();
			if(basePath)
			{
				std::string candidate = std::string(basePath) + fileName;
				SDL_free(basePath);
				shaderStream.clear();
				shaderStream.open(candidate);
				if(shaderStream.is_open())
				{
					resolvedPath = candidate;
				}
			}
		}
		if (!shaderStream.is_open())
		{
			Logger::Warning() << "Couldn't open shader file " << resolvedPath << '\n';
			return "";
		}
	}

	//Copy the file to memory
	std::string shaderCode;
	shaderCode.assign(std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>());

	shaderStream.close();
	return shaderCode;
}

namespace GL {

/**
 * @brief 获取着色器编译日志。
 * @return 日志字符串。
 */
std::string Shader::GetInfoLog() const
{
	GLint infoLogLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	std::unique_ptr<char> errorMessage(new char[infoLogLength]);
	glGetShaderInfoLog(shaderId, infoLogLength, NULL, errorMessage.get());

	return std::string(errorMessage.get());
}

/**
 * @brief 从文件加载着色器源代码并编译。
 * @param fileName 着色器文件路径。
 * @return 编译成功返回 true，否则返回 false。
 */
bool Shader::FromFile(const std::string& fileName)
{
	return FromString(ReadShader(fileName));
}

/**
 * @brief 使用给定字符串作为源代码编译着色器。
 * @param source GLSL 源代码。
 * @return 编译成功返回 true，否则返回 false。
 */
bool Shader::FromString(const std::string& source)
{
	if(shaderId == 0)
	{
		Logger::Warning() << "Can't compile shader: shader name invalid.\n";
		return false;
	}

	const char* str1[1];
	str1[0] = source.c_str();
	glShaderSource( shaderId, 1, str1, NULL );

	// Compile shader
	glCompileShader( shaderId );

	// Get Compilation status
	GLint result = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	return result == GL_TRUE;
}

}// namespace GL
