#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace king
{
	template<class T, class Container=vector<T>>
	class priority_queue
	{
	public:
		//迭代器区间初始化的构造函数
		template<class InputIterator>
		priority_queue(InputIterator first,InputIterator last)
			:_con(first,last)
		{}
		//无参的构造函数
		priority_queue()
		{}
		//插入（尾插）
		void push(const T& x);
		//删除（变相头删，交换头尾再尾删）
		void pop();
		//返回容器有效元素个数
		size_t size() const;
		//返回堆顶元素
		T& top();
		//判空
		bool empty();
	private:
		Container _con;//默认是vector<T> _con;
	};
}
