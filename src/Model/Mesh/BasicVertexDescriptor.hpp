/**
 * @file BasicVertexDescriptor.hpp
 * @brief 声明基础顶点格式的 VAO 描述器，封装顶点属性布局。
 */

#ifndef BASIC_VERTEX_DESCRIPTOR_HPP
#define BASIC_VERTEX_DESCRIPTOR_HPP

#include "../../Helper/VertexArray.hpp"
#include "../../Helper/VertexArrayBinding.hpp"
#include "../../Helper/Buffer.hpp"
#include "../../Helper/TypeEnum.hpp"

#include "BasicVertexFormat.h"

#include <cstddef>

/**
 * @brief 为 BasicVertexFormat 设置顶点属性布局的封装类。
 */
class BasicVertexDescriptor : public GL::VertexArray
{
private:
	GL::VertexArrayBinding binding;
public:
	/**
	 * @brief 构造函数，初始化顶点属性布局（位置、法线、UV）。
	 */
	BasicVertexDescriptor()
	{
		//First attrribute
		EnableAttrib(0);
		FormatAttrib(0, 3, GL::TypeEnum<float>::value, false, offsetof(BasicVertexFormat, pos));
		binding.BindAttrib(*this, 0);

		//Set Second attribute
		EnableAttrib(1);
		FormatAttrib(1, 3, GL::TypeEnum<float>::value, false, offsetof(BasicVertexFormat, norm));
		binding.BindAttrib(*this, 1);

		//Set Third attribute
		EnableAttrib(2);
		FormatAttrib(2, 2, GL::TypeEnum<float>::value, false, offsetof(BasicVertexFormat, uv));
		binding.BindAttrib(*this, 2);
	}

	/**
	 * @brief 绑定顶点缓冲到 VAO，设置步长等信息。
	 * @param buffer 顶点缓冲对象。
	 */
	inline void AttachVertex(const GL::Buffer& buffer)
	{
		binding.BindBuffer(*this, buffer, 0, sizeof(BasicVertexFormat));
	}

	/**
	 * @brief 绑定当前 VAO。
	 */
	inline void Bind() const
	{
		VertexArray::Bind();
	}

	/**
	 * @brief 获取底层 VAO 句柄。
	 * @return OpenGL VAO 标识。
	 */
	inline GLint Get() const
	{
		return id;
	}
};

#endif //BASIC_VERTEX_DESCRIPTOR_HPP
