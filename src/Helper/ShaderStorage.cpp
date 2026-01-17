/**
 * @file ShaderStorage.cpp
 * @brief 实现 ShaderStorage 的缓冲绑定与块绑定逻辑。
 */

#include "ShaderStorage.hpp"

#include "Program.hpp"
#include "Buffer.hpp"

namespace GL {

/**
 * @brief 将缓冲绑定到 Shader Storage Buffer 的整个绑定点上。
 * @param buffer 要绑定的缓冲对象。
 */
void ShaderStorage::AttachBuffer(const Buffer& buffer)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingIndex, buffer.GetId());
}

/**
 * @brief 将缓冲的一个区间绑定到 Shader Storage Buffer 上。
 * @param buffer 缓冲对象。
 * @param offset 起始偏移。
 * @param size 绑定的大小。
 */
void ShaderStorage::AttachBufferRange(const Buffer &buffer, GLuint offset, GLuint size)
{
	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, bindingIndex, buffer.GetId(), offset, size);
}

/**
 * @brief 将绑定点与指定程序中的 Shader Storage Block 建立关联。
 * @param program OpenGL 程序对象。
 * @param index 块索引。
 */
void ShaderStorage::AttachToBlock(const Program& program, const GLuint index) const
{
	//Logger::Debug() << "shader storage buffer bind:" << bindingIndex << " -> program" << program.Get() << ":"  << index <<  '\n';

	glShaderStorageBlockBinding(program.Get(), index, bindingIndex);
}

}// namspace GL
