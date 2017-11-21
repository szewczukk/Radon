#include <Radon.hpp>

#include <iostream>

int main()
{
	radon::File file("File.ini");

	std::cout << "Width of window = " << file.getSection("Window")->getKey("width").getStringValue().data() << std::endl;
	std::cout << "Height of window = " << file.getSection("Window")->getKey("height").getStringValue().data() << std::endl;
	
	file.getSection("Window")->addKey(radon::Key("A", "a"));

	std::cout << file.getSection("Window")->getKey("A").getStringValue() << std::endl;

	file.saveToFile();

	system("PAUSE");

	return 0;
}