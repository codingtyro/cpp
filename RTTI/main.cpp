
#include <cstdlib>
#include <ctime>
#include<iostream>
 
using std::cout;
class Grand
{
private:
  int hold;
public :
  Grand(int h = 0) :hold(h) {}
  virtual void Speak() const { cout << "I am a grand class \n"; }
  virtual int Value() const { return hold; }
};
 
class Superb :public Grand
{
public :
  Superb(int h = 0) :Grand(h) {}
  void Speak() const { cout << "I am a superb class ! \n"; }
  virtual void Say() const
  {
    cout << "I hold the superb value of " << Value() << "! \n";
  }
};
 
class Magnificent : public Superb
{
private :
  char ch;
public :
  Magnificent(int h = 0, char c = 'A') :Superb(h), ch(c)
  {
  }
  void Speak() const
  {
    cout << "I am a magnificent class !!!! \n";
  }
  void Say() const
  {
    cout << "I hold the character " << ch << " and the integer " << Value() <<"! \n";
  }
};
 
Grand * GetOne();
int main()
{
  std::srand(static_cast<unsigned int>(std::time(0)));
  Grand * pg;
  Superb * ps;
  for (int i = 0; i < 5; i++)
  {
    pg = GetOne();
    pg->Speak();
    if (ps = dynamic_cast<Superb *>(pg)) {
      ps->Say();
    }
  }
  system("pause");
  return 0;
}
Grand * GetOne()
{
  Grand * p = new Grand();
  switch (std::rand() % 3)
  {
    delete p;
  case 0:p = new Grand(std::rand() % 100); break;
  case 1:p = new Superb(std::rand() % 100); break;
  case 2:p = new Magnificent(std::rand() % 100, std::rand() % 26); break;
  }
 
  return p;
}


/**
 * 运行结果:
 * I am a superb class !
 * I hold the superb value of 3!
 * I am a magnificent class !!!
 * I hold the character and the integer 5!
 * I am a grand class
 * I am a grand class
 * I am a magnificent class !!!
 * I hold the character and the integer 87!
*/
