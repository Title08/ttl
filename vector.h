#ifndef _TT_VECTOR_INCLUDED_
#define _TT_VECTOR_INCLUDED_

#include <iostream>
#include <stdexcept>

namespace tt {

    template<typename T>
    class vector {
    protected:
        T *mData;      // pointer เก็บ array ของ element
        size_t mSize;  // จำนวน element จริง
        size_t mCap;   // ความจุที่ allocate

        // ขยายพื้นที่เก็บข้อมูล
        void expand(size_t capacity) {
            T *newData = new T[capacity];
            for (size_t i = 0; i < mSize; ++i) {
                newData[i] = mData[i];  // copy element
            }
            delete[] mData;
            mData = newData;
            mCap = capacity;
        }

        // ตรวจสอบและขยายถ้าจำเป็น
        void ensure_capacity(size_t capacity) {
            if (mSize >= mCap) {
                size_t expand_capacity = (capacity > 2 * mCap) ? capacity : (mCap ? 2 * mCap : 1);
                expand(expand_capacity);
            }
        }

        // copy data จาก vector อื่น
        void copy(const vector &other) {
            T *newData = new T[other.mCap];
            for (size_t i = 0; i < other.mSize; ++i) {  // ใช้ other.mSize
                newData[i] = other.mData[i];
            }
            delete[] mData;
            mData = newData;
            mSize = other.mSize;
            mCap = other.mCap;
        }

    public:
        // ================= Constructors / Destructor =================
        vector() : mData(nullptr), mSize(0), mCap(0) {}

        vector(size_t capacity) : mData(new T[capacity]), mSize(0), mCap(capacity) {}

        vector(const vector &other) {
            copy(other);
        }

        ~vector() {
            delete[] mData;
        }

        vector &operator=(const vector &other) {
            if (this != &other) copy(other);
            return *this;
        }

        // ================= Iterators =================

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin() { return mData; }
        iterator end() { return mData + mSize; }

        const_iterator begin() const { return mData; }
        const_iterator end() const { return mData + mSize; }

        const_iterator cbegin() const { return mData; }
        const_iterator cend() const { return mData + mSize; }

    

        // ================= Accessors =================
        size_t size() const { return mSize; }
        size_t capacity() const { return mCap; }
        bool empty() const { return mSize == 0; }

        const T &front() const {
            if (empty()) throw std::out_of_range("vector is empty");
            return mData[0];
        }
        T &front() {
            if (empty()) throw std::out_of_range("vector is empty");
            return mData[0];
        }

        const T &back() const {
            if (empty()) throw std::out_of_range("vector is empty");
            return mData[mSize - 1];
        }
        T &back() {
            if (empty()) throw std::out_of_range("vector is empty");
            return mData[mSize - 1];
        }

        const T &at(size_t index) const {
            if (index >= mSize) throw std::out_of_range("index out of range");
            return mData[index];
        }
        T &at(size_t index) {
            if (index >= mSize) throw std::out_of_range("index out of range");
            return mData[index];
        }

        const T &operator[](size_t index) const { return mData[index]; }
        T &operator[](size_t index) { return mData[index]; }

        // ================= Modifiers =================
        void push_back(const T &value) {
            ensure_capacity(mSize + 1);
            mData[mSize++] = value;
        }

        void pop_back() {
            if (empty()) throw std::out_of_range("pop_back on empty vector");
            --mSize;
        }

        void clear() { mSize = 0; }

        void reserve(size_t capacity) {
            if (capacity > mCap) expand(capacity);
        }

        void resize(size_t n) {
            if (n > mCap) expand(n);
            mSize = n;
        }

        void resize(size_t n, const T &val) {
            if (n > mCap) expand(n);
            if (n > mSize) {
                for (size_t i = mSize; i < n; ++i)
                    mData[i] = val;
            }
            mSize = n;
        }
    };
}

#endif
