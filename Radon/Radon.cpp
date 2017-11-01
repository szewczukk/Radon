// Copyright Dmitro bjornus Szewczuk 2017

#include "Radon.hpp"

#include <assert.h>
#include <fstream>
#include <string>
#include <memory>

namespace radon
{
	File::File(const std::string & path)
	{
		std::string buffer;

		std::ifstream stream(path);

		std::string nameOfCurrent = "";

		if (stream.is_open())
		{
			while (std::getline(stream, buffer))
			{
				if (buffer[0] == ';') continue;
				if (buffer[0] == '[')
				{
					nameOfCurrent = buffer.substr(1, buffer.size() - 2);
					categories[nameOfCurrent].setName(nameOfCurrent);
				}
				else
				{
					int equalsPosition = buffer.find("=");

					std::string nameOfElement = buffer.substr(0, equalsPosition - 1);
					std::string valueOfElement = buffer.substr(equalsPosition + 1, buffer.size());

					categories[nameOfCurrent].variables[nameOfElement].name = nameOfElement;
					categories[nameOfCurrent].variables[nameOfElement].value = valueOfElement;
				}
			}
		}

		assert(1);
	}


	Category File::getCategory(const std::string & name)
	{
		for each (auto var in categories)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
		return Category();
	}


	Variable Category::getVariable(const std::string & name)
	{
		for each (auto var in variables)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
		return Variable();
	}


	std::string Variable::getStringValue()
	{
		return value;
	}


	int Variable::getIntValue()
	{
		return atoi(value.data());
	}
}