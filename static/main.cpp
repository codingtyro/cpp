#include<iostream>
 
 
using namespace std;
 
 
class Rectangle
{
private:
	int m_w,m_h;
	static int s_sum;
	
public:
	Rectangle(int w,int h)
	{
		this->m_w = w;
		this->m_h = h;
		s_sum += (this->m_w * this->m_h);
	}
 
 
	void GetSum()
	{
		cout<<"sum = "<<s_sum<<endl;
	}
 
 
};
 
 
int Rectangle::s_sum = 0;  //初始化
 
 
 
 
int main()
{
	cout<<"sizeof(Rectangle)="<<sizeof(Rectangle)<<endl;
	Rectangle *rect1 = new Rectangle(3,4);
	rect1->GetSum();
	cout<<"sizeof(rect1)="<<sizeof(*rect1)<<endl;
	Rectangle rect2(2,3);
	rect2.GetSum();
	cout<<"sizeof(rect2)="<<sizeof(rect2)<<endl;
	
	system("pause");
	return 0;
}
