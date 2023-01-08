// define the max size for the heap array
#include <iostream>
using namespace std;
const int HEAP_MAX_SIZE = 1000;
class MinHeap
{
private:
  int heapArr[HEAP_MAX_SIZE];
  int size;
  void swap(int x, int y)
  {
    // add your code here
  }
  void percolateUp(int index)
  {
    }
  void percolateDown(int index)
  {
    // add your code here
  }

public:
  MinHeap() { size = -1; }
  void insert(int element)
  {
    // add your code here
  }
  void deleteMin()
  {
    // add your code here
  }
  int extractMin()
  {
    // add your code here
    return 0;
  }
  int heapSize()
  {
    // add your code here
    return 0;
  }
  void heapDisplay()
  {
    // add your code here
  }
};
// in your main function, test your implementations. For example,
int main()
{
  MinHeap mh;
  mh.insert(4);
  mh.insert(8);
  mh.insert(1);
  mh.insert(7);
  mh.insert(3);
  // display heap
  mh.heapDisplay(); // the output should be: 1, 3, 4, 8, 7
  // deleteMin
  mh.deleteMin();
  mh.heapDisplay();                // the output should be: 3, 7, 4, 8
                                   // extractMin
  cout << mh.extractMin() << endl; // the output should be: 3
  // heapSize
  cout << mh.heapSize() << endl; // the output should be: 4
  return 0;
}