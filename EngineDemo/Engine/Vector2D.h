#pragma once
#include <vector>
#include <iterator>

namespace Engine
{
    /// <summary>
    /// Implementation of a 2D vector using monodimensional vector for
    /// better performance (cache)
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<typename T>
    class Vector2D
    {
        // -------------------------------------------------------------------- Fields
    private:
        size_t width = 0;
        std::vector<T> vector;

        // -------------------------------------------------------------------- Methods
    public:
        Vector2D() : Vector2D(0) {};
        Vector2D(size_t width) : width(width) { vector.resize(width); }

        Vector2D(size_t width, const std::vector<T>& vect) : width(width)
        {
            vector = vect;
        }

        size_t GetSizeX() const { return width; }
        size_t GetSizeY() const { return width == 0 ? 0 : vector.size() / width; }

        void IncreaseSizeY() { vector.resize(vector.size() + width); }
        void Resize(size_t width, size_t height)
        {
            this->width = width;
            vector.resize(width * height);
        }
        void Clear() { vector.clear(); }

        const T& Get(size_t x, size_t y) const { return vector[width * y + x]; }
        T& Get(size_t x, size_t y) { return vector[width * y + x]; }

        // -------------------------------------------------------------------- Iterator
    public:
        class Iterator
        {
        public:
            // iterator traits
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t; 
            using pointer = T*;
            using reference = T&;

        private:
            typename std::vector<T>::iterator it;

        public:
            Iterator(typename std::vector<T>::iterator it) : it(it) {}

            reference operator*() { return *it; }
            pointer operator->() { return &(*it); }
            Iterator& operator++() { ++it; return *this; }
            Iterator operator++(int) { Iterator temp = *this; ++it; return temp; }
            Iterator& operator--() { --it; return *this; }
            Iterator operator--(int) { Iterator temp = *this; --it; return temp; }
            Iterator operator+(difference_type n) const { return Iterator(it + n); }
            Iterator operator-(difference_type n) const { return Iterator(it - n); }
            difference_type operator-(const Iterator& other) const { return it - other.it; }
            bool operator==(const Iterator& other) const { return it == other.it; }
            bool operator!=(const Iterator& other) const { return it != other.it; }
            bool operator<(const Iterator& other) const { return it < other.it; }
            bool operator<=(const Iterator& other) const { return it <= other.it; }
            bool operator>(const Iterator& other) const { return it > other.it; }
            bool operator>=(const Iterator& other) const { return it >= other.it; }
            reference operator[](difference_type n) const { return *(it + n); }
        };

        Iterator begin() { return Iterator(vector.begin()); }
        Iterator end() { return Iterator(vector.end()); }

        // -------------------------------------------------------------------- Const Iterator
        class ConstIterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

        private:
            typename std::vector<T>::const_iterator it;

        public:
            ConstIterator(typename std::vector<T>::const_iterator it) : it(it) {}

            reference operator*() const { return *it; }
            pointer operator->() const { return &(*it); }
            ConstIterator& operator++() { ++it; return *this; }
            ConstIterator operator++(int) { ConstIterator temp = *this; ++it; return temp; }
            ConstIterator& operator--() { --it; return *this; }
            ConstIterator operator--(int) { ConstIterator temp = *this; --it; return temp; }
            ConstIterator operator+(difference_type n) const { return ConstIterator(it + n); }
            ConstIterator operator-(difference_type n) const { return ConstIterator(it - n); }
            difference_type operator-(const ConstIterator& other) const { return it - other.it; }
            bool operator==(const ConstIterator& other) const { return it == other.it; }
            bool operator!=(const ConstIterator& other) const { return it != other.it; }
            bool operator<(const ConstIterator& other) const { return it < other.it; }
            bool operator<=(const ConstIterator& other) const { return it <= other.it; }
            bool operator>(const ConstIterator& other) const { return it > other.it; }
            bool operator>=(const ConstIterator& other) const { return it >= other.it; }
            reference operator[](difference_type n) const { return *(it + n); }
        };

        ConstIterator begin() const { return ConstIterator(vector.begin()); }
        ConstIterator end() const { return ConstIterator(vector.end()); }
    };
}
