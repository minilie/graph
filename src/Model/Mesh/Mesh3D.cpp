/**
 * @file Mesh3D.cpp
 * @brief 实现 Mesh3D 的构造与绘制接口。
 */

#include "Mesh3D.hpp"

/**
 * @brief 构造网格对象，记录其在顶点/索引缓冲中的位置与类型信息。
 */
Mesh3D::Mesh3D(GLint _vertexOffset, GLuint _vertexSize, void* _indexPointer, GLuint _indexCount, GLenum _type) :
	vertexOffset(_vertexOffset),
	vertexSize(_vertexSize),
	indexPointer(_indexPointer),
	indexCount(_indexCount),
	type(_type)
{
}

/**
 * @brief 使用 glDrawElementsBaseVertex 按索引绘制网格。
 */
void Mesh3D::Draw() const
{
	glDrawElementsBaseVertex
	(
		GL_TRIANGLES,
		indexCount,
		type,
		indexPointer,
		vertexOffset
	);
}

/**
 * @brief 获取顶点缓冲偏移。
 * @return 顶点偏移。
 */
GLint 	Mesh3D::GetOffset() const
{
	return vertexOffset;
}

/**
 * @brief 获取顶点数据占用的字节数。
 * @return 顶点数据大小。
 */
GLuint 	Mesh3D::GetSize() const
{
	return vertexSize;
}

/**
 * @brief 获取索引缓冲起始指针。
 * @return 索引指针。
 */
void * 	Mesh3D::GetIndexPointer() const
{
	return indexPointer;
}

/**
 * @brief 获取索引数量。
 * @return 索引个数。
 */
GLuint 	Mesh3D::GetCount() const
{
	return indexCount;
}
