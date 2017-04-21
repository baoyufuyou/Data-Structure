#include <iostream>
#include <random>

using namespace std;

#include "Timer.h"
#include "Sort.h"

#define PRINT_SORT_TIME(A, sortfun) \
{\
    vector<int> arrt(A);\
    Timer ts;\
    sortfun(arrt);\
    cout << #sortfun##" " << maxSize << " ���������ʱ: " << ts.stop_delta<Timer::ms>() << " ms" << endl;\
}

int main()
{
    const int maxSize = 100000;
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, maxSize);

    vector<int> arr;
    for (int i = 0; i < maxSize; ++i)
        arr.push_back(u(e));

    if (maxSize <= 1000)
        PRINT_SORT_TIME(arr, insertionSort);
    PRINT_SORT_TIME(arr, shellSort);
    PRINT_SORT_TIME(arr, heapSort);

    getchar();
    return 0;
}