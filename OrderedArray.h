//
// Created by 刘祺霖 on 2023/4/9.
//
#ifndef ORDEREDARRAY_H
#define ORDEREDARRAY_H

#include <algorithm>
#include <vector>
/// @brief 一个有序数组，支持插入、删除、查找、下标访问等操作，底层使用std::vector实现，插入、删除、查找的时间复杂度为O(logn)。
/// @tparam T
template <typename T>
class OrderedArray {
public:
    OrderedArray();
    OrderedArray(const OrderedArray& rhs);
    OrderedArray& operator=(const OrderedArray& rhs);
    void insert(const T& item);
    void remove(const T& item);
    bool contains(const T& item) const;
    [[nodiscard]] int size() const;
    T& operator[](int index);
    const T& operator[](int index) const;

private:
    std::vector<T> data;
};

#include "OrderedArray.cpp"

#endif  // ORDEREDARRAY_H
