/**
 * @file ManagedBuffer.hpp
 * @brief 声明带简单分配器的 GPU 缓冲管理类。
 */

#ifndef MANAGED_BUFFER_HPP
#define MANAGED_BUFFER_HPP

#include "GPUAllocator.hpp"
#include "../Helper/Buffer.hpp"

/**
 * @brief 将 GPUAllocator 与具体的 GL 缓冲封装在一起的管理类。
 */
class ManagedBuffer
{
private:
	GPUAllocator allocator;
	GL::Buffer buffer;
public:
	/**
	 * @brief 构造函数，创建指定大小与用法的 GPU 缓冲。
	 * @param size 缓冲大小（字节）。
	 * @param usage OpenGL 缓冲用法标志。
	 */
	ManagedBuffer(GLuint size, GLenum usage) :
		allocator(size)
	{
		buffer.BufferData(size, nullptr, usage);
	}

	/**
	 * @brief 在缓冲中保留一段未初始化的空间。
	 * @param size 需要的字节数。
	 * @param alignment 对齐字节数。
	 * @return 分配得到的偏移。
	 */
	GLuint Reserve(GLuint size, GLuint alignment)
	{
		GLuint offset = Allocate(size, alignment);
		buffer.BufferSubData(offset, size, nullptr);

		return offset;
	}

	/**
	 * @brief 向缓冲中写入一段原始数据。
	 * @param size 数据大小。
	 * @param data 数据指针。
	 * @param alignment 对齐要求。
	 * @return 写入数据在缓冲中的偏移。
	 */
	GLuint Push(GLuint size, void const * data, GLuint alignment)
	{
		GLuint offset = Allocate(size, alignment);
		buffer.BufferSubData(offset, size, data);

		return offset;
	}

	/**
	 * @brief 以任意类型对象的形式向缓冲中写入数据。
	 * @tparam T 数据类型。
	 * @param data 要写入的对象。
	 * @param alignment 对齐要求。
	 * @return 写入数据的偏移。
	 */
	template <typename T>
	GLuint Push(const T& data, GLuint alignment)
	{
		return Push(sizeof(data), &data, alignment);
	}

	/**
	 * @brief 以数组形式向缓冲中写入数据。
	 * @tparam T 元素类型。
	 * @param data 数据数组。
	 * @param alignment 对齐要求。
	 * @return 写入数据的偏移。
	 */
	template <typename T>
	GLuint Push(const std::vector<T>& data, GLuint alignment)
	{
		return Push(sizeof(data[0]) * data.size(), data.data(), alignment);
	}

	/**
	 * @brief 仅执行空间分配，不写入数据。
	 * @param size 需要的空间大小。
	 * @param alignment 对齐要求。
	 * @return 分配得到的偏移。
	 */
	GLuint Allocate(GLuint size, GLuint alignment)
	{
		GLuint offset;
		allocator.Allocate(size, alignment, &offset);

		return offset;
	}

	/**
	 * @brief 释放之前分配的空间。
	 * @param offset 起始偏移。
	 * @param length 长度。
	 */
	void Free(GLuint offset, GLuint length)
	{
		allocator.DeAllocate(offset, length);
	}

	/**
	 * @brief 获取内部 GL 缓冲对象引用。
	 * @return 缓冲对象引用。
	 */
	GL::Buffer& GetBuffer()
	{
		return buffer;
	}

	/**
	 * @brief 获取内部 GL 缓冲对象常量引用。
	 * @return 常量缓冲引用。
	 */
	const GL::Buffer& GetBuffer() const
	{
		return buffer;
	}
};

#endif
