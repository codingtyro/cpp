#include<bits/stdc++.h>
using namespace std;

// 重载operator delete，在申请空间时：打印在哪个文件、哪个函数、第多少行，申请了多少个
// 字节
void* operator new(size_t size, const char* fileName, const char* funcName,
	size_t lineNo)
{
	void* p = ::operator new(size);
	cout << fileName << "-" << funcName << "-" << lineNo << "-" << p << "-"
		<< size << endl;
	return p;
}
// 重载operator delete，在释放空间时：打印再那个文件、哪个函数、第多少行释放
void operator delete(void* p, const char* fileName, const char* funcName,
	size_t lineNo)
{
	cout << fileName << "-" << funcName << "-" << lineNo << "-" << p <<
		endl;
	::operator delete(p);
}
int main()
{
	// 对重载的operator new 和 operator delete进行调用
	int* p = new(__FILE__, __FUNCTION__, __LINE__) int;
	operator delete(p, __FILE__, __FUNCTION__, __LINE__);
	return 0;
}
// 上述调用显然太麻烦了，可以使用宏对调用进行简化
// 只有在Debug方式下，才调用用户重载的 operator new 和 operator delete
#ifdef _DEBUG
#define new new(__FILE__, __FUNCTION__, __LINE__)
#define delete(p) operator delete(p, __FILE__, __FUNCTION__, __LINE__)
#endif
int main()
{
	int* p = new int;
	delete(p);
	return 0;
}