#ifndef DS_CH07_SORT_H
#define DS_CH07_SORT_H

#include <vector>
#include <algorithm>

//��������
template <typename T>
void insertionSort(vector<T> &a)
{
    int j = 0;
    T tmp;

    for (int p = 1; p < a.size() ; ++p) {
        tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}

template <typename T>
void insertionSort(vector<T> &a, int left, int right)
{
    int j = 0;
    T tmp;

    for (int p = left + 1; p < right + 1; ++p) {
        tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}

//ϣ������ ʹ��Shell����
template <typename T>
void shellSort(vector<T> &a)
{
    int i = 0, j = 0;
    T tmp;

    for (int gap = static_cast<int>(a.size() >> 1); gap > 0; gap >>= 1) {
        for (i = gap; i < a.size(); ++i) {
            tmp = a[i];
            for (j = i; j >= gap && tmp < a[j - gap]; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = tmp;
    	}
    }
}

//������ ��ʹ�ø�������
inline int leftChild(int i)
{
    return (i << 1) + 1;
}

template <typename T>
void percolateDown(vector<T> &a, int hole, int n)
{
    int child = 0;
    T tmp;
    for (tmp = a[hole]; leftChild(hole) < n; hole = child) {
        child = leftChild(hole);
        //����if��ĵ�һ���жϱ�֤���һ���ڵ�������ӵ�����µ���ȷ��
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

template <typename T>
void heapSort(vector<T> &a)
{
    //buildheap
    for (int i = static_cast<int>(a.size() >> 1); i >= 0; --i)
        percolateDown(a, i, static_cast<int>(a.size()));

    //deleteMax
    for (int i = static_cast<int>(a.size() - 1); i > 0; --i) {
        std::swap(a[0], a[i]);
        percolateDown(a, 0, i);
    }
}

//�鲢���� �ݹ�ʵ��
template <typename T>
void merge(vector<T> &a, vector<T> &tmp, int leftPos, int rightPos, int rightEnd)
{
    //���������ʱ��A,B��������
    //A�ķ�Χ[leftPos, leftEnd], B�ķ�Χ[rightPos, rightEnd]
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    //A,B���С�߷���C ����±��ƽ�
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos])
            tmp[tmpPos++] = a[leftPos++];
        else
            tmp[tmpPos++] = a[rightPos++];
    }

    while (leftPos <= leftEnd) //��������
        tmp[tmpPos++] = a[leftPos++];

    while (rightPos <= rightEnd) //���߿����Ұ��
        tmp[tmpPos++] = a[rightPos++];

    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = tmp[rightEnd]; //������ȥ
}

template <typename T>
void mergeSort(vector<T> &a, vector<T> &tmp, int left, int right)
{
    if (left < right) {
        int center = (left + right) >> 1;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        merge(a, tmp, left, center + 1, right);
    }
}

template <typename T>
void mergeSort(vector<T> &a)
{
    vector<T> tmp(a.size());
    mergeSort(a, tmp, 0, static_cast<int>(a.size() - 1));
}

//ex 7.16 �鲢����ķǵݹ�ʵ��
template <typename T>
void mergeSort2(vector<T> &a)
{
    int n = static_cast<int>(a.size());
    vector<T> tmp(n);
    int part1Start = 0, part2Start = 0, part2End = 0;

    for (int subListSize = 1; subListSize < n ; subListSize <<= 1) {
        part1Start = 0;
        while (part1Start + subListSize < n - 1) {
            part2Start = part1Start + subListSize;
            part2End = std::min(n - 1, part2Start + subListSize - 1);
            merge(a, tmp, part1Start, part2Start, part2End);
            part1Start = part2End + 1;
        }
    }
}

//��������
template <typename T>
const T &median3(vector<T> &a, int left, int right)
{
    int center = (left + right) >> 1;
    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[right], a[center]);

    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

template <typename T>
void quickSort(vector<T> &a, int left, int right)
{
    if (left + 10 <= right) {
        T pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for (;;) {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);

        quickSort(a, left, i - 1);
        quickSort(a, i + 1, right);
    } else {
        insertionSort(a, left, right);
    }
}

template <typename T>
void quickSort(vector<T> &a)
{
    quickSort(a, 0, static_cast<int>(a.size() - 1));
}

//����ѡ�� ִ������k����СԪ��a[k-1]
template <typename T>
void quickSelect(vector<T> &a, int left, int right, int k)
{
    if (left + 10 <= right) {
        T pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for (;;) {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);

        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    } else {
        insertionSort(a, left, right);
    }
}

#endif // DS_CH07_SORT_H
