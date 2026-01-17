/**
 * @file Program.hpp
 * @brief 封装 OpenGL Program 对象的创建、链接与使用接口。
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>
#include <memory>

#include "Shader.hpp"

namespace GL
{

/**
 * @brief 对 OpenGL 程序对象的简单封装，提供常用操作方法。
 */
class Program
{
private:
	GLuint programID;
public:
	/**
	 * @brief 构造函数，创建一个空的 OpenGL 程序对象。
	 */
	Program()
	{
		programID = glCreateProgram();
	}

	/**
	 * @brief 预留接口，目前未使用。
	 */
	inline void CreateName()
	{
	}

	/**
	 * @brief 通过已有的程序 ID 构造包装对象。
	 * @param p 已存在的 OpenGL 程序 ID。
	 */
	inline explicit Program(GLuint p) :
		programID(p)
	{
	}

	/**
	 * @brief 析构函数，自动销毁底层程序对象。
	 */
	inline ~Program()
	{
		Destroy();
	}

	/**
	 * @brief 获取底层程序 ID。
	 * @return OpenGL 程序 ID。
	 */
	inline GLuint Get() const
	{
		return programID;
	}

	/**
	 * @brief 解引用运算符，返回程序 ID。
	 */
	inline GLuint operator*() const
	{
		return programID;
	}

	/**
	 * @brief 转换为 bool，表示链接状态是否成功。
	 */
	inline operator bool ()
	{
		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		return result == GL_TRUE;
	}

	/**
	 * @brief 取反运算符，表示链接是否失败。
	 */
	inline bool operator ! ()
	{
		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		return result != GL_TRUE;
	}

	/**
	 * @brief 获取指定统一变量的位置。
	 * @param name uniform 名称。
	 * @return 位置索引。
	 */
	inline GLuint GetUniformLocation(const char* name) const
	{
		return glGetUniformLocation(programID, name);
	}

	/**
	 * @brief 获取统一变量块索引。
	 * @param name 块名称。
	 * @return 块索引。
	 */
	inline GLuint GetUniformBlockIndex(const char* name) const
	{
		return glGetUniformBlockIndex(programID, name);
	}

	/**
	 * @brief 获取 Shader Storage Block 的索引。
	 * @param name 块名称。
	 * @return 资源索引。
	 */
	inline GLuint GetShaderStorageBlockIndex(const char* name) const
	{
		return glGetProgramResourceIndex(programID, GL_SHADER_STORAGE_BLOCK, name);
	}

	/**
	 * @brief 将一个编译好的着色器对象附加到该程序上。
	 * @param shader 着色器对象。
	 */
	inline void AttachShader(const Shader& shader)
	{
		glAttachShader(programID, shader.GetId());
	}

	/**
	 * @brief 链接当前程序。
	 * @return 链接成功返回 true，否则返回 false。
	 */
	inline bool Link()
	{
		GLint result = GL_FALSE;

		glLinkProgram(programID);
		glGetProgramiv(programID, GL_LINK_STATUS, &result);

		return result == GL_TRUE;
	}

	/**
	 * @brief 将该程序设置为当前使用的 OpenGL 程序。
	 */
	inline void Use() const
	{
		glUseProgram(programID);
	}

	/**
	 * @brief 取消当前使用的程序。
	 */
	inline void Unuse() const
	{
		glUseProgram(0);
	}

	/**
	 * @brief 销毁底层 OpenGL 程序对象。
	 */
	inline void Destroy()
	{
		glDeleteProgram(programID);
	}

	/**
	 * @brief 获取程序的链接日志信息。
	 * @return 日志字符串。
	 */
	inline std::string GetInfoLog()
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::unique_ptr<char> errorMessage(new char[infoLogLength]);
		glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage.get());

		return std::string(errorMessage.get());
	}

	bool VsFsProgram( 	const std::string& vertexShaderName,
						const std::string& fragmentShaderName);
};

}// namespace GL;

#endif //PROGRAM_H
