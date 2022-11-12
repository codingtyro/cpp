#include<iostream>
#include<typeinfo>   //需要添加的头文件
using namespace std;
 
int main()
{
    //typeid().name()不仅可以可以获取变量类型，还可以获取、函数、类的数据类型名
    //对于非引用类型，typeid().name()是在编译期间识别的，只有引用类型在运行时识别
	int a;
	cout<<typeid(a).name()<<endl;   //int
    cout<<typeid(typeid(a).name()).name()<<endl;   //const char *
	const int b=3;
	cout<<typeid(b).name()<<endl;   //int
	int &c=a;
	cout<<typeid(c).name()<<endl;   //int
	int *d;
	cout<<typeid(d).name()<<endl;   //int *
	const int *e;  //常指针可以不用初始化
	cout<<typeid(e).name()<<endl;   //const int *
	const int &f=a;  //引用必须必须初始化
	cout<<typeid(f).name()<<endl;   //int
        
    return 0;
    //经过验证可以看出const修饰变量是不影响变量类型的，但是const修饰指针，是影响其类型的
    //const修饰引用不会改变引用变量的类型
    //对于cout<<typeid(typeid(a).name()).name()<<endl;返回了存储类型名的字符串
}
 