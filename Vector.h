#ifndef VECTOR_H
#define VECTOR_H

namespace STL {
    
#include <stdexcept>

template <typename T>
class vector 
{
public:
	vector() : m_size{0}, m_capacity{4}, m_buffer{new T[m_capacity]}
	{}
	vector(int input_capacity) : m_size{0}, m_capacity{input_capacity}, m_buffer{new T[m_capacity]}
	{}

	vector(const vector& oth){
		m_size = oth.m_size;
		m_capacity = oth.m_capacity;

		m_buffer = new T[m_capacity];

		for (int i = 0; i < m_size; ++i) {
			m_buffer[i] = oth.m_buffer[i];
		}
	}

	vector& operator=(const vector& rhs) {
		m_size = rhs.m_size;
		m_capacity = rhs.m_capacity;

		T* tmp = new T[m_capacity];
		for (int i = 0; i < m_size; ++i) {
			tmp[i] = rhs.m_buffer[i];
		}

		delete[] m_buffer;
		m_buffer = tmp;

		return *this;
	}
	
	~vector() {
		delete[] m_buffer;
	}

	void push_back(const T& element) {
		if (m_size == m_capacity) {
			m_capacity *= 2;
			T* tmp = new T[m_capacity];

			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_buffer[i];
			}

			delete[] m_buffer;
			m_buffer = tmp;
		}

		m_buffer[m_size] = element;
		++m_size;
	}

	void pop_back() {
		if (m_size != 0) {
			--m_size;
			T* tmp = new T[m_capacity];
			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_buffer[i];
			}

			delete[] m_buffer;
			m_buffer = tmp;
		}
		else {
			throw std::invalid_argument("empty vector");
		}
	}

	void erase(int index) {
		if (m_size != 0) {
			T* tmp = new T[m_capacity];
			for (int i = 0, j = 0; i < m_size; ++i, ++j) {
				if (i == index) { ++i; }
				tmp[j] = m_buffer[i];
			}

			delete[] m_buffer;
			m_buffer = tmp;
			--m_size;
		}
	}

	int size() {
		return m_size;
	}

	int capacity() {
		return m_capacity;
	}

	void resize(int input_capacity) {
		if(input_capacity <= m_capacity){
			throw std::invalid_argument("Invalid resize");
		}
		else {
			m_capacity = input_capacity;
		}
	}

	T& at(int index) {
		if (index + 1 > m_size) {
			throw std::invalid_argument("Vector out of range");
		}
		else {
			return this->m_buffer[index];
		}
	}

	T& operator[](int index) {
		if (index + 1 > m_size) {
			throw std::invalid_argument("Vector out of range");
		}
		else {
			return this->m_buffer[index];
		}
	}

private:
	int m_size;
	int m_capacity;
	T* m_buffer;
};

}

#endif //VECTOR_H
