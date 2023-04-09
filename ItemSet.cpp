#include "ItemSet.h"
/// @brief 添加一个item，如果已经存在则不添加，时间复杂度O(n) n为items的大小
/// @param item
void ItemSet::add(int item = 0) {
    int index = lower_bound(items.begin(), items.end(), item) - items.begin();
    if (index == items.size() || items[index] != item) {
        items.insert(items.begin() + index, item);
    }
}

void ItemSet::setSupport(int support) {
    this->support = support;
}

string ItemSet::toString() const {
    stringstream ret;
    for (const auto& i : items) {
        ret << i << " ";
    }
    ret << "support: " << support;
    return ret.str();
}

ItemSet::ItemSet(int support) : support(support) {}
/// @brief 判断长度为n-1的前缀是否相同，时间复杂度O(n - 1) n为items的大小
/// @param rhs
/// @return 是返回true，否则返回false
bool ItemSet::prefixEqual(const ItemSet& rhs) const {
    if (rhs.items.size() != items.size()) {
        return false;
    }
    int size = items.size();
    for (int i = 0; i < size - 1; i++) {
        if (items[i] != rhs.items[i]) {
            return false;
        }
    }
    return true;
}
/// @brief 判断是不是rhs的子集，时间复杂度O(n) n为items的大小
/// @param rhs 待判断的集合
/// @return 是子集返回true，否则返回false
bool ItemSet::isSubset(const ItemSet& rhs) const {
    int size = items.size();
    int rhsSize = rhs.items.size();
    int i = 0, j = 0;
    while (i < size && j < rhsSize) {
        if (items[i] == rhs.items[j]) {
            i++;
            j++;
        } else if (items[i] < rhs.items[j]) {
            return false;
        } else {
            j++;
        }
    }
    return i == size;
}

ItemSet::ItemSet() : support(0) {}

ItemSet::ItemSet(const ItemSet& rhs) {
    this->items = rhs.items;
    this->support = rhs.support;
}
