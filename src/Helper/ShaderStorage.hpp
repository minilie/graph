/**
 * @file ShaderStorage.hpp
 * @brief 封装 Shader Storage Buffer 绑定与管理的类声明。
 */

#ifndef SHADER_STORAGE_HPP
#define SHADER_STORAGE_HPP

#include <GL/glew.h>

#include "StaticCounter.hpp"
#include "../Log/Logger.h"

namespace GL
{
	class Program;
	class Buffer;
}

namespace GL {

/**
 * @brief 管理一个 Shader Storage Buffer 的绑定点及绑定操作。
 */
class ShaderStorage
{
private:
	StaticCounter<GLuint, ShaderStorage> bindingIndex;
public:
	/**
	 * @brief 构造函数，分配一个新的绑定点索引并输出调试信息。
	 */
	ShaderStorage()
	{
		Logger::Debug() << "Created shader storage buffer with binding index: " << bindingIndex.Get() << '\n';
	}

	void AttachToBlock(const Program& program, const GLuint index) const;

	void AttachBuffer(const Buffer& buffer);

	void AttachBufferRange(const Buffer& buffer, GLuint offset, GLuint size);

	/**
	 * @brief 获取当前使用的绑定点索引。
	 * @return 绑定点索引。
	 */
	GLuint GetBlockBinding() const
	{
		return bindingIndex;
	}
};

} //namespace GL

#endif //SHADER_STORAGE_HPP
