/**
 * @file Shader.hpp
 * @brief 封装 OpenGL 着色器对象的创建、编译与查询接口。
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <utility>
#include <string>

namespace GL {

/**
 * @brief 对 OpenGL Shader 对象的封装类。
 */
class Shader
{
private:
	GLuint shaderId;
public:
	/**
	 * @brief 构造函数，创建指定类型的着色器对象。
	 * @param shaderType 着色器类型，如 GL_VERTEX_SHADER。
	 */
	inline Shader(GLenum shaderType)
	{
		shaderId = glCreateShader(shaderType);
	}

	/**
	 * @brief 析构函数，删除底层着色器对象。
	 */
	inline ~Shader()
	{
		if(shaderId != 0)
			glDeleteShader(shaderId);
	}

	Shader() = delete;
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	/**
	 * @brief 移动构造函数，转移着色器所有权。
	 */
	inline Shader(Shader&& other) :
		shaderId(other.shaderId)
	{
		other.shaderId = 0;
	}

	/**
	 * @brief 移动赋值运算符，交换内部着色器 ID。
	 */
	inline Shader& operator=(Shader&& other)
	{
		std::swap(shaderId, other.shaderId);
		return *this;
	}

	/**
	 * @brief 隐式转换为 GLuint，返回着色器 ID。
	 */
	inline operator GLuint () const
	{
		return shaderId;
	}

	/**
	 * @brief 获取着色器 ID。
	 * @return OpenGL 着色器 ID。
	 */
	inline GLuint GetId() const
	{
		return shaderId;
	}

	std::string GetInfoLog() const;

	bool FromFile(const std::string& fileName);

	bool FromString(const std::string& source);
};

}// namespace GL

#endif
