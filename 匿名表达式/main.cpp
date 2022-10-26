#include<bits/stdc++.h>

using namespace std;


int g_num = 10;		// 全局变量
int func() { return 10; }	// 全局函数
static int s_func() { return 10; }	// 静态函数
int main()
{
	static int s_num = 100;	// 静态变量

	cout  << []() {return g_num + 10; }() << endl;	// lambda+全局变量

	cout << []() {return s_num + 10; }() << endl;	// lambda+静态变量

	cout << []() {return func() + 10; }() << endl;	// lambda+全局函数

	cout << []() {return s_func() + 10; }() << endl;	// lambda+全局静态函数

	return 0;
}
