#include <iostream>
#include "string.h"
#include <fstream>

using namespace std;

//定义了一个实体类 Person
class Person
{
public:
    Person(char* name, int age)
    {
        strcpy(this->name, name);
        this->age = age;
    }
    Person() {}
    void showInfo()
    {
        cout << name << " " << age << endl;
    }
    int getAge()
    {
        return age;
    }
    char * getName()
    {
        return name;
    }

public:
    char name[10] { 0 };
    int age = 0;
};

//二进制文件 进行写
void WriteBinaryFile(Person * ps,int size)
{
    ofstream file("binary.txt",ios::out | ios::binary );
    if (!file.is_open())
    {
        cout << "文件打开失败" << endl;
    }

    for (int i=0;i<size;i++)
    {
        file.write((char*)&ps[i],sizeof(Person));
    }

    file.close();
}

//二进制文件 进行读
Person * ReadBinaryFile()
{
    ifstream file("binary.txt", ios::in | ios::binary);

    if (!file.is_open())
    {
        cout << "文件打开失败" << endl;
    }

    //开辟一块空间 存放读取的数据
    char* temp = new char[sizeof(Person)];
    //或者 Person p;开辟的空间肯定合适
    //Person temp;
    Person* ps = new Person[5];
    int i=0;
    //将数据读入的 temp对应的空间
    while (file.read(temp,sizeof(Person)))
    {
        Person p = *(Person*)temp;
        ps[i] = p;
        i++;
    }

    file.close();
    return ps;
}

int main(int argc, char *argv[])
{
    //序列化操作  往文件中写数据
//    Person* ps = new Person[5];
//    ps[0] = Person("Lay1", 11);
//    ps[1] = Person("Lay1", 12);
//    ps[3] = Person("Lay1", 13);
//    ps[2] = Person("Lay1", 14);
//    ps[4] = Person("Lay1", 15);
//    WriteBinaryFile(ps,5);

    //反序列化操作  程序读取文件中的数据
    Person* ps2;
    ps2 = ReadBinaryFile();
    for (int i=0; i<5; i++)
    {
        cout << ps2[i].getName() << " " << ps2[i].getAge() << endl;
    }

    return 0;
}

