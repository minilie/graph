/**
 * @file GPUAllocator.cpp
 * @brief 实现 GPUAllocator 的区间分配与回收逻辑。
 */

#include "GPUAllocator.hpp"

/**
 * @brief 构造分配器，初始时所有空间作为一个大空洞。
 */
GPUAllocator::GPUAllocator(GLuint _max) :
	max(_max)
{
	holesByOffset.emplace(0, max);
	holesByLength.emplace(0, max);
}

/**
 * @brief 析构函数，当前未做额外工作。
 */
GPUAllocator::~GPUAllocator()
{
}

/**
 * @brief 在当前空洞集合中查找并分配一段满足大小与对齐要求的空间。
 * @param size 需要的空间大小。
 * @param alignment 对齐字节数。
 * @param value 输出参数，返回分配的起始偏移。
 * @return 分配成功返回 true，若没有合适空洞则返回 false。
 */
bool GPUAllocator::Allocate(GLuint size, GLuint alignment, GLuint* value)
{
	GLuint alignOffset;
	auto iter = holesByLength.lower_bound(size);
	while( iter != holesByLength.end())
	{
		alignOffset = (alignment - iter->offset % alignment) % alignment;
		if(alignOffset + size <= iter->size)
			break;
		++iter;
	}
	if(iter == holesByLength.end())
		return false;

	if(alignOffset > 0)
		AddHole(iter->offset, alignOffset);
	if(alignOffset + size < iter->size)
		AddHole(iter->offset + alignOffset + size, iter->size - alignOffset - size);

	holesByOffset.erase(Hole(iter->offset, iter->size));
	holesByLength.erase(iter);

	*value = iter->offset + alignOffset;

	return true;
};

/**
 * @brief 向空洞集合中加入一个新的空洞。
 * @param offset 空洞起始偏移。
 * @param size 空洞长度。
 */
void GPUAllocator::AddHole(GLuint offset, GLuint size)
{
	holesByLength.emplace(offset, size);
	holesByOffset.emplace(offset, size);
}

/**
 * @brief 释放指定区间，并与相邻空洞合并以减少碎片。
 * @param offset 起始偏移。
 * @param size 区间大小。
 */
void GPUAllocator::DeAllocate(GLuint offset, GLuint size)
{
	GLuint newOffset = offset, newSize = size;

	auto before = holesByOffset.lower_bound(Hole(offset, size));
	--before;
	if(before != holesByOffset.end() && before->offset + before->size >= offset)
	{
		newOffset = before->offset;
		newSize += before->size;

		holesByLength.erase(Hole(before->offset, before->size));
		holesByOffset.erase(before);
	}

	auto after = holesByOffset.upper_bound(Hole(offset, size));
	if(after != holesByOffset.end() && offset + size >= after->offset)
	{
		newSize += after->size;

		holesByLength.erase(Hole(after->offset, after->size));
		holesByOffset.erase(after);
	}

	AddHole(newOffset, newSize);
}
