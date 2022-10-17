#include<bits/stdc++.h>
using namespace std;

/**
 * 重载运算符的规则
 * 不允许创造新的运算符, 只能对已有 C++ 运算符进行重载.
 * 重载不能改变运算符运算对象 (即操作数) 的个数
 * 重载不能改变运算符的优先级别
 * 重载不能改变运算符的结合性
 * 重载运算符的函数不能有默认的参数
 * 重载的运算符必须和用户定义的自定义类型的对象一起使用. 参数至少有一个是类对象或其 引用
 * 
 * 
 * 对已有的运算符赋予多重含义，使得同一运算符作用于不同数据类型的数据时导致不同类型的行为。
 * 形式：
 * 返回值类型 operator 运算符(形参表){}
 * 注意，当重载为成员函数时，参数个数为运算符数目-1.
*/

class Complex{
	public:
		double real,imag;
		Complex(double r = 0.0,double i = 0.0):real(r),imag(i){}
		Complex operator-(const Complex &c);//声明重载为成员函数
        Complex operator+(const Complex &c);
};
Complex Complex::operator+(const Complex &c)
{
	return Complex(real+c.real,imag+c.imag);//返回临时对象
}
Complex Complex::operator-(const Complex &c)
{
	return Complex(real-c.real,imag-c.imag);//只需一个参数，a-b相当于a.operator-(b)
}


int main(){
    Complex a(3,4),b(2,2);
    cout << (a + b).real << (a + b).imag << endl;
    cout << (a - b).real << (a - b).imag << endl;
}