#include <iostream>
#include <string>
using namespace std;

class Box
{
public:
  int length;
  int width;
  int height;
};

Box AddBox(Box box1, Box box2)
{
  Box box3;

  box3.width = box1.width + box2.width;
  box3.height = box1.height + box2.height;

  if (box1.length >= box2.length)
    box3.length = box1.length;
  else
  {
    box3.length = box2.length;
  };

  cout << "The length is: " << box3.length << " The width is: " << box3.width << " The height is: " << box3.height << endl;

  return box3;
}

int Palindrome(string input)
{
  for (int i = 0; i < input.length() / 2; i++)
  {
    if (input[i] != input[input.length() - i - 1])
    {
      return 0;
    }
  }
  return 1;
}

int main()
{
  int F = 0;
  int D = 0;
  int C = 0;
  int B = 0;
  int A = 0;
  int Grade = 0;

  cout << "Provide your percentage grade as an INTGER: ";
  cin >> Grade;

  if (Grade <= 59)
  {
    cout << "Your grade is an F" << endl;
  }
  if (Grade >= 60 && Grade <= 69)
  {
    cout << "Your grade is an D" << endl;
  }
  if (Grade >= 70 && Grade <= 79)
  {
    cout << "Your grade is an C" << endl;
  }
  if (Grade >= 80 && Grade <= 89)
  {
    cout << "Your grade is an B" << endl;
  }
  if (Grade >= 90 && Grade <= 100)
  {
    cout << "Your grade is an A" << endl;
  }

  int length1 = 0;
  int width1 = 0;
  int height1 = 0;
  int length2 = 0;
  int width2 = 0;
  int height2 = 0;

  cout << "Provide length, width, & height of box 1 as an INTEGER: ";
  cin >> length1 >> width1 >> height1;

  cout << "Provide length, width, & height of box 2 as an INTEGER: ";
  cin >> length2 >> width2 >> height2;

  Box box1;
  Box box2;

  box1.length = length1;
  box1.width = width1;
  box1.height = height1;

  box2.length = length2;
  box2.width = width2;
  box2.height = height2;

  AddBox(box1, box2);

  string input;

  cout << "Provide a name: ";
  cin >> input;
  cout << Palindrome(input) << endl;

  return 0;
}