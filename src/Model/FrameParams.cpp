/**
 * @file FrameParams.cpp
 * @brief 实现 FrameParams 与 OpenGL 程序之间的绑定与更新。
 */

#include "FrameParams.h"

#include "../Helper/Program.hpp"
#include "../Log/Logger.h"

/**
 * @brief 将该帧参数缓冲绑定到指定着色器程序的统一变量块。
 * @param program 目标 OpenGL 程序对象。
 */
void FrameParams::Bind(const GL::Program& program)
{
	Logger::Debug() << "Fp " << blockName << " " << program.GetUniformBlockIndex(blockName) << '\n';
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingPoint.AttachBuffer(buffer);
}

/**
 * @brief 将当前存储的视图与投影矩阵更新到 GPU 缓冲。
 */
void FrameParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}
