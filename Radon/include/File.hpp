// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <string>
#include <map>

namespace radon
{
	class Section;

	class File
	{
	public:

		File(const std::string & path);

		Section getSection(const std::string & name);

		void addSection(Section & category);

		void saveToFile();

	private:
		std::map<std::string, Section> sections;
		std::string path;
	};
}