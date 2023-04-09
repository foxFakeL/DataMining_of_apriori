#ifndef ITEMSET_H
#define ITEMSET_H

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class ItemSet {
public:
    // 存储项集中的所有项
    vector<int> items;
    // 项集的支持度
    int support;
    // 向项集中添加项
    void add(int item);
    // 设置项集的支持度
    void setSupport(int);
    // 将项集转换成字符串
    string toString() const;
    explicit ItemSet(int);  // 构造函数
    ItemSet();              // 默认构造函数
    ItemSet(const ItemSet&);
    bool operator<(const ItemSet& rhs) const {
        return items < rhs.items;
    }
    bool operator==(const ItemSet& rhs) const {
        return items == rhs.items;
    }
    bool operator!=(const ItemSet& rhs) const {
        return items != rhs.items;
    }
    int& operator[](int index) {
        return items[index];
    }
    // 判断前缀是否相同0 ~ size-1
    bool prefixEqual(const ItemSet& rhs) const;
    /// @brief 判断是不是rhs的子集，时间复杂度O(n) n为items的大小
    /// @param rhs 待判断的集合
    /// @return 是子集返回true，否则返回false
    bool isSubset(const ItemSet& rhs) const;
};

#endif  // ITEMSET_H