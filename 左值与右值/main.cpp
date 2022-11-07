#include<iostream>
#include<string>

#define func(x)  _func(x,"func("#x")") 
using namespace std;

void _func(int &x,string str){ //左值值重载_func()
    cout << str << "left value !"<<endl;
    return ;
}

void _func(int &&x,string str){ //右值重载_func()
    cout << str << "right value !"<<endl;
    return ;
}
int main(){
    int x = 3;
    int y = 4;
    func(123);
    func(x++);
    func(++x);
    func(x*3);
    func(x*=3);
    func(y/4);
    func(y/=4);
    return 0;
}

