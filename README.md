# Radon
Simple parser for INI files

## Installation
1. Clone repo
	
	$ git clone https://github.com/bjornus/Radon

2. Open Radon project, compile them in Release mode
3. Attach to project

## Getting value from INI file
### Long version
```cpp
radon::File file("File.ini");

std::shared_ptr<Section> section = file.getSection("section");

std::string value = section->getKey("key").getStringValue();
```
### Short version
```cpp
radon::File file("file.ini");

std::string value = file.getSection("section")->getKey("key").getStringValue();
```

## Creating INI files
```cpp
radon::File file("file.ini");

file.addSection(new Section("section"));
file.getSection("section")->addKey("key");
file.getSection("section")->getKey("key")->setValue("Value");

file.saveToFile();
```