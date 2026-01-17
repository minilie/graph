/**
 * @file SlotContainer.hpp
 * @brief 实现 SlotContainer 的模板成员函数。
 */

#include "SlotContainerDec.hpp"

/**
 * @brief 在容器中插入一个新元素，优先复用空闲槽位。
 * @tparam T 元素类型。
 * @param data 要插入的元素常量引用。
 * @return 插入元素所在槽位的索引。
 */
template<typename T>
std::size_t SlotContainer<T>::Push(const T& data)
{
	if(freeHead > 0)
	{
		std::size_t next = storage[freeHead].free.next;
		storage[freeHead].data = data;
		freeHead = next;
	}
	else
	{
		storage.push_back(data);
		return storage.size();
	}
}

/**
 * @brief 插入一个新元素的右值版本。
 * @tparam T 元素类型。
 * @param data 要插入的元素右值。
 * @return 插入元素所在槽位的索引。
 */
template<typename T>
std::size_t SlotContainer<T>::Push(T&& data)
{
	if(freeHead > 0)
	{
		std::size_t next = storage[freeHead].free.next;
		storage[freeHead].data = data;
		freeHead = next;
	}
	else
	{
		storage.push_back(data);
		return storage.size();
	}
}

/**
 * @brief 删除指定索引处的元素，将该槽位挂回空闲链表。
 * @tparam T 元素类型。
 * @param index 要删除的槽位索引。
 */
template<typename T>
void SlotContainer<T>::Erase(std::size_t index)
{
	storage[index].free.next = freeHead;
	freeHead = index;
}

/**
 * @brief 通过索引访问容器中的元素。
 * @tparam T 元素类型。
 * @param index 槽位索引。
 * @return 指定槽位中的元素引用。
 */
template<typename T>
T& SlotContainer<T>::operator[](std::size_t index)
{
	return storage[index].data;
}

/**
 * @brief 通过索引访问容器中的元素（常量版本）。
 * @tparam T 元素类型。
 * @param index 槽位索引。
 * @return 指定槽位中元素的常量引用。
 */
template<typename T>
const T& SlotContainer<T>::operator[](std::size_t index) const
{
	return storage[index].data;
}
