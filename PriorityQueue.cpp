#include <iostream>
#include <vector>
using namespace std;
template <typename T>
struct maxcomparator
{
    inline bool operator()(T parent, T child)
    {
        return child > parent;
    }
};
template <typename T>
struct mincomparator
{
    inline bool operator()(T parent, T child)
    {
        return child < parent;
    }
};
template <typename T, typename compare = mincomparator<T>>
class MinHeap
{
private:
    vector<T> minheap;

public:
    compare mincomp;
    void push(T val)
    {
        if (minheap.empty())
            minheap.push_back(val);
        else
        {
            minheap.push_back(val);
            int curr = minheap.size() - 1;
            int parent = (curr - 1) / 2;
            while (parent >= 0)
            {
                if (mincomp(minheap[parent], minheap[curr]))
                {
                    swap(minheap[parent], minheap[curr]);
                    curr = parent;
                    parent = (curr - 1) / 2;
                }
                else
                    break;
            }
        }
        return;
    }
    T Top()
    {
        if (minheap.empty())
        {
            cout << "Error!!!\n";
            return T();
        }
        return minheap.front();
    }
    void pop()
    {
        if (minheap.empty())
        {
            cout << "Error!!!\n";
        }
        else
        {
            swap(minheap[0], minheap[minheap.size() - 1]);
            minheap.pop_back();
            int curr = 0;
            while (curr < minheap.size())
            {
                if (2 * curr + 1 < minheap.size() && 2 * curr + 2 < minheap.size())
                {
                    if (!mincomp(minheap[curr], minheap[2 * curr + 1]) && !mincomp(minheap[curr], minheap[2 * curr + 2]))
                        break;
                    else
                    {
                        if (mincomp(minheap[2 * curr + 2], minheap[2 * curr + 1]))
                        {
                            swap(minheap[curr], minheap[2 * curr + 1]);
                            curr = 2 * curr + 1;
                        }
                        else
                        {
                            swap(minheap[curr], minheap[2 * curr + 2]);
                            curr = 2 * curr + 2;
                        }
                    }
                }
                else if (2 * curr + 1 < minheap.size())
                {
                    if (mincomp(minheap[curr], minheap[2 * curr + 1]))
                    {
                        swap(minheap[curr], minheap[2 * curr + 1]);
                        curr = 2 * curr + 1;
                    }
                    else
                        break;
                }
                else
                    break;
            }
        }
        return;
    }
};
template <typename T, typename compare = maxcomparator<T>>
class MaxHeap
{
private:
    vector<T> maxheap;

public:
    compare maxcomp;
    void push(T val)
    {
        if (maxheap.empty())
            maxheap.push_back(val);
        else
        {
            maxheap.push_back(val);
            int curr = maxheap.size() - 1;
            int parent = (curr - 1) / 2;
            while (parent >= 0)
            {
                if (maxcomp(maxheap[parent], maxheap[curr]))
                {
                    swap(maxheap[parent], maxheap[curr]);
                    curr = parent;
                    parent = (curr - 1) / 2;
                }
                else
                    break;
            }
        }
        return;
    }
    T top()
    {
        if (maxheap.empty())
        {
            cout << "Error!!!\n";
            return T();
        }
        return maxheap.front();
    }
    void pop()
    {
        if (maxheap.empty())
        {
            cout << "Error!!!\n";
        }
        else
        {
            swap(maxheap[0], maxheap[maxheap.size() - 1]);
            maxheap.pop_back();
            int curr = 0;
            while (2 * curr + 1 < maxheap.size())
            {
                if (2 * curr + 2 < maxheap.size())
                {
                    if (!maxcomp(maxheap[curr], maxheap[2 * curr + 1]) && !maxcomp(maxheap[curr], maxheap[2 * curr + 2]))
                        break;
                    else
                    {
                        if (maxcomp(maxheap[2 * curr + 1], maxheap[2 * curr + 2]))
                        {
                            swap(maxheap[curr], maxheap[2 * curr + 2]);
                            curr = 2 * curr + 2;
                        }
                        else
                        {
                            swap(maxheap[curr], maxheap[2 * curr + 1]);
                            curr = 2 * curr + 1;
                        }
                    }
                }
                else if (maxcomp(maxheap[curr], maxheap[2 * curr + 1]))
                {
                    swap(maxheap[curr], maxheap[2 * curr + 1]);
                    curr = 2 * curr + 1;
                }
                else
                    break;
            }
        }
        return;
    }
};
int main(){}