// Create a short program that requests two INTEGERS from the user. The program then decides if the first integer input is a multiple of the second integer input and outputs the appropriate response. If the first integer IS a multiple of the second integer, the other factor is also supplied. For instance, if the first integer input is 20 and the second integer input is 5, the answer is "yes and the other factor is 4". The program should repeat the input and output until the user wishes to quit.

#include <iostream>
using namespace std;

int main()
{
  int Integer1 = 0, Integer2 = 0, Remainder = 0, Factor = 0; // Integers set to 0 so they can be used in input

  cout << "Takes two integers and determines if the first is a multiple of the second!" << endl;
  cout << "Provide two integers:";
  cin >> Integer1 >> Integer2;

  Remainder = Integer1 % Integer2;
  Factor = Integer1 / Integer2;

  if (Remainder == 0)
  {
    cout << Integer1 << " is a multiple & the other factor is " << Factor;
  }
  else
  {
    cout << Integer1 << " is not a multiple";
  }

  return 0;
}
