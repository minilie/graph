/**
 * @file Material.hpp
 * @brief 声明描述材质数据在统一缓冲中偏移和大小的辅助类。
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/glew.h>

/**
 * @brief 表示一个材质在缓冲中的存储位置与大小。
 */
class Material
{
private:
	GLuint offset;
	GLuint size;
public:
	/**
	 * @brief 通过缓冲偏移和大小构造材质描述。
	 * @param _offset 缓冲中的起始偏移。
	 * @param _size 材质数据占用的字节数。
	 */
	Material(GLuint _offset, GLuint _size) :
		offset(_offset),
		size(_size)
	{
	}

	/**
	 * @brief 获取缓冲偏移。
	 * @return 起始偏移（字节）。
	 */
	GLuint GetOffset()
	{
		return offset;
	}

	/**
	 * @brief 获取材质数据大小。
	 * @return 材质大小（字节）。
	 */
	GLuint GetSize()
	{
		return size;
	}
};

#endif //MATERIAL_HPP
