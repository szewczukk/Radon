// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <map>

namespace radon
{
	class File;
	class Key;
	class Section;

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

	class Key
		: public Named
	{
	public:

		Key();

		Key(const std::string & name, const std::string & value);
		
		Key(const std::string & name, const float & value);

		std::string getStringValue();

		float getFloatValue();

		void setValue(float & value);

		void setValue(std::string & value);

	private:
		std::string value;

		friend class File;
	};


	class Section
		: public Named
	{
	public:

		Section();

		Section(const std::string & name);

		Key getKey(const std::string & name);

		void addKey(Key & variable);

	private:
		std::map<std::string, Key> keys;

		friend class File;
	};

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