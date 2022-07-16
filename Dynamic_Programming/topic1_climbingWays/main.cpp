#include <iostream>
#include <unordered_map>
#include <sys/time.h>


/*
题目1：
一个人要登上一个N级的台阶，但一次只能向上1或2级台阶，一共有多少种行走方法

分析：
1)
基础思想：递归法
由于一次只能向上1或2级台阶，因此要么是从第N-1级台阶登上第N级台阶，要么是从第N-2级台阶登上第N级台阶，
因此登上一个N级的台阶的行走方法F(N) = F(N - 1) + F(N - 2)
2)
递归法的问题：
递归调用的过程形成了一个二叉树，高度为N-1（一直选择只走一级台阶的分支）
N-1层二叉树的节点数量为1 + 2 + 2^2 + ... + 2^(N-1) = (2^N)-1
因此递归调用树的节点数量小于(2^N)-1，但在同一数量级，每个节点对应一次递归函数调用，故递归方式的时间复杂度为O(2^N)
3)
对递归方法的改进：带哈希表储存的递归法
F(N) = F(N - 1) + F(N - 2)
F(N - 1) = F(N - 2) + F(N - 3)
F(N - 2) = F(N - 3) + F(N - 4)
...
显然递归二叉树中是有大量相同值的节点的，那么显然可以用哈希表对计算过的节点进行储存
3)
对带哈希表储存的递归法的改进：递推法（动态规划）
既然F(N)的值仅由F(N - 1)，F(N - 2)决定，那么就可以逆转递归的思考过程，从F(1),F(2)推导F(3), F(4), ... , F(N)的值

参考：https://zhuanlan.zhihu.com/p/31628866
*/




/*
方法1：递归法
时间复杂度：O(2^N)，因为计算的节点的数量级为2^N
*/
int getClimbingWays_1(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else if (n >= 3) {
        return (getClimbingWays_1(n - 1) + getClimbingWays_1(n - 2));
    } else {
        return 0;
    }
}




/*
方法2：带哈希表储存的递归法
时间复杂度：O(N)，因为需要计算的节点为F(3), F(4), ... , F(N)，个数为N-2个
空间复杂度：O(N)，因为哈希表中存储节点的个数为N-2个，n=1，n=2时不存储，其他都存储
*/
int getClimbingWays_2(int n, std::unordered_map<int, int> &map) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else if (n < 1) {
        return 0;
    }
    
    if (map.find(n) != map.end()) {
        return map[n];
    } else {
        int waysNum = getClimbingWays_2(n - 1, map) + getClimbingWays_2(n - 2, map);
        map[n] = waysNum;
        return waysNum;
    }
}
/*
c++ HashMap和map之间的异同
[HashMap]
实现方式：基于哈希表
消耗更多内存
存储和查找时间复杂度为O(1)
不可以做范围查找
[map]
实现方式：基于红黑树
消耗更少内存
存储和查找时间复杂度为O(logN)
可以做范围查找
*/




/*
方法3：递推法（动态规划）
时间复杂度：O(N)，因为需要递推出F(3), F(4), ... , F(N)，计算N-2次
空间复杂度：O(1)，因为只需要三个变量waysNum_n、waysNum_nMinus1、waysNum_nMinus2存储当前关心的三个数值
*/
int getClimbingWays_3(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else {
        int waysNum_nMinus1 = 2;
        int waysNum_nMinus2 = 1;
        int waysNum_n;
        for (int i = 3; i <= n; i++) {
            waysNum_n = waysNum_nMinus1 + waysNum_nMinus2;
            waysNum_nMinus2 = waysNum_nMinus1;
            waysNum_nMinus1 = waysNum_n;
        }
        return waysNum_n;
    }
}



long getCurTimeUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}



int main() {
    int stairNum = 30;
    struct timeval tv;
    long timeStart;

    // 方法1：递归法
    timeStart = getCurTimeUs();
    std::cout << "waysNum : " << getClimbingWays_1(stairNum) << " time cost : " << getCurTimeUs() - timeStart << std::endl;

    // 方法2：带哈希表储存的递归法
    std::unordered_map<int, int> waysNumMap;
    timeStart = getCurTimeUs();
    std::cout << "waysNum : " << getClimbingWays_2(stairNum, waysNumMap)  << " time cost : " << getCurTimeUs() - timeStart << std::endl;

    // 方法2：递推法（动态规划）
    timeStart = getCurTimeUs();
    std::cout << "waysNum : " << getClimbingWays_3(stairNum)  << " time cost : " << getCurTimeUs() - timeStart << std::endl;
}