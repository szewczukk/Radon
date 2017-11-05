#include <Radon.hpp>

#include <iostream>

int main()
{
	radon::File file("File.ini");

	std::cout << "Width of window = " << file.getSection("Window").getKey("width").getStringValue().data() << std::endl;
	std::cout << "Height of window = " << file.getSection("Window").getKey("height").getStringValue().data() << std::endl;

	radon::File f("a.ini");
	f.addSection(radon::Section("ASD"));

	f.saveToFile();

	system("PAUSE");

	return 0;
}