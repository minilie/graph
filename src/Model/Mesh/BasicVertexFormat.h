/**
 * @file BasicVertexFormat.h
 * @brief 声明基础顶点格式，用于存储位置、法线与纹理坐标。
 */

#ifndef BASIC_VERTEX_FORMAT_H
#define BASIC_VERTEX_FORMAT_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

/**
 * @brief 用于渲染基本三维模型的顶点格式。
 */
struct BasicVertexFormat
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;

	/**
	 * @brief 通过常量引用初始化顶点属性。
	 * @param p 顶点位置。
	 * @param n 顶点法线。
	 * @param UV 顶点纹理坐标。
	 */
	BasicVertexFormat(const glm::vec3& p, const glm::vec3& n, const glm::vec2& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

	/**
	 * @brief 通过右值引用初始化顶点属性，便于移动构造。
	 * @param p 顶点位置。
	 * @param n 顶点法线。
	 * @param UV 顶点纹理坐标。
	 */
	BasicVertexFormat(glm::vec3&& p, glm::vec3&& n, glm::vec2&& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

};

#endif //BASIC_0VERTEXT_FORMAT_H
