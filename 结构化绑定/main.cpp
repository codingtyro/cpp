#include <iostream>
using namespace std;
 
class A{
public:
	int d1 = 1;
	int d2 = 2;
};
int main()
{
    int a[] = {1, 2, 3};
    auto &[m1,m2,m3] =  a;                     //绑定到数组
    cout<<m1++<<" "<<m2++<<" "<<m3++<<endl;    //输出：1 2 3
    for(auto item : a)
    {
    	cout<<item<<" ";                       //输出：2 3 4
    }
    cout<<endl;
 
    auto [n1, n2] =  A();                      //绑定到对象
    cout<<n1<<" "<<n2<<endl;                   //输出：1 2
    return 0;
}
 
// 需要注意的是：绑定到类对象的话，只能绑定public成员变量