#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

std::function<bool(int)> is_even = [](int x) -> bool
{
	return x % 2 ? false : true;
};

//使用auto关键字自动推导
auto isEven = [](int x) -> bool
{
	return x % 2 == 0;
};

int main()
{
	//是否容器内所有元素都是偶数
	std::vector<int> intArray = { 2, 4, 6, 8, 10 };
	bool bIsEven = std::all_of(intArray.begin(), intArray.end(), isEven);
	if (bIsEven) 
	{
		std::cout << "yes, all elements is even" << std::endl;
	}
	else
	{
		std::cout << "no, not all elements is even" << std::endl;
	}

    return 0;
}
