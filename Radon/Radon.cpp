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
		std::ifstream stream(path);

		if (stream.is_open())
		{
			std::string buffer;
			std::string nameOfCurrent = "";

			while (std::getline(stream, buffer))
			{
				if (buffer[0] == ';') continue;
				if (buffer[0] == '[')
				{
					nameOfCurrent = buffer.substr(1, buffer.size() - 2);
				}
				else
				{
					int equalsPosition = buffer.find("=");

					std::string nameOfElement = buffer.substr(0, equalsPosition - 1);
					std::string valueOfElement = buffer.substr(equalsPosition + 1, buffer.size());

					categories[nameOfCurrent].variables[nameOfElement].value = valueOfElement;
				}
			}
		}
	}


	Category File::getCategory(const std::string & name)
	{
		for each (auto var in categories)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
	}


	void File::addCategory(Category & category)
	{
		categories[category.name] = category;
	}


	void File::saveToFile()
	{
		std::ofstream file;
		file.open(path);

		for each (auto category in categories)
		{
			file << "[" << category.first << "]";
			for each(auto var in category.second.variables)
			{
				file << var.first << "=" << var.second.getStringValue();
			}
		}
		file.close();
	}


	Variable Category::getVariable(const std::string & name)
	{
		for each (auto var in variables)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
	}


	void Category::addVariable(Variable & variable)
	{
		variables[variable.getName()] = variable;
	}


	Variable::Variable()
		: Named()
	{
	}

	Variable::Variable(const std::string & name, const std::string & value)
		: Named(name), value(value)
	{
	}


	Variable::Variable(const std::string & name, const float & value)
		: Named(name), value(std::to_string(value))
	{
	}


	std::string Variable::getStringValue()
	{
		return value;
	}

	Category::Category()
		: Named()
	{
	}

	Category::Category(const std::string & name)
		: Named(name)
	{
	}


	float Variable::getFloatValue()
	{
		return (float)(atof(value.data()));
	}


	void Variable::setValue(float & value)
	{
		this->value = std::to_string(value);
	}


	void Variable::setValue(std::string & value)
	{
		this->value = value;
	}


	Named::Named()
	{
		setName("You need to set name!");
	}

	Named::Named(const std::string & name)
	{
		setName(name);
	}


	void Named::setName(const std::string & name)
	{
		this->name = name;
	}


	std::string Named::getName()
	{
		return name;
	}
}