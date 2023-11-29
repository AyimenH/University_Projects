#include <iostream>
using namespace std;

int getSet(int set); // loop taking in user input for setA and setB
void printSet(int set); // takes user input set and prints out the binary

int main() {
  cout << "Welcome to HW 2: programming!  Given subsets A and B of a universal set with 10 elements" << endl
<< "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, we will use bit strings to find A U B, A ∩ B, and A – B." << endl
<< "Users will be asked to populate each set." << endl;

  int setA = 0; // a variable to save the bit vector of set A
  int setB = 0; // a variable to save the bit vector of set B
  
  // gets setA and setB from user input
  cout << endl << "Set A: " << endl;
  setA = getSet(setA);

  cout << endl << "Set B: " << endl;
  setB = getSet(setB);
  cout << endl;

  cout << "Set A: ";
  printSet(setA);

  cout << "Set B: ";
  printSet(setB);

// calcuates union, disjunction, and difference

  int unionSet = setA | setB; // from Week 3 Wednesday slides
  int interSet = setA & setB;
  int diffSet = setA & ~setB;
  cout << endl;

  cout << "Union: ";
  printSet(unionSet);

  cout << "Intersection: ";
  printSet(interSet);

  cout << "Difference: ";
  printSet(diffSet);

  return 0;
}

int getSet(int set){
  int userInput; // a variable to save the user input

  while (userInput != -1) { // keeps loop open until an invalid number
    cout << "Please enter a number for the set (enter -1 to stop): ";
    cin >> userInput;
    set |= (1 << userInput); // | is the bitwise-or; << is the left shift operator, used set instead individual variables for A & B
  }
  return set;
}

void printSet(int set){
  for (int i = 9; i >= 0; i--) {
    int mask = 512; // based on 2^9 = 512, 0-9 is 10 bits, from the rubric
    mask >>= i; // starts from least significant bit and builds set from right to left** 
    // **(values are displayed left to right though like 2 = 0010 0000 00)

     if ((set & mask) > 0) { // set & mask seem to be turned into bits and then the operation occours
        cout << "1";
     }
     else {
      cout << "0";
     }
  }
  cout << endl;
}