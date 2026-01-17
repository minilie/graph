/**
 * @file Buffer.hpp
 * @brief 封装 OpenGL 缓冲对象的创建与数据更新接口。
 */

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <GL/glew.h>
#include <vector>

#include "../Log/Logger.h"

namespace GL {

/**
 * @brief 对 OpenGL 缓冲对象的简单封装，提供常见数据上传函数。
 */
class Buffer
{
private:
	GLuint id;
public:
	/**
	 * @brief 构造函数，创建一个新的 OpenGL 缓冲对象。
	 */
	Buffer()
	{
		glCreateBuffers(1, &id);
		Logger::Debug() << "Created glBuffer with id: " << id << '\n';
	}

	/**
	 * @brief 获取底层缓冲对象的 ID。
	 * @return OpenGL 缓冲 ID。
	 */
	GLint GetId() const
	{
		return id;
	}

	/**
	 * @brief 将缓冲绑定到指定目标上。
	 * @param target OpenGL 缓冲绑定目标。
	 */
	void Bind(GLenum target) const
	{
		glBindBuffer(target, id);
	}

	/**
	 * @brief 为缓冲分配存储并可选上传初始数据。
	 * @param size 数据大小（字节）。
	 * @param data 数据指针，为空则仅分配空间。
	 * @param usage OpenGL 使用模式。
	 */
	void BufferData(GLuint size, const void* data, GLenum usage)
	{
		glNamedBufferData(id, size, data, usage);
	}

	/**
	 * @brief 以任意类型对象的形式为缓冲分配存储并上传数据。
	 * @tparam T 数据类型。
	 * @param data 要上传的对象。
	 * @param usage OpenGL 使用模式。
	 */
	template<typename T>
	void BufferData(const T& data, GLenum usage)
	{
		BufferData(sizeof(T), reinterpret_cast<const void *>(&data), usage);
	}

	/**
	 * @brief 以数组形式为缓冲分配存储并上传数据。
	 * @tparam T 元素类型。
	 * @param vector 要上传的数据数组。
	 * @param usage OpenGL 使用模式。
	 */
	template<typename T>
	void BufferData(const std::vector<T>& vector, GLenum usage)
	{
		BufferData(vector.size() * sizeof(T), reinterpret_cast<const void *>(vector.data()), usage);
	}

	/**
	 * @brief 向已存在的缓冲指定偏移处写入子数据。
	 * @param offset 起始偏移。
	 * @param size 写入大小。
	 * @param data 数据指针。
	 */
	void BufferSubData(GLuint offset, GLsizeiptr size, const void* data)
	{
		glNamedBufferSubData(id, offset, size, data);
	}

	/**
	 * @brief 向缓冲中写入一个对象作为子数据。
	 * @tparam T 数据类型。
	 * @param offset 起始偏移。
	 * @param data 对象引用。
	 */
	template<typename T>
	void BufferSubData(GLuint offset, const T& data)
	{
		BufferSubData(offset, sizeof(data), reinterpret_cast<void *>(&data));
	}

	/**
	 * @brief 以数组形式向缓冲中写入子数据。
	 * @tparam T 元素类型。
	 * @param offset 起始偏移。
	 * @param vector 数据数组。
	 * @param usage 未使用，仅保留参数以保持接口一致。
	 */
	template<typename T>
	void BufferSubData(GLuint offset, const std::vector<T>& vector, GLenum usage)
	{
		BufferSubData(offset, vector.size() * sizeof(T), reinterpret_cast<const void *>(vector.data()));
	}

	/**
	 * @brief 初始化一个给定大小的空缓冲。
	 * @param size 大小（字节）。
	 * @param usage OpenGL 使用模式。
	 */
	void InitEmpty(GLuint size, GLenum usage)
	{
		BufferData(size, nullptr, usage);
	}

	/**
	 * @brief 析构函数，删除底层 OpenGL 缓冲对象。
	 */
	~Buffer()
	{
		glDeleteBuffers(1, &id);
	}

};

}// namespace GL

#endif
