#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string filepath)
{
	std::ifstream stream(filepath);
	if (stream)
	{
		std::string result;
		//read file
		stream.close();
		return result;
	}
	return {};
}

int main()
{
	std::optional<std::string> data = ReadFileAsString("data.txt");
	if (data)
	{
		std::cout << "File read successuflly!\n";
	}
	else
	{
		std::cout << "File could not be opened\n";
	}
}