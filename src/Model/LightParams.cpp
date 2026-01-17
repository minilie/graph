/**
 * @file LightParams.cpp
 * @brief 实现光源参数与 OpenGL 程序之间的绑定和更新。
 */

#include "LightParams.h"
#include "../Helper/Program.hpp"

/**
 * @brief 将当前光源数据写入 GPU 缓冲。
 */
void LightParams::Update()
{
	buffer.BufferData(data, GL_STATIC_DRAW);
}

/**
 * @brief 将光源参数缓冲绑定到指定着色器程序的统一变量块。
 * @param program 目标 OpenGL 程序对象。
 */
void LightParams::Bind(const GL::Program& program)
{
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingPoint.AttachBuffer(buffer);
}
