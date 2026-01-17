/**
 * @file IndexedLinkedList.hpp
 * @brief 实现 IndexedLinkedList 的迭代器接口。
 */

#include "IndexedLinkedDec.hpp"

// --- iterator ---

/**
 * @brief 通过指针访问当前迭代器指向的元素。
 */
template<typename T>
T* IndexedLinkedList<T>::iterator::operator->() const
{
	return &parent->storage[index];
}

/**
 * @brief 解引用迭代器，返回当前元素引用。
 */
template<typename T>
T& IndexedLinkedList<T>::iterator::operator*() const
{
	return &parent->storage[index];
}

/**
 * @brief 后置自增，将迭代器移动到下一个元素。
 */
template<typename T>
typename IndexedLinkedList<T>::iterator& IndexedLinkedList<T>::iterator::operator++(int)
{
	index = *parent[index].next;
	return *this;
}

/**
 * @brief 前置自增，将迭代器移动到下一个元素并返回旧值。
 */
template<typename T>
typename IndexedLinkedList<T>::iterator IndexedLinkedList<T>::iterator::operator++()
{
	iterator copy = *this;
	operator++(0);
	return copy;
}

/**
 * @brief 后置自减，将迭代器移动到前一个元素。
 */
template<typename T>
typename IndexedLinkedList<T>::iterator& IndexedLinkedList<T>::iterator::operator--(int)
{
	index = *parent[index].prev;
	return *this;
}

/**
 * @brief 前置自减，将迭代器移动到前一个元素并返回旧值。
 */
template<typename T>
typename IndexedLinkedList<T>::iterator IndexedLinkedList<T>::iterator::operator--()
{
	iterator copy = *this;
	operator--(0);
	return copy;
}

/**
 * @brief 判断两个可写迭代器是否相等。
 */
template<typename T>
bool IndexedLinkedList<T>::iterator::operator==(const iterator& other) const
{
	return other.parent == parent && other.index == index;
}

/**
 * @brief 判断两个可写迭代器是否不相等。
 */
template<typename T>
bool IndexedLinkedList<T>::iterator::operator!=(const iterator& other) const
{
	return other.parent != parent || other.index != index;
}

// --- const_iterator ---

/**
 * @brief 通过指针访问当前 const 迭代器指向的元素。
 */
template<typename T>
T const * IndexedLinkedList<T>::const_iterator::operator->() const
{
	return &parent->storage[index];
}

/**
 * @brief 解引用 const 迭代器，返回当前元素常量引用。
 */
template<typename T>
const T& IndexedLinkedList<T>::const_iterator::operator*() const
{
	return &parent->storage[index];
}

/**
 * @brief 后置自增，将 const 迭代器移动到下一个元素。
 */
template<typename T>
typename IndexedLinkedList<T>::const_iterator& IndexedLinkedList<T>::const_iterator::operator++(int)
{
	index = *parent[index].next;
	return *this;
}

/**
 * @brief 前置自增，将 const 迭代器移动到下一个元素并返回旧值。
 */
template<typename T>
typename IndexedLinkedList<T>::const_iterator IndexedLinkedList<T>::const_iterator::operator++()
{
	iterator copy = *this;
	operator++(0);
	return copy;
}

/**
 * @brief 后置自减，将 const 迭代器移动到前一个元素。
 */
template<typename T>
typename IndexedLinkedList<T>::const_iterator& IndexedLinkedList<T>::const_iterator::operator--(int)
{
	index = *parent[index].prev;
	return *this;
}

/**
 * @brief 前置自减，将 const 迭代器移动到前一个元素并返回旧值。
 */
template<typename T>
typename IndexedLinkedList<T>::const_iterator IndexedLinkedList<T>::const_iterator::operator--()
{
	iterator copy = *this;
	operator--(0);
	return copy;
}

/**
 * @brief 判断 const 迭代器与普通迭代器是否指向同一元素。
 */
template<typename T>
bool IndexedLinkedList<T>::const_iterator::operator==(const iterator& other) const
{
	return other.parent == parent && other.index == index;
}

/**
 * @brief 判断 const 迭代器与普通迭代器是否指向不同元素。
 */
template<typename T>
bool IndexedLinkedList<T>::const_iterator::operator!=(const iterator& other) const
{
	return other.parent != parent || other.index != index;
}
