#include <stdexcept>
#include <cstring>

class Vector {
public:
    size_t m_size;
    Vector();
    Vector(size_t size);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    void push_back(int value);
    void push_front(int value);

private:
    int* m_data;

    size_t m_capacity;

    void reserve(size_t new_capacity);
};

Vector::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

Vector::Vector(size_t size) : m_data(new int[size]), m_size(size), m_capacity(size) {}

Vector::Vector(const Vector& other) : m_data(new int[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
    std::memcpy(m_data, other.m_data, sizeof(int) * m_size);
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (other.m_size <= m_capacity) {
            std::memcpy(m_data, other.m_data, sizeof(int) * other.m_size);
            m_size = other.m_size;
        }
        else {
            Vector temp(other);
            std::swap(m_data, temp.m_data);
            std::swap(m_size, temp.m_size);
            std::swap(m_capacity, temp.m_capacity);
        }
    }
    return *this;
}

Vector::~Vector() {
    delete[] m_data;
}

int& Vector::operator[](size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

const int& Vector::operator[](size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

void Vector::push_back(int value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_data[m_size++] = value;
}

void Vector::push_front(int value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    std::memmove(m_data + 1, m_data, sizeof(int) * m_size);
    m_data[0] = value;
    ++m_size;
}

void Vector::reserve(size_t new_capacity) {
    if (new_capacity > m_capacity) {
        int* new_data = new int[new_capacity];
        std::memcpy(new_data, m_data, sizeof(int) * m_size);
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
}