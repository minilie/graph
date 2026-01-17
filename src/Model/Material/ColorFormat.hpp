/**
 * @file ColorFormat.hpp
 * @brief 声明用于描述材质颜色属性的数据结构。
 */

#ifndef COLOR_FORMAT_H
#define COLOR_FORMAT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * @brief 存储环境光、漫反射、高光颜色及高光指数的材质颜色格式。
 */
struct ColorFormat
{
	alignas(16) glm::vec3 ambientColor;

	alignas(16) glm::vec3 diffuseColor;

	alignas(16) glm::vec3 specularColor;
	float specularExponent;

	ColorFormat() = default;

	/**
	 * @brief 通过颜色和高光指数初始化材质。
	 * @param a 环境光颜色。
	 * @param d 漫反射颜色。
	 * @param s 高光颜色。
	 * @param sE 高光指数。
	 */
	ColorFormat(const glm::vec3& a, const glm::vec3& d, const glm::vec3& s, const float sE) :
		ambientColor(a),
		diffuseColor(d),
		specularColor(s),
		specularExponent(sE)
	{
	}
};

#endif //COLOR_FORMAT_H
