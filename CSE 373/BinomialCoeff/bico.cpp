// Write a function bico(int x, int y) that returns the ith coefficient of binomial (x + y)^n.
// Was told to mention using Recursion by the professor

#include <iostream>
using namespace std;

unsigned int Factorial(unsigned int f)
{
  if (f == 0 || f == 1)
    return 1;
  return f * Factorial(f - 1);
}

int main()
{
  int n = 0, i = 0, Answer = 0; // n is the exponent and i is the index of the coeffeicent

  cout << "Input the degree of the binomial: ";
  cin >> n;
  cout << "Input the index of the coefficient: ";
  cin >> i;

  Answer = (Factorial(n)) / ((Factorial(i) * Factorial(n - i))); // nCr or Combination formula
  cout << "The answer is: " << Answer;

  return 0;
}