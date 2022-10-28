/**
 * C++ IO流，使用面向对象+运算符重载的方式，能更好的兼容自定义类型，流插入和流提取
 * C++IO流，自动识别类型的本质–函数重载，内置类型可以直接使用–因为库里面ostream类型已经实现了
 * 在while(cin>>d)这类语句中，输入换行 + ctrl+Z（正常退出）用于结束该输入或者输入ctrl+c（终止）
 * getline和cin的区别在于cin遇到空格或者换行会刷新缓冲区而getline遇到换行会刷新缓冲区
 * 对于自定义类型想要循环输入，需要实现operator bool和operator >>函数
*/

#include<bits/stdc++.h>
using namespace std;
class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	operator bool()
	{
		if (_year == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
private:
	int _year;
	int _month;
	int _day;
};

istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}


int main()
{

	Date d(2022, 4, 10);
	cout << d<<endl;

	string str;
	//cin >> str;
	getline(cin, str);
	cout << str;
	//while (cin>>str) // operator>>(cin, str)
	// 这里本质相当于下面的调用
	//while ((cin >> str).operator bool())
	
	
	while (d)
	{
		cin >> d;
		cout << d;
	}

	return 0;
}
