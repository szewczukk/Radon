// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <assert.h>

namespace radon
{
	class Section;
	class Key;
	class File;

	class Named
	{
	public:

		Named()
		{
			setName("You need to set name!");
		}


		Named(const std::string & name)
		{
			setName(name);
		}


		void setName(const std::string & name)
		{
			this->name = name;
		}


		std::string getName()
		{
			return name;
		}

	protected:
		std::string name;
	};

	class File
	{
	public:

		File(const std::string & path, bool reading = true)
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
							sections.push_back(std::unique_ptr<Section>(new Section(nameOfCurrent)));
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

		std::unique_ptr<Section> getSection(const std::string & name)
		{
			for (auto & section : sections)
			{
				if (section->getName() == name)
				{
					return std::make_unique<Section>(*section);
				}
			}

			assert(1);
		}

		void addSection(Section & category)
		{
			sections.push_back(std::make_unique<Section>(category));
		}

		void saveToFile()
		{
			std::ofstream file(path.data(), std::ios::out | std::ios::trunc);

			for (auto & section : sections)
			{
				file << "[" << section->getName() << "] \n";
				for (auto & key : section->keys)
				{
					file << key.getName() << "=" << key.getStringValue() << "\n";
				}
			}
			file.close();
		}

	private:
		std::vector<std::unique_ptr<Section>> sections;
		std::string path;
	};

	class Key
		: public Named
	{
	public:

		Key()
			: Named()
		{
		}


		Key(const std::string & name, const std::string & value)
			: Named(name), value(value)
		{
		}


		Key(const std::string & name, const float & value)
			: Named(name), value(std::to_string(value))
		{
		}


		std::string getStringValue()
		{
			return value;
		}


		float getFloatValue()
		{
			return (float)(atof(value.data()));
		}


		void setValue(float & value)
		{
			this->value = std::to_string(value);
		}


		void setValue(std::string & value)
		{
			this->value = value;
		}

	private:
		std::string value;

		friend class File;
	};

	class Section
		: public Named
	{
	public:

		Section()
			: Named()
		{
		}


		Section(const std::string & name)
			: Named(name)
		{
		}


		Key getKey(const std::string & name)
		{
			for each (auto var in keys)
			{
				if (var.getName() == name)
					return var;
			}

			assert(1);
		}


		void addKey(Key & variable)
		{
			keys.push_back(variable);
		}

	private:
		std::vector<Key> keys;

		friend class File;
	};
}