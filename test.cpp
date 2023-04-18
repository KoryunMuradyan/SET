#include <iostream>
#include <string>

#include "set.hpp"
#include "iterator.hpp"

int main()
{
	stl::set<int> obj2 = {100,200,300,250,275,225,212,219,206,215,
		222,203,209,50,150,125,126,127,218,201,216,214};
	//stl::set<int> obj2;
	obj2.insert(222);
	obj2.insert(209);

	for (auto i : obj2)
	{
		std::cout << i << std::endl;
	}

	//obj2.Delete(222);
	//obj2.Delete(225);
	//obj2.Delete(100);

	return 0;
}
