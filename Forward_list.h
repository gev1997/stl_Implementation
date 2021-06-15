#ifndef FWD_LIST_H
#define FWD_LIST_H

#include <iostream>
#include <stdexcept>

namespace STL {

template <typename T>
struct Node {
	T data;
	Node<T>* next;
};

template <typename T>
class forward_list
{
public:
	forward_list() : m_head(nullptr) {}
	
	forward_list(const forward_list<T>& oth) : m_head(nullptr)
	{
		if (oth.m_head == nullptr) {
			return;
		}

		this->m_head = new Node<T>;

		Node<T>* tmp = m_head;
		Node<T>* oth_tmp = oth.m_head;

		while (oth_tmp != nullptr) {  
			tmp->data = oth_tmp->data;

			if (oth_tmp->next == nullptr) {
				break;
			}
			tmp->next = new Node<T>;

			tmp = tmp->next;
			oth_tmp = oth_tmp->next;
		}
		tmp->next = nullptr;
	}

	~forward_list()
	{
		Node<T>* tmp = m_head;
		while(tmp != nullptr) {
			tmp = m_head->next;
			delete m_head;
			m_head = tmp;
		}
	}

	forward_list<T>& operator=(const forward_list<T>& oth)
	{
		if (this == &oth) {
			return *this;
		}
		if (oth.m_head == nullptr) {
			return *this;
		}

		this->m_head = new Node<T>;

		Node<T>* tmp = m_head;
		Node<T>* oth_tmp = oth.m_head;

		while (oth_tmp != nullptr) {  
			tmp->data = oth_tmp->data;

			if (oth_tmp->next == nullptr) {
				break;
			}
			tmp->next = new Node<T>;

			tmp = tmp->next;
			oth_tmp = oth_tmp->next;
		}
		tmp->next = nullptr;

		return *this;
	}

	void push_back(T element)
	{
		Node<T>* new_node = new Node<T>;
		new_node->data = element;
		new_node->next = nullptr;

		if (m_head == nullptr)
		{
			m_head = new_node;
			return;
		}

		Node<T>* current = m_head;
		while(current->next != nullptr)
		{
			current = current->next;
		}

		current->next = new_node;
	}

	void push_front(T element) {
		Node<T>* new_node = new Node<T>;
		new_node->data = element;

		if (m_head == nullptr)
		{
			m_head = new_node;
			new_node->next = nullptr;
			return;
		}

		new_node->next = m_head;
		m_head = new_node;
	}

	void insert_after(int position, T element) 
	{
		if (size() < position) {
			throw std::invalid_argument("out of range");
		}

		Node<T>* new_node = new Node<T>;
		new_node->data = element;

		if (position == 0) {
			push_front(element);
		}
		else if (position == size()) {
			push_back(element);
		}
		else {
			Node<T>* tmp = m_head;
			for (int i = 0; i < position - 1; ++i) {
				tmp = tmp->next;
			}
			
			new_node->next = tmp->next;
			tmp->next = new_node;
		}
	}

	void print() 
	{
		Node<T>* tmp = m_head;
		while (tmp != nullptr) {
			std::cout << tmp->data << std::endl;
			tmp = tmp->next;
		}
	}

private:
	int size() {
		Node<T>* tmp = m_head;

		int count = 0;
		while (tmp != nullptr) {
			++count;
			tmp = tmp->next;
		}

		return count;
	}

	Node<T>* m_head;
};

}

#endif //FWD_LIST_H
