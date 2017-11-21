# Radon
Simple parser for INI files

## Installation
1. Clone repo
	
	$ git clone htpps://https://github.com/bjornus/Radon

2. Open Radon project, compile them in Release mode
3. Attach to project

## Getting value from INI file
### Long version
```cpp
	//Load file
	radon::File file("File.ini");

	//Get Section with traditional or modern pointer
	Section * section = file.getSection("section");

	//Or

	std::shared_ptr<Section> section = file.getSection("section");

	//Get value of Key in float or string
	float value = section->getKey("key").getFloatValue();

	//Or

	std::string value = section->getKey("key").getStringValue();
```