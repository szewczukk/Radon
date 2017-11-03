// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <map>

namespace radon
{
	class File;
	class Variable;
	class Category;

	class Named
	{
	public:

		Named();

		Named(const std::string & name);

		void setName(const std::string & name);

		std::string getName();

	protected:
		std::string name;
	};

	class Variable
		: public Named
	{
	public:

		Variable();

		Variable(const std::string & name, const std::string & value);
		
		Variable(const std::string & name, const float & value);

		std::string getStringValue();

		float getFloatValue();

		void setValue(float & value);

		void setValue(std::string & value);

	private:
		std::string value;

		friend class File;
	};


	class Category
		: public Named
	{
	public:

		Category();

		Category(const std::string & name);

		Variable getVariable(const std::string & name);

		void addVariable(Variable & variable);

	private:
		std::map<std::string, Variable> variables;

		friend class File;
	};

	class File
	{
	public:

		File(const std::string & path);

		Category getCategory(const std::string & name);

		void addCategory(Category & category);

		void saveToFile();

	private:
		std::map<std::string, Category> categories;
		std::string path;
	};
}