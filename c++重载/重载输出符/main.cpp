#include <iostream>
using namespace std;
 
// 自定义类 A
class A {
public:
	A():_value(10){}
	~A(){}
	
public:
	// 重载 << 运算符
	friend ostream& operator<<(ostream& out, A& a) {
		out << a._value;
		return out;
	}
 
	// 重载 >> 运算符
	friend istream& operator>>(istream& in, A& a) {
		in >> a._value;
		return in;
	}
 
private:
	int _value;
};
 
int main(int argc, char **argv)
{
	A a;
	cin >> a;
	cout << a << endl;
	return 0;
}