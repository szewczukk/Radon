#include <Radon.hpp>

#include <iostream>

int main()
{
	radon::File file("File.ini");

	std::cout << file.getSection("Window").getKey("width").getStringValue().data();

	system("PAUSE");

	return 0;
}