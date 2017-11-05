// Copyright Dmitro bjornus Szewczuk 2017

#include "Radon.hpp"

#include <assert.h>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>

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
					nameOfCurrent = buffer.substr(buffer.find("[") + 1, buffer.find("]") - 1);
				}
				else
				{
					int equalsPosition = buffer.find('=');

					std::string nameOfElement = buffer.substr(0, equalsPosition);
					std::string valueOfElement = buffer.substr(equalsPosition + 1, buffer.size());

					sections[nameOfCurrent].keys[nameOfElement].value = valueOfElement;
				}
			}
		}
	}


	Section File::getSection(const std::string & name)
	{
		for each (auto var in sections)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
	}


	void File::addSection(Section & category)
	{
		sections[category.name] = category;
	}


	void File::saveToFile()
	{
		std::ofstream file;
		file.open(path);

		for each (auto category in sections)
		{
			file << "[" << category.first << "]";
			for each(auto var in category.second.keys)
			{
				file << var.first << "=" << var.second.getStringValue();
			}
		}
		file.close();
	}


	Key Section::getKey(const std::string & name)
	{
		for each (auto var in keys)
		{
			if (var.first == name)
				return var.second;
		}

		assert(1);
	}


	void Section::addKey(Key & variable)
	{
		keys[variable.getName()] = variable;
	}


	Key::Key()
		: Named()
	{
	}

	Key::Key(const std::string & name, const std::string & value)
		: Named(name), value(value)
	{
	}


	Key::Key(const std::string & name, const float & value)
		: Named(name), value(std::to_string(value))
	{
	}


	std::string Key::getStringValue()
	{
		return value;
	}

	Section::Section()
		: Named()
	{
	}

	Section::Section(const std::string & name)
		: Named(name)
	{
	}


	float Key::getFloatValue()
	{
		return (float)(atof(value.data()));
	}


	void Key::setValue(float & value)
	{
		this->value = std::to_string(value);
	}


	void Key::setValue(std::string & value)
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