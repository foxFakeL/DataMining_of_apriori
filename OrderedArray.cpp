//
// Created by 刘祺霖 on 2023/4/9.
//

#include "OrderedArray.h"

template <typename T>
OrderedArray<T>::OrderedArray() = default;

template <typename T>
OrderedArray<T>::OrderedArray(const OrderedArray& rhs) : data(rhs.data) {}

template <typename T>
OrderedArray<T>& OrderedArray<T>::operator=(const OrderedArray& rhs) {
    data = rhs.data;
    return *this;
}

template <typename T>
void OrderedArray<T>::insert(const T& item) {
    auto index = std::lower_bound(data.begin(), data.end(), item) - data.begin();
    if (index == data.size() || data[index] != item) {
        data.insert(data.begin() + index, item);
    }
}

template <typename T>
void OrderedArray<T>::remove(const T& item) {
    auto index = std::lower_bound(data.begin(), data.end(), item) - data.begin();
    if (index != data.size() && data[index] == item) {
        data.erase(data.begin() + index);
    }
}

template <typename T>
bool OrderedArray<T>::contains(const T& item) const {
    auto index = std::lower_bound(data.begin(), data.end(), item) - data.begin();
    return index != data.size() && data[index] == item;
}

template <typename T>
int OrderedArray<T>::size() const {
    return data.size();
}

template <typename T>
T& OrderedArray<T>::operator[](int index) {
    return data[index];
}

template <typename T>
const T& OrderedArray<T>::operator[](int index) const {
    return data[index];
}

template class OrderedArray<int>;