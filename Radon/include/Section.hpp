// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <string>
#include <map>

#include "Named.hpp"

namespace radon
{
	class Key;

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
}