// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <map>

namespace radon
{
	class Category;
	class File;

	class Named
	{
	public:
		std::string getName() { return name; };

		void setName(const std::string & name) { this->name = name; };
	protected:
		std::string name;
	};

	class Variable 
		: public Named
	{
	public:

		std::string getStringValue();

		int getIntValue();

	private:
		std::string value;

		friend class Category;
		friend class File;
	};


	class Category
		: public Named
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