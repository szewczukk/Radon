#include "../include/Radon.hpp"

#include <assert.h>

namespace radon
{
	Section::Section()
		: Named()
	{
	}

	Section::Section(const std::string & name)
		: Named(name)
	{
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

	
}