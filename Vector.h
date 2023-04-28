// https://github.com/Miguel-Deniz/Vector-Implementation/blob/master/Vector%20Implementation/Vector.h?fbclid=IwAR1M0UoHF2Qm0IvFzxTrzq6GBuDe-LcrNXraMawZ-MEiiP5IZ5HjnG7kkp4
#pragma once

template <typename T>
class Vector {
public:
    /* ----- CONSTRUCTOR ----- */

    // Default constructor
    Vector();
    // Destructor
    ~Vector();

    /* -------- ITERATORS --------*/

    // Returns the address of the first element
    T* begin();
    // Returns the address of the last element
    T* end();

	/* -------- CAPACITY -------- */

	bool empty() const;
	// Returns size of allocated storate capacity
	size_t size() const;
	// Requests a change in capacity
	// reserve() will never decrase the capacity
	void reserve(size_t capacity);

    /* -------- MODIFIERS --------*/

    // Inserts element at the back
    void push_back(T value);
	// Removes the last element from the Vector
    void pop_back();

    /* ----- ELEMENT ACCESS ----- */

    // Access elements
    T& operator[](size_t index);
    // Access elements
    const T& operator[](size_t index) const;

private:
    size_t mSize;
    size_t mCapacity;
    T* mData;
};

// Constructors/Destructor
template<typename T>
Vector<T>::Vector()
    : mSize(0),
      mCapacity(4),
      mData(new T[mCapacity]) {}

template<typename T>
Vector<T>::~Vector() { delete[] mData; }

// Iterators
template<typename T>
T* Vector<T>::begin() { return mData; }

template<typename T>
T* Vector<T>::end() { return mData + mSize; }

// Capacity
template<typename T>
bool Vector<T>::empty() const { return mSize == 0; }

template<typename T>
size_t Vector<T>::size() const { return mSize; }

template<typename T>
void Vector<T>::reserve(size_t capacity) {
    T* newData = new T[capacity];
    for (size_t i = 0; i < mSize; ++i) {
        newData[i] = mData[i];
    }
    delete[] mData;
    mData     = newData;
    mCapacity = capacity;
}

// Modifiers
template<typename T>
void Vector<T>::push_back(T value) {
    if (mSize == mCapacity) {
        reserve(mCapacity * 2);
    }
    m_data[mSize++] = value;
}

template<typename T>
void Vector<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Index out of range");
    }
    --mSize;
}

// Element Access
template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= mSize) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= mSize) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}
