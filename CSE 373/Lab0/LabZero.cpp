#include <iostream> // #include functions like import in Java, a part of the starter code for every project
using namespace std; // allows us to use basic functions without having to specify where it's from, could also be part of starter code
// namespaces can be used simultaneuosly with the same variable but "X"::Variable would be the layout
#include <string> // imports common string functions like length(), s.empty(), s.at(x), s.append("new string"), s.find_first_of('y')

int main(){ // int type is most commonly used for main, second is void
    cout << "Hello World!"; // cout is how you print/ output, "<<" seperates elements when printing like a , in Java
  return 0;// prevents error from not returning an integer
  }

//! int, double, char, bool are the most common types in C++
//! cin >> is how you recieve input, putting ">>" between variables lets you recieve multiple
//! if, while, for all function the same as Java
//! endl is C++'s equivalent of \n in Java for new line

/* 
struct Pet{ // struct lets you create a new type
  string name;
  int age;
  char type;
  };

  Pet myPet; // This is how you declare a varaiable with your new type
 */

/*
Linked list require using struct, using a pointer, & deallocating memory after being used

ptr->data = 24 // This is how to input a value into a specific list

struct Node{ // Starter code for a linked list
  int data;
  Node* next;
};

 while (data != nullptr){ // This is an example of deallocating after using a linked list
    temp = data;       // we need a pointer to delete this node
    data = data->next;  // we can now move head to the next node
    delete temp;    // deallocating the node memory
  }

*/

/*
int main (){
  int i = 9; //** #include <vector> is importing the Vector Library
  vector<int> v; //** vector<type> name; is the layout for Vectors
  v.push_back(1); //** places an integer into "slot" 1
  for(int i = 0; i<v.size(); i++){ //** iterates i until larger than vector size
    cout << v[i] << endl; //** v[i] allows you to iterate the vector
  }
}
*/