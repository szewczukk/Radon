// Copyright Dmitro bjornus Szewczuk 2017

#include "../include/Radon.hpp"

#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>

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
				buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
				if (buffer[0] == ';') continue;
				if (buffer[0] == '[')
				{
					nameOfCurrent = buffer.substr(buffer.find("[") + 1, buffer.find("]") - 1);
					sections[nameOfCurrent] = Section(nameOfCurrent);
				}
				else
				{
					int equalsPosition = buffer.find('=');

					std::string nameOfElement = buffer.substr(0, equalsPosition);
					std::string valueOfElement = buffer.substr(equalsPosition + 1, buffer.size());

					sections[nameOfCurrent].keys[nameOfElement] = Key(nameOfElement, valueOfElement);
				}
			}
		}
	}


	Section File::getSection(const std::string & name)
	{
		for each (auto var in sections)
		{
			if (var.first == name)
			{
				return var.second;
			}
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
}