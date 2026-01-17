/**
 * @file IndexedLinkedDec.hpp
 * @brief 声明基于索引实现的链表及其迭代器。
 */

#ifndef INDEXED_LINKED_LIST_HPP
#define INDEXED_LINKED_LIST_HPP

#include <vector>

#include "SlotContainer.hpp"

/**
 * @brief 使用数组存储节点，并通过索引链接形成链表的容器。
 * @tparam T 存储的元素类型。
 */
template<typename T>
class IndexedLinkedList
{
private:
	class Node
	{
		T data;
		std::size_t prev;
		std::size_t next;
	};

	std::vector<Node> storage;

	/**
	 * @brief 可修改迭代器，实现对链表的顺序遍历。
	 */
	class iterator
	{
	private:
		IndexedLinkedList* parent;
		std::size_t index;

		iterator(IndexedLinkedList* _parent, std::size_t _index) :
			parent(_parent),
			index(_index)
		{
		}
	public:
		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;

		T* operator->() const;
		T& operator*() const;
		iterator& operator++(int);
		iterator operator++();
		iterator& operator--(int);
		iterator operator--();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
	};

	/**
	 * @brief 只读迭代器，提供 const 版本的访问。
	 */
	class const_iterator
	{
	private:
		IndexedLinkedList const* parent;
		std::size_t index;

		const_iterator(IndexedLinkedList const* _parent, std::size_t _index) :
			parent(_parent),
			index(_index)
		{
		}
	public:
		const_iterator(const const_iterator&) = default;
		const_iterator& operator=(const const_iterator&) = default;

		T const * operator->() const;
		const T& operator*() const;
		const_iterator& operator++(int);
		const_iterator operator++();
		const_iterator& operator--(int);
		const_iterator operator--();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
	};

	SlotContainer<T> container;

	std::size_t front;
	std::size_t back;
public:
	/**
	 * @brief 构造函数，初始化表头与表尾索引。
	 */
	IndexedLinkedList() :
		front(0),
		back(0)
	{
	}

	
};

#endif
