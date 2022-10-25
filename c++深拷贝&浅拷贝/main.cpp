#include <iostream>
#include <string.h>
using namespace std;

class Test {
public:
    Test():ptr(new char[1]) { // 带参数的构造函数
        cout << "Test():ptr(new char[1])" << endl;
    }
    Test operator=(const Test& obj)
    {
        if (this == &obj) { // s=s
            return *this;
        }
        delete[] ptr;
        ptr = new char[strlen(obj.ptr) + 1];
        strcpy(ptr, obj.ptr);
        cout << "Test& operator=(const Test& obj)" << endl;
        return *this;
    }
    Test& operator=(const char *s)
    {
        delete[] ptr;
        ptr = new char[strlen(s) + 1];
        strcpy(ptr, s);
        cout << "Test& operator=(const Test& obj)" << endl;
        return *this;
    }
    ~Test() { // 析构函数
        delete[] ptr;
    }
private:
    char* ptr;
};

int main() {
    Test a;
    a= "test";
    Test b;
    b= a;
    Test d;
    getchar();
    return 0;
}
