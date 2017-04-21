#include <iostream>
#include <random>

using namespace std;

#include "Timer.h"
#include "Sort.h"

int main()
{
    Timer ts;
    const int maxSize = 1000;
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, maxSize);

    vector<int> arr;
    for (int i = 0; i < maxSize; ++i)
        arr.push_back(u(e));

    ts.start();
    insertionSort(arr);
    cout << "��������" << maxSize << "���������ʱ: " << ts.stop_delta<Timer::ms>() << " ms" << endl;

    getchar();
    return 0;
}