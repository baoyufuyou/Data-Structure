#include <iostream>

#include "exercise_2.h"

using namespace std;

int main()
{
    maxInfo i;
    vector<int> arr;
    int temp = 0;
    cout << "Please input some numbers: ";
    while (cin >> temp) {
        arr.push_back(temp);
    }

    cout << "��С���������к�: " << minSubSum(arr) << endl;
    
    i = maxSubSum(arr);
    cout << "������������к�: " << i.Sum << ", ��ʼ�±�: " << i.begin << ", �����±�: " << i.end << endl;
    
    return 0;
}