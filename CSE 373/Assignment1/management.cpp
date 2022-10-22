#include "management.h"

class Animal
{
public:
  string animalName;
  int Count;
};

queue<Animal> DogQueue;
queue<Animal> CatQueue;

int Counter = 0;

void Functions::addAnimal()
{
  Animal Dog;
  Animal Cat;

  string AnimalName;
  int CatorDogNum = 0;

  cout << "Enter animal name: ";
  cin >> AnimalName;

  cout << "Enter '0' if dog, otherwise enter '1' for cat: ";
  cin >> CatorDogNum;

  if (CatorDogNum == 0)
  {
    Dog.animalName = AnimalName;
    Dog.Count = Counter;
    DogQueue.push(Dog);
    Counter++;
  }
  else
  {
    Cat.animalName = AnimalName;
    Cat.Count = Counter;
    CatQueue.push(Cat);
    Counter++;
  }
}

void Functions::getDog()
{
  cout << "Your dog's name is " << DogQueue.front().animalName << endl;

  DogQueue.pop();
}

void Functions::getCat()
{
  cout << "Your cat's name is " << CatQueue.front().animalName << endl;

  CatQueue.pop();
}

void Functions::getAnimal()
{
  if (DogQueue.front().Count < CatQueue.front().Count)
  {
    cout << "Your new pet is a dog named " << DogQueue.front().animalName;

    DogQueue.pop();
  }
  else
  {
    cout << "Your new pet is a cat named " << CatQueue.front().animalName;

    CatQueue.pop();
  }
}

void Functions::UserInterface()
{

  bool IsOn = true;
  int Case;

  while (IsOn != false)
  {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    cout << "Press '1' to add an animal \n";
    cout << "Press '2' to adopt a dog \n";
    cout << "Press '3' to adopt a cat \n";
    cout << "Press '4' to adopt any animal \n";
    cout << "Press '5' to exit the interface \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";

    cout << "Choice: ";
    cin >> Case;

    switch (Case)
    {
    case 1:
      addAnimal();
      break;

    case 2:
      if (DogQueue.empty())
      {
        cout << "Sorry No dogs are available \n";
      }
      else
      {
        getDog();
      }
      break;

    case 3:
      if (CatQueue.empty())
      {
        cout << "Sorry No cats are available \n";
      }
      else
      {
        getCat();
      }
      break;

    case 4:
      if (DogQueue.empty() && CatQueue.empty())
      {
        cout << "Sorry No animals are available \n";
      }

      else if (DogQueue.empty())
      {
        getCat();
      }

      else if (CatQueue.empty())
      {
        getDog();
      }

      else if (DogQueue.front().Count < CatQueue.front().Count)
      {
        getDog();
      }

      else if (CatQueue.front().Count < DogQueue.front().Count)
      {
        getCat();
      }

      else
      {
        getAnimal();
      }
      break;

    case 5:
      IsOn = false;
      break;
    }
  }
}