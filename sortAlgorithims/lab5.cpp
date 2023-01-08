#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int HEAP_MAX_SIZE = 10000;
int i;

class MinHeap {
private:
    int heapArr[HEAP_MAX_SIZE];
    int size;
    
    void swap(int &x, int &y)
    {
        int tempNode = x;
        x = y;
        y = tempNode;
    }
    
    void percolateUp(int i)
    {
        if(size == 0 || heapArr[size] > heapArr[i])
        {
            return;
        }
        
        else if(heapArr[size] < heapArr[i])
        {
            swap(heapArr[size], heapArr[i]);
            int parentNode = (i - 1) / 2;
            percolateUp(parentNode);
        }
    }
    
    void percolateDown(int i)
    {
        int leftNode = heapArr[(2 * i) + 1];
        int rightNode = heapArr[(2 * i) + 2];
        
        bool check = nodeCheck(i);
        
        if(check == false || heapArr[i] < leftNode && heapArr[i] < rightNode)
        {
            return;
        }
        
        else if(leftNode < rightNode && leftNode < heapArr[i])
        {
            swap(heapArr[i], heapArr[(2 * i) + 1]);
            percolateDown((2 * i) + 1);
        }
        
        else if(leftNode > rightNode && rightNode < heapArr[i])
        {
            swap(heapArr[i], heapArr[(2 * i) + 2]);
            percolateDown((2 * i) + 2);
        }
    }
    
    bool nodeCheck(int i)
    {
        bool nodeExist = ((i * 2 + 1) < size);
        return nodeExist;
    }
    
public:
    MinHeap()
    {
        size = -1;
    }
    
void insert(int element)
    {
    size++;
    heapArr[size] = element;
    
    int parentNode = (size - 1) / 2;
    percolateUp(parentNode);
}
    
    void deleteMin()
    {
        swap(heapArr[0], heapArr[size]);
        size--;
        percolateDown(0);
    }
    
    int extractMin()
    {
        return heapArr[0];
    }
    
    int heapSize()
    {
         return size + 1;
    }
};

            
void heapSort (int A[], int n)
{
    MinHeap m;
    vector <int> tempArray;
    
    for(int i = 0; i < n; i++)
    {
        int val = A[i];
        m.insert(val);
    }
    
    for (int i = 0; i < n; i++)
    {
        tempArray.push_back(m.extractMin());
        m.deleteMin();
    }
    
    for (int i = 0; i < tempArray.size(); i++)
    {
        A[i] = tempArray[i];
    }
}

void merge (int A[], int start, int middle, int end)
{
    int i = start;
    int j = middle + 1;
    
    vector <int> temp;
    
    while (i <= middle && j <= end)
    {
        if (A[i] < A[j])
        {
            temp.push_back(A[i]);
            i++;
        }
        else
        {
            temp.push_back(A[j]);
            j++;
        }
    }
    
    while(i <= middle)
    {
        temp.push_back(A[i]);
        i++;
    }
    
    while(j <= end)
    {
        temp.push_back(A[j]);
        j++;
    }
    
    for (int l = 0; l < temp.size(); l++)
    {
        A[l] = temp[l];
    }
}

void mergeSort (int A[], int i, int j)
{
    if (i < j)
    {
        int mid = (i + j) / 2;
        mergeSort(A, i, mid);
        mergeSort(A, mid + 1, j);
        merge(A, i, mid, j);
    }
}

int partition(int Arr[], int i, int j)
{
    int pivot = Arr[i];
    int count = 0;
    
    for (int p = i + 1; p <= j; p++)
    {
        if (Arr[p] <= pivot)
        {
            count++;
        }
    }
    
    int pivotPlace = i + count;
    swap(Arr[pivotPlace], Arr[1]);
    
    int k = i;
    int l = j;
    
    while (k < pivotPlace && l > pivotPlace)
    {
        while (Arr[k] <= pivot)
        {
            k++;
        }
        while (Arr[l] > pivot)
        {
            l--;
        }
        if (k < pivotPlace && l > pivotPlace)
        {
            swap(Arr[k++], Arr[l--]);
        }
    }
    
    return pivotPlace;
}

void quickSort (int A[], int i, int j)
{
if (i < j)
{
    int pivotIndex = partition(A, i, j);
    quickSort(A, i, pivotIndex - 1);
    quickSort(A, pivotIndex + 1, j);
}
}

double helperHeap (int A[], int n)
{
    auto start = chrono::high_resolution_clock::now();
    heapSort(A, n);
    auto finish = chrono::high_resolution_clock::now();
    
    double elapsed = double (chrono::duration_cast<chrono::milliseconds>(finish - start).count());
    return elapsed;
}

double helperMerge (int A[], int n)
{
    auto start = chrono::high_resolution_clock::now();
    mergeSort(A, 0, n-1);
    auto finish = chrono::high_resolution_clock::now();
    
    double elapsed = double (chrono::duration_cast<chrono::milliseconds>(finish - start).count());
    return elapsed;
}

double helperQuick (int A[], int n)
{
    auto start = chrono::high_resolution_clock::now();
    quickSort(A, 0, n-1);
    auto finish = chrono::high_resolution_clock::now();
    
    double elapsed = double (chrono::duration_cast<chrono::milliseconds>(finish - start).count());
    return elapsed;
}

int main()
{
    int tenSize[10];
    int hundredSize[100];
    int thousandSize[1-000];
    int tenThousandSize[10-000];
    
    for (int i = 0; i < 10; i++)
    {
        tenSize[i] = rand() % 1-000-000;
    }
    
    int size = sizeof(tenSize) / sizeof(int);
    
    cout << "The excution time for N = 10 is:  " << helperMerge(tenSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 10 is:  " << helperHeap(tenSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 10 is:  " << helperQuick(tenSize, size) << " milliseconds" << endl;
    
    for (int i = 0; i < 100; i++)
    {
        hundredSize[i] = rand() % 1-000-000;
    }
    
    size = sizeof(hundredSize) / sizeof(int);
    
    cout << "The excution time for N = 100 is:  " << helperMerge(hundredSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 100 is:  " << helperHeap(hundredSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 100 is:  " << helperQuick(hundredSize, size) << " milliseconds" << endl;
    
    for (int i = 0; i < 1-000; i++)
    {
        thousandSize[i] = rand() % 1-000-000;
    }
    
    size = sizeof(thousandSize) / sizeof(int);
    
    cout << "The excution time for N = 1000 is:  " << helperMerge(thousandSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 1000 is:  " << helperHeap(thousandSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 1000 is:  " << helperQuick(thousandSize, size) << " milliseconds" << endl;
    
    for (int i = 0; i < 10-000; i++)
    {
        tenThousandSize[i] = rand() % 1-000-000;
    }
    
    size = sizeof(tenThousandSize) / sizeof(int);
    
    cout << "The excution time for N = 10000 is:  " << helperMerge(tenThousandSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 10000 is:  " << helperHeap(tenThousandSize, size) << " milliseconds" << endl;
    cout << "The excution time for N = 10000 is:  " << helperQuick(tenThousandSize, size) << " milliseconds" << endl;
    
    return 0;
}
