/**
 * @file SlotContainerDec.hpp
 * @brief 声明基于槽位的容器，支持存储与复用元素位置。
 */

#ifndef SLOT_CONTAINER_HPP
#define SLOT_CONTAINER_HPP

#include <vector>

/**
 * @brief 一个简单的槽位容器，通过空闲链表实现删除后位置的复用。
 * @tparam T 存储的元素类型。
 */
template<typename T>
class SlotContainer
{
private:
	/**
	 * @brief 表示空闲节点的结构，仅存储下一个空位索引。
	 */
	class alignas(T) EmptyNode
	{
		std::size_t next;
	};

	/**
	 * @brief 存储节点的联合体，可以是有效数据或空闲节点信息。
	 */
	using Node = union {
		T data;
		EmptyNode free;
	};

	std::vector<Node> storage;

	std::size_t freeHead;
public:
	std::size_t Push(const T& data);
	std::size_t Push(T&& data);
	void Erase(std::size_t index);

	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

	/**
	 * @brief 返回当前占用的槽位数量。
	 */
	std::size_t Size()
	{
	};

	/**
	 * @brief 构造函数，初始化存储与空闲链表。
	 */
	SlotContainer() :
		storage(1)
	{
		storage.push_back(EmptyNode(0));
	}


	SlotContainer(const SlotContainer&) = default;
	SlotContainer(SlotContainer&&) = default;

	SlotContainer& operator=(const SlotContainer&) = default;
	SlotContainer& operator=(SlotContainer&&) = default;

	~SlotContainer() = default;
};

#endif
