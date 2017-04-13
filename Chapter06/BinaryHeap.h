#ifndef DS_CH06_BINARYHEAP_H
#define DS_CH06_BINARYHEAP_H

#include <vector>
#include <stdexcept>

template <typename T>
class BinaryHeap {
public:
    BinaryHeap() = delete;
    explicit BinaryHeap(int capacity) : arr(capacity), curSize(0) { }
    BinaryHeap(const vector<T> &items)
        : arr(items.size() + 10), curSize(int(items.size()))
    {
        if (!empty()) {
            for (int i = 0; i < items.size(); ++i)
                arr[i + 1] = items[i];
            buildHeap();
        }
    }
    BinaryHeap(const BinaryHeap &rhs) : curSize(0), arr(100) { operator=(rhs); }
    ~BinaryHeap() = default;
    
public:
    const BinaryHeap &operator=(const BinaryHeap &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            
            arr.resize(rhs.arr.capacity());
            curSize = rhs.size();
            for (int i = 0; i < rhs.size(); ++i)
                arr[i + 1] = rhs.arr[i + 1];
        }
        return *this;
    }

    int size() const { return curSize; }
    bool empty() const { return size() == 0; }
    const T &findMin() const
    {
        if (empty())
            throw std::underflow_error("��ǰ��Ϊ��");
        return arr[1];
    }
    
    void insert(const T &x)
    {
        if (curSize == arr.size() - 1)
            arr.resize(arr.size() << 1);

        //percolateUp
        int hole = ++curSize;
        //�����Ĳ��������˽�����ֻ���滻
        for (; hole > 1 && x < arr[hole >> 1]; hole >>= 1)
            arr[hole] = arr[hole >> 1];

        arr[hole] = x;
    }
    void deleteMin()
    {
        if (empty())
            throw std::underflow_error("��ǰ��Ϊ��");

        arr[1] = arr[curSize--];
        percolateDown(1);
    }
    void deleteMin(T &minItem) //ɾ��min����minֵ���ظ�minItem
    {
        if (empty())
            throw std::underflow_error("��ǰ��Ϊ��");

        minItem = arr[1];
        arr[1] = arr[curSize--];
        percolateDown(1);
    }
    void makeEmpty() { curSize = 0; arr.clear(); }
    
private:
    void buildHeap()
    {
        for (int i = curSize >> 1; i > 0; --i)
            percolateDown(i);
    }
    void percolateDown(int hole)
    {
        int child = 0;
        T tmp = arr[hole];
        for (; (child = hole << 1) <= curSize; hole = child) {
            //����if��ĵ�һ���жϱ�֤���һ���ڵ�������ӵ�����µ���ȷ��
            if (child != curSize && arr[child + 1] < arr[child])
                ++child;
            if (arr[child] < tmp)
                arr[hole] = arr[child];
            else
                break;
        }
        arr[hole] = tmp;
    }

private:
    int curSize;
    vector<T> arr;
};

#endif // DS_CH06_BINARYHEAP_H
