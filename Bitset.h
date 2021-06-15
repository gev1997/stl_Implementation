#ifndef BITSET_H
#define BITSET_H

typedef unsigned int BIT_TYPE;

template <BIT_TYPE bytes>
class bitset {
public:
    bitset() : m_bits_count(bytes), m_word_size(sizeof(BIT_TYPE) * 8), 
            m_buf_count(bytes / m_word_size), 
            m_buffer(new BIT_TYPE[m_buf_count])
    {
        ++m_buf_count;
    }

    bitset(const bitset& other) : m_bits_count(bytes), m_word_size(sizeof(BIT_TYPE) * 8), 
            m_buf_count(bytes / m_word_size), 
            m_buffer(new BIT_TYPE[m_buf_count])
    {
        ++m_buf_count;

        for (int i = 0; i < m_buf_count; ++i) {
            this->m_buffer[i] = other.m_buffer[i];
        }
    }

    ~bitset() {
        delete [] m_buffer;
    }

    BIT_TYPE size() {
        return m_bits_count;
    }

    BIT_TYPE count() {
        int count = 0;

        if (m_buf_count == 1) {
            for (int i = 0; i < m_bits_count; ++i) {
                if (m_buffer[0] & (1 << i)) {
                    ++count;
                }
            }
        }
        else {
            for (int i = 0; i < m_buf_count - 1; ++i) {
                for (int j = 0; j < m_word_size; ++j) {
                    if (m_buffer[i] & (1 << j)) {
                        ++count;
                    }
                }
            }

            int remainder = m_bits_count - ((m_buf_count - 1) * m_word_size);
            
            for (int i = 0; i < remainder; ++i) {
                if (m_buffer[m_buf_count - 1] & (1 << i)) {
                    ++count;
                }
            }
        }
        
        return count;
    }

    bitset& reset() {
        for (int i = 0; i < m_buf_count; ++i) {
            m_buffer[i] = 0;
        }

        return *this;
    }

    bitset& reset(const BIT_TYPE index) {
        return set(index, 0);
    }
    
    bitset& set() {
        for (int i = 0; i < m_buf_count; ++i) {
            for (int j = 0; j < m_word_size; ++j) {
                m_buffer[i] |= (1 << j); 
            }
        }

        return *this;
    }

    bitset& set(const BIT_TYPE index, BIT_TYPE value = 1) {
        _throw_out_of_range_(index);
        BIT_TYPE shift = _shift_count(index);

        if (value) {
            m_buffer[index / m_word_size] |= (1 << shift);
        }
        else {
            m_buffer[index / m_word_size] &= ~(1 << shift);
        }

        return *this;
    }

    bool test(const BIT_TYPE index) {
        _throw_out_of_range_(index);
        BIT_TYPE shift = _shift_count(index);

        return (m_buffer[index / m_word_size]) & (1 << shift);
    }

    bitset& flip() {
        for (int i = 0; i < m_buf_count; ++i) {
            for (int j = 0; j < m_word_size; ++j) {
                m_buffer[i] ^= (1 << j);
            }
        }

        return *this;
    }

    bitset& flip(const BIT_TYPE index) {
        _throw_out_of_range_(index);
        BIT_TYPE shift = _shift_count(index);

        m_buffer[index / m_word_size] ^= (1 << shift);

        return *this;
    }

    bool all() {
        return size() == count();
    }

    bool any() {
        return count();
    }

    bool none() {
        return !count();
    }

    bool operator[] (const BIT_TYPE index) {
        _throw_out_of_range_(index);
        BIT_TYPE shift = _shift_count(index);

        return (m_buffer[index / m_word_size]) & (1 << shift);
    } 

    bitset& operator=(const bitset& rhs) {
        for (int i = 0; i < m_buf_count; ++i) {
            this->m_buffer[i] = rhs.m_buffer[i];
        }

        return *this;
    }

    bitset& operator&=(const bitset& rhs) {
        for (int i = 0; i < m_buf_count; ++i) {
            this->m_buffer[i] &= rhs.m_buffer[i];
        }

        return *this;
    }

    bitset& operator|=(const bitset& rhs) {
        for (int i = 0; i < m_buf_count; ++i) {
            this->m_buffer[i] |= rhs.m_buffer[i];
        }

        return *this;
    }

    bitset& operator^=(const bitset& rhs) {
        for (int i = 0; i < m_buf_count; ++i) {
            this->m_buffer[i] ^= rhs.m_buffer[i];
        }

        return *this;
    }

    bitset& operator~() {
        return this->flip();
    }
    
private:
    void _throw_out_of_range_(const BIT_TYPE index) {
        if (std::greater<BIT_TYPE>()(index, m_bits_count)) {
            throw ("out of range");
        }
    }

    BIT_TYPE _shift_count(BIT_TYPE index) {
        if (index >= 32) {
            BIT_TYPE tmp_position = index;
            while (tmp_position >= 32) {
                tmp_position -= 32;
            }

            return tmp_position;
        }

        return index;
    }

private:
    BIT_TYPE m_bits_count; // input template argument
    const BIT_TYPE m_word_size; // 32bit
    BIT_TYPE m_buf_count;
    BIT_TYPE* m_buffer;
};

#endif //BITSET_H
