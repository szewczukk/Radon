// Copyright Dmitro bjornus Szewczuk 2017

#include "../include/Radon.hpp"

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <assert.h>

namespace radon
{
	File::File(const std::string & path, bool reading)
	{
		this->path = path;
		if (reading)
		{
			std::ifstream stream(path);

			if (stream.is_open())
			{
				std::string buffer;
				std::string nameOfCurrent = "";

				while (std::getline(stream, buffer))
				{
					buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
					if (buffer[0] == ';' || buffer[0] == '#') continue;
					if (buffer[0] == '[')
					{
						nameOfCurrent = buffer.substr(buffer.find("[") + 1, buffer.find("]") - 1);
						sections.push_back(std::shared_ptr<Section>(new Section(nameOfCurrent)));
					}
					else
					{
						int equalsPosition = buffer.find('=');

						std::string nameOfElement = buffer.substr(0, equalsPosition);
						std::string valueOfElement = buffer.substr(equalsPosition + 1, buffer.size());

						sections.back()->addKey(Key(nameOfElement, valueOfElement));
					}
				}
			}
		}
	}


	std::shared_ptr<Section> File::getSection(const std::string & name)
	{
		for each (auto var in sections)
		{
			if (var->getName() == name)
			{
				return var;
			}
		}

		assert(1);
	}


	void File::addSection(Section * category)
	{
		sections.push_back(std::make_shared<Section>(*category));
	}


	void File::saveToFile()
	{
		std::ofstream file(path.data(), std::ios::out | std::ios::trunc);

		for each (auto section in sections)
		{
			file << "[" << section->getName() << "] \n";
			for each(auto var in section->keys)
			{
				file << var.getName() << "=" << var.getStringValue() << "\n";
			}
		}
		file.close();
	}
}