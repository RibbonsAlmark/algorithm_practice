#include <iostream>
#include <map>
#include <sys/time.h>


/*
题目2：
有5座金矿，藏金量和需要的工人数量分别为：
金矿1：500金，5人
金矿2：200金，3人
金矿3：300金，4人
金矿4：350金，3人
金矿5：400金，5人
现有10名矿工，如何分配能得到最多的黄金

分析：
1)
方法1：排列组合
每座矿有两种状态：挖、不挖，那么N座矿就有2^N种挖法
枚举出所有挖法，排除掉需要人数大于10的，计算所得黄金，取最大值
*/




std::map<int, bool> resignWays(std::map<int, int> goldMineMap, int workersNum) {
    for (std::map<int, int>::iterator i = goldMineMap.begin(); i != goldMineMap.end(); i++) {}
}




int main() {
    int workersNum = 10;
    std::map<int, int> goldMineMap;
}