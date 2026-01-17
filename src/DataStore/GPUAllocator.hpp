/**
 * @file GPUAllocator.hpp
 * @brief 声明在 GPU 缓冲上进行区间分配和回收的简单分配器。
 */

#ifndef GPU_ALLOCATOR_HPP
#define GPU_ALLOCATOR_HPP

#include <GL/glew.h>
#include <set>

/**
 * @brief 在一个固定大小的线性空间上管理空洞与分配的简易分配器。
 */
class GPUAllocator
{
private:
	GLuint max;

	/**
	 * @brief 表示一个可用空洞的起始偏移和大小。
	 */
	struct Hole
	{
		GLuint offset;
		GLuint size;

		Hole(GLuint _offset, GLuint _size = 0) :
			offset(_offset),
			size(_size)
		{
		}

		bool operator==(const Hole& rhs)
		{
			return offset == rhs.offset && size == rhs.size;
		}

		bool operator!=(const Hole& rhs)
		{
			return offset != rhs.offset || size != rhs.size;
		}
	};

	struct ByOffset
	{
		inline bool operator()(const Hole& lhs, const Hole& rhs) const
		{
			return lhs.offset < rhs.offset;
		}
	};

	struct ByLength
	{
		inline bool operator()(const Hole& lhs, const Hole& rhs) const
		{
			return lhs.size < rhs.size;
		}
	};

	std::set<Hole, ByOffset> holesByOffset;
	std::set<Hole, ByLength> holesByLength;

	void AddHole(GLuint offset, GLuint size);
public:
	/**
	 * @brief 构造分配器，指定可管理的最大空间大小。
	 * @param max 可分配的总字节数。
	 */
	GPUAllocator(GLuint max);
	~GPUAllocator();

	/**
	 * @brief 在缓冲空间中分配一段满足对齐要求的区域。
	 * @param size 需要的字节数。
	 * @param alignment 对齐字节数。
	 * @param value 输出参数，返回分配的偏移。
	 * @return 分配成功返回 true，失败返回 false。
	 */
	bool Allocate(GLuint size, GLuint alignment, GLuint* value);

	/**
	 * @brief 释放指定区间，使其重新成为空洞。
	 * @param offset 区间起始偏移。
	 * @param length 区间长度。
	 */
	void DeAllocate(GLuint offset, GLuint length);

	/**
	 * @brief 获取可管理空间的总大小。
	 * @return 最大字节数。
	 */
	GLuint GetSize() const
	{
		return max;
	}
};

#endif
