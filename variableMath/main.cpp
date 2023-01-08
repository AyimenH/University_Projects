/*
11N^3 + logN + 12sqrt(N): By testing the growth rate of these terms using a calculator 11N^3 seems to grow the quickest. T(N) is time complexity and the worst case scenario (slowest possible run time) IS T(N). Just 11N^3 being exponential makes it the clear worst case as well. Big O however is the smallest T(N) value that is still the upper bound. 11N^3 is constant C * constant N to a power of 3. When we get to a large enough constant N (N being the amount of times an action/operation is done) the C constant has a menial effect on its value. Thus for simplictiy and practicallity N^3 is our O(N)
*/

#include <iostream>
#include <cmath> // told to include in the Canvas page
#include <queue>
using namespace std;

double y = 1;

int sumDigits(int d)
{

  if (d / 10 == 0)
  {
    return d;
  }
  else
  {
    return sumDigits(d % 10) + sumDigits(d / 10);
  }
}

double rootHelper(double n, double y)
{

  if (abs(pow(y, 5) - n) < 0.00001)
  {
    return y;
  }

  y = (4 * y + (n / pow(y, 4))) / (5);
  return rootHelper(n, y);
}
double root5(double n)
{
  double x = 1.0;
  return rootHelper(n, x);
}

int doubleInt(int x)
{
  int Multiple = x + x;
  return Multiple;
}

int halveInt(int val, int Ans)
{
  int Final = 2;
  if (val == Final)
  {
    return Ans;
  }
  else if (Final > val)
  {
    Ans--;
    return Ans;
  }
  val -= 2;

  return Ans += halveInt(val, Ans);
}

int egyptDivision(int Divisor, int Dividend)
{
  int a;
  int b;
  int c;
  int d;
  int Ans = 1;

  a = 1;
  b = Divisor;
  c = Dividend;

  while (b < c)
  {
    a = doubleInt(a);
    b = doubleInt(b);
  }

  d = 0;

  while (a >= 1)
  {
    if (b <= c)
    {
      d = a + d;
      c = c - b;
    }
    a = halveInt(a, Ans);
    b = halveInt(b, Ans);
  }

  return d;
}

int l = 0;

double ramanujan(int d)
{
  if (d == 0)
  {
    return sqrt(6);
  }

  int firstRadical = l + 6;
  int coEff = l + 1;
  l++;

  if (d == l)
  {
    return firstRadical * sqrt(coEff);
  }

  return firstRadical * sqrt(coEff + ramanujan(d));
}

int main()
{
 // int d = 0;
  //int sumDigits(int n);

  //cout << "Provide your values with NO commas or spaces between them: ";
  //cin >> d;
  //cout << "Your value is " << sumDigits(d) << endl;

 // double n = 243;
//  double num = root5(n);
 // cout << num << endl;
 // double rootHelper(double n, double y);

 // cout << "Provide a value to calculate its fifth root: ";
 // cin >> n;
 // cout << "The fifth root of " << n << " is " << root5(n, y) << endl;

 // int egyptDivision(int Divisor, int Dividend);
 // cout << egyptDivision(56, 1960);

  return 0;
}
