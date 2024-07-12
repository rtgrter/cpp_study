#include <iostream>

struct Vector1
{
	float x, y, z;
	double c;
};

int main()
{
	int offset = (int)&((Vector1*)nullptr)->c;
	std::cout << offset << std::endl;

	std::cin.get();
}