/**
 * @file MaterialParams.cpp
 * @brief 实现材质参数缓冲的绑定、写入与选择逻辑。
 */

#include "MaterialParams.h"
#include "../../Helper/Program.hpp"

/**
 * @brief 将材质统一缓冲绑定到指定着色器程序的统一变量块。
 * @param program 目标 OpenGL 程序对象。
 */
void MaterialParams::Bind(const GL::Program& program)
{
	bindingIndex.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingIndex.AttachBuffer(buffer.GetBuffer());
}

/**
 * @brief 向缓冲中写入一个新的材质并返回其索引。
 * @param material 材质颜色与参数。
 * @return 新材质在内部列表中的索引。
 */
size_t MaterialParams::Push(const ColorFormat& material)
{
	GLuint offset = buffer.Push(material, sizeof(ColorFormat));

	materials.emplace_back(offset, sizeof(ColorFormat));

	return materials.size() - 1;
}

/**
 * @brief 选中并绑定指定 ID 的材质到统一缓冲绑定点。
 * @param id 材质索引。
 */
void MaterialParams::UseMaterial(size_t id)
{
	bindingIndex.AttachBufferRange(buffer.GetBuffer(), materials[id].GetOffset(), materials[id].GetSize());
}
