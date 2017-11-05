#include <Radon.hpp>

#include <iostream>

int main()
{
	radon::File file("File.ini");

	std::cout << file.getCategory("Window").getVariable("width").getStringValue().data();

	system("PAUSE");

	return 0;
}