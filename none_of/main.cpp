#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
	std::vector < int > scores = { 78, 89, 94, 97 };
	//是否没有一科分数低于60分
	bool result = std::none_of(scores.begin(), scores.end(), [](const int& score) 
		{
			return score < 60;
		});

	if (result)
	{
		std::cout << "yes, all scores are above 60" << std::endl;
	}
	else 
	{
		std::cout << "no, all scores are below 60" << std::endl;
	}

    return 0;
}
