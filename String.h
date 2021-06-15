#ifndef STRING_H
#define STRING_H

#include <stdexcept>

namespace STL {

class string 
{
public:
	string() : m_size(0), m_capacity(10), m_ptr(new char[m_capacity]) {}

	string(int in_capacity) : m_size(0), m_capacity(in_capacity), m_ptr(new char[m_capacity]) {}

	string(const char* input) : m_size(0), m_capacity(10), m_ptr(new char[m_capacity])
	{
		for (int i = 0; input[i] != '\0'; ++i) {
			++m_size;
		}

		if (m_size <= m_capacity) {
			for (int i = 0; i < m_size; ++i) {
				m_ptr[i] = input[i];	
			}
		}
		else {
			m_capacity = m_size * 2;

			char* tmp = new char[m_capacity];

			for (int i = 0; i < m_size; ++i) {
				tmp[i] = input[i];
			}

			delete[] m_ptr;
			m_ptr = tmp;
		}	
	}

	string(const string& input) : m_size(0), m_capacity(10), m_ptr(new char[m_capacity])
	{
		m_size = input.m_size;

		if (m_size <= m_capacity) {
			for (int i = 0; i < m_size; ++i) {
				m_ptr[i] = input.m_ptr[i];	
			}
		}
		else {
			m_capacity = m_size * 2;

			char* tmp = new char[m_capacity];

			for (int i = 0; i < m_size; ++i) {
				tmp[i] = input.m_ptr[i];
			}

			delete[] m_ptr;
			m_ptr = tmp;
		}
	}

	~string() {
		delete[] m_ptr;
	}
	
	string& operator=(const string& input) {

		if (&input == this) {
			return *this;
		}

		m_size = input.m_size;

		if (m_size <= m_capacity) {
			for (int i = 0; i < m_size; ++i) {
				m_ptr[i] = input.m_ptr[i];	
			}
		}
		else {
			m_capacity = m_size * 2;

			char* tmp = new char[m_capacity];

			for (int i = 0; i < m_size; ++i) {
				tmp[i] = input.m_ptr[i];
			}

			delete[] m_ptr;
			m_ptr = tmp;
		}

		return *this;
	}

	string& operator=(const char* rhs) {
		m_size = 0;
		for (int i = 0; rhs[i] != '\0'; ++i) {
			++m_size;
		}

		if (m_capacity < m_size) {
			m_capacity *= 2;
		}

		char* tmp = new char[m_capacity];

		for (int i = 0; i < m_size; ++i) {
			tmp[i] = rhs[i];
		}

		delete[] m_ptr;
		m_ptr = tmp;

		return *this;
	}

	string& operator+=(const char* rhs) {
		int rhs_size = 0;
		for (int i = 0; rhs[i] != '\0'; ++i) {
			++rhs_size;
		}
		
		char* tmp = new char[m_capacity];

		for (int i = 0; i < m_size; ++i) {
			tmp[i] = m_ptr[i];
		}

		for (int i = m_size; i < m_size + rhs_size; ++i) {
			tmp[i] = rhs[i - m_size];
		}

		delete[] m_ptr;
		m_ptr = tmp;

		m_size = m_size + rhs_size;

		return *this;
	}

	string& operator+=(const string& rhs) {
		if (m_capacity < m_size + rhs.m_size) {
			m_capacity = (m_size + rhs.m_size) * 2;
		}

		char* tmp = new char[m_capacity];

		for (int i = 0; i < m_size; ++i) {
			tmp[i] = m_ptr[i];
		}

		for (int i = m_size; i < m_size + rhs.m_size; ++i) {
			tmp[i] = rhs.m_ptr[i - m_size];
		}

		delete[] m_ptr;
		m_ptr = tmp;

		m_size = m_size + rhs.m_size;

		return *this;
	}

	char& operator[](int index) {
		return m_ptr[index];
	}

	int size() {
		return m_size;
	}

	int capacity() {
		return m_capacity;
	}

	void resize(int in_capacity) {
		if (in_capacity < m_size) {
			throw std::invalid_argument("bad_resize");
		}
		else {
			m_capacity = in_capacity;

			char* tmp = new char[m_capacity];

			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_ptr[i];
			}

			delete[] m_ptr;
			m_ptr = tmp;
		}
	}

	void clear() {
		m_capacity = 10;
		m_size = 0;

		char* tmp = new char[m_capacity];

		delete[] m_ptr;
		m_ptr = tmp;
	}

	bool empty() {
		if (m_size == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void erase(int index) {
		if (m_size == 0) {
			throw std::invalid_argument("empty string");
		}
		else if (index > m_size) {
			throw std::invalid_argument("index out of range");
		}
		else {
			char* tmp = new char[m_capacity];

			for (int i = 0, j = 0; i < m_size; ++i, ++j) {
				if (index == i) { ++i; }
				tmp[j] = m_ptr[i];
			}

			delete[] m_ptr;
			m_ptr = tmp;

			--m_size;
		}
	}

	void insert(int index, char element) {
		if (m_size == 0 && index == 0) {
			m_ptr[0] = element;
			++m_size;
		}
		else if (index == m_size && m_size < m_capacity) {
			m_ptr[m_size] = element;
			++m_size;
		}
		else if (index > m_size) {
			throw std::invalid_argument("index out of range");
		}
		else {
			if (m_capacity == m_size) {
				m_capacity *= 2;
			}

			char* tmp = new char[m_capacity];

			for (int i = 0, j = 0; i < m_size + 1; ++i, ++j) {
				if (i == index) {
					tmp[i] = element;
					++i;
				}
				tmp[i] = m_ptr[j];
			}

			delete[] m_ptr;
			m_ptr = tmp;

			++m_size;
		}
	}

private:
	int m_size;
	int m_capacity;
	char* m_ptr;
};

}

#endif //STRING_H
