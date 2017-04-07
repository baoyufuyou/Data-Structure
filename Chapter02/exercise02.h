#ifndef EXERCISE02_H
#define EXERCISE02_H

#include <vector>
using std::vector;

//2.17
//a.����С���������к�  O(N)�㷨
int minSubSum(const vector<int> &a)
{
    int minSum = 0, thisSum = 0;
    for (int i = 0; i < a.size(); ++i) {
        thisSum += a[i];
        if (thisSum < minSum)
            minSum = thisSum;
        else if (thisSum > 0)
            thisSum = 0;
    }
    return minSum;
}

//2.19
//����������������к��Լ���Ӧ���±�
struct maxInfo {
    maxInfo() = default;
    int Sum;
    int begin;
    int end;
};

maxInfo info;

maxInfo maxSubSum(const vector<int> &a)
{
    int thisSum = 0;
    bool isBegin = false;
    for (int i = 0; i < a.size(); ++i) {
        thisSum += a[i];
        if (thisSum > info.Sum) {
            info.Sum = thisSum;
            if (!isBegin) {
                isBegin = true;
                info.begin = i;
            }
            info.end = i;
        } else if (thisSum < 0) {
            thisSum = 0;
            isBegin = false;
        }
    }
    return info;
}

#endif //EXERCISE02_H
