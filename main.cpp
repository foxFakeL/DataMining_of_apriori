#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "ItemSet.h"
#include "OrderedArray.h"

using namespace std;

// 所有的item集合
set<int> allItem;

// 最小支持度
double minSupportDec = 0.01;
int minSupport = 0;

// 从k-1频繁项集生成k候选项集
OrderedArray<ItemSet> generateCandidate(OrderedArray<ItemSet>& frequentItemSet_k_1) {
    OrderedArray<ItemSet> candidateItemSet_k;
    for (int i = 0; i < frequentItemSet_k_1.size(); i++) {
        for (int j = i + 1; j < frequentItemSet_k_1.size(); j++) {
            // 拷贝构造函数会把support也拷贝过来，所以要把support置为0
            ItemSet itemset1 = frequentItemSet_k_1[i];
            itemset1.support = 0;
            ItemSet itemset2 = frequentItemSet_k_1[j];
            itemset2.support = 0;
            // 判断前k-2个元素是否相等，相等则可以合并，否则退出循环，因为数组是按字典序的
            if (itemset1.prefixEqual(itemset2)) {
                // 新生成的候选项集的支持度一定要重新设置为0
                ItemSet candidateItemSet = itemset1;
                candidateItemSet.support = 0;
                candidateItemSet.add(itemset2.items.back());
                // 剪枝
                bool flag = true;
                // 判断它的k-1子项集是否都是频繁项集
                for (int k = 0; k < candidateItemSet.items.size(); k++) {
                    ItemSet subItemSet = candidateItemSet;
                    subItemSet.items.erase(subItemSet.items.begin() + k);
                    if (!frequentItemSet_k_1.contains(subItemSet)) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    candidateItemSet_k.insert(candidateItemSet);
                }
            } else {
                break;
            }
        }
    }
    return candidateItemSet_k;
}
// 递归求出所有的频繁项集
void apriori(OrderedArray<ItemSet>& frequentItemSet_k_1, vector<ItemSet>& itemData, int k, fstream& fout, int time) {
    // 由k-1频繁项集生成k候选项集
    OrderedArray<ItemSet> candidateItemSet_k = generateCandidate(frequentItemSet_k_1);
    if (candidateItemSet_k.size() == 0) {
        return;
    }
    cout << "candidateItemSet_" << k << " total number = " << candidateItemSet_k.size() << endl;
    // 遍历所有的记录，统计候选项集的支持度
    OrderedArray<ItemSet> frequentItemSet_k;
    int cnt = 0;
    for (int i = 0; i < candidateItemSet_k.size(); i++) {
        for (const auto& j : itemData) {
            if (candidateItemSet_k[i].isSubset(j)) {
                candidateItemSet_k[i].support++;
            }
        }
        if (candidateItemSet_k[i].support >= minSupport) {
            frequentItemSet_k.insert(candidateItemSet_k[i]);
        }
    }
    if (frequentItemSet_k.size() == 0) {
        return;
    }
    fout << "frequentItemSet_" << k << " total number = " << frequentItemSet_k.size() << endl;
    for (int i = 0; i < frequentItemSet_k.size(); i++) {
        fout << frequentItemSet_k[i].toString() << endl;
    }
    cout << "Process frequentItemSet_" << k << " finished! total number : " << frequentItemSet_k.size() << "\n"
         << "total time: " << (clock() - time) / 1000.0 << "s" << endl;
    // 递归求出k+1频繁项集
    apriori(frequentItemSet_k, itemData, k + 1, fout, time);
}

int main() {
    int beginTime = clock();
    string line;
    fstream fin("retail.dat");
    vector<ItemSet> itemData;
    unordered_map<int, int> itemSetCnt;
    while (getline(fin, line)) {
        istringstream iss(line);
        // 一行记录
        ItemSet itemset;
        int item;
        while (iss >> item) {
            itemset.add(item);
            allItem.insert(item);
            itemSetCnt[item]++;
        }
        itemData.emplace_back(itemset);
    }
    minSupport = ceil(minSupportDec * itemData.size());
    cout << "minSupport = " << minSupport << endl;
    cout << "transaction number = " << itemData.size() << endl;
    // 遍历所有的item，找出支持度大于minSupport的1项集
    OrderedArray<ItemSet> frequentItemSet_1;
    for (const auto& item : itemSetCnt) {
        if (item.second >= minSupport) {
            ItemSet itemset(item.second);
            itemset.add(item.first);
            frequentItemSet_1.insert(itemset);
        }
    }
    fstream fout("result.txt", ios::out);
    cout << "Process frequentItemSet_1 finished! total number : " << frequentItemSet_1.size() << endl;
    cout << "total time :" << (clock() - beginTime) / 1000.0 << "s" << endl;
    fout << "frequentItemSet_1:" << endl;
    for (int i = 0; i < frequentItemSet_1.size(); i++) {
        fout << frequentItemSet_1[i].toString() << endl;
    }
    apriori(frequentItemSet_1, itemData, 2, fout, beginTime);
    printf("The program takes %lf seconds to run.\n", (double)(clock() - beginTime) / CLOCKS_PER_SEC);
}