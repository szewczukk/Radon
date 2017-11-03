#include <Radon.hpp>

#include <iostream>

int main()
{
	radon::File file("File.ini");

	std::cout << file.getCategory("Window").getVariable("width").getStringValue().data();

	file.addCategory(radon::Category("ASD"));
	file.getCategory("ASD").addVariable(radon::Variable("QWE", 800.f));

	file.saveToFile();

	system("PAUSE");
	return 0;
}