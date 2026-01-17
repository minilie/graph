/**
 * @file Mesh3D.hpp
 * @brief 声明用于绘制三维网格的 Mesh3D 类。
 */

#ifndef MESH3D_H
#define MESH3D_H

#include <GL/glew.h>

/**
 * @brief 封装顶点缓冲与索引缓冲中一个网格片段的信息，并负责绘制。
 */
class Mesh3D
{
private:
	GLint vertexOffset;
	GLuint vertexSize; // size taken on vertex buffer for deallocation

	void* indexPointer;
	GLuint indexCount;

	GLenum type;

public:
	/**
	 * @brief 通过顶点缓冲偏移、大小和索引信息构造网格对象。
	 * @param _vertexOffset 顶点缓冲中的起始偏移。
	 * @param _vertexSize 顶点缓冲占用的大小（字节）。
	 * @param _indexPointer 索引缓冲中的起始指针。
	 * @param _indexCount 索引数量。
	 * @param _type 索引类型（如 GL_UNSIGNED_SHORT）。
	 */
	Mesh3D(GLint _vertexOffset, GLuint _vertexSize, void* _indexPointer, GLuint _indexCount, GLenum _type = GL_UNSIGNED_SHORT);

	Mesh3D(const Mesh3D&) = delete;
	Mesh3D(Mesh3D&&) = default;

	Mesh3D& operator=(const Mesh3D&) = delete;

	Mesh3D& operator=(Mesh3D&&) = default;

	void Draw() const;

	GLint GetOffset() const;
	GLuint GetSize() const;
	void * GetIndexPointer() const;
	GLuint GetCount() const;
};

#endif //MESH3D_H
