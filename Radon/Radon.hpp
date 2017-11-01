// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <map>

namespace radon
{
	class File;

	class Variable
	{
	public:

		std::string getStringValue();

		int getIntValue();

	private:
		std::string value;

		friend class File;
	};


	class Category
	{
	public:

		Variable getVariable(const std::string & name);

	private:
		std::map<std::string, Variable> variables;

		friend class File;
	};

	class File
	{
	public:

		File(const std::string & path);

		Category getCategory(const std::string & name);

	private:
		std::map<std::string, Category> categories;
	};
}