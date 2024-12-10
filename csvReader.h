#pragma once
#include <fstream>
#include "tokeniser.h"
#include "csvObjects.h"

//functions from CSVReader.cpp in merkelrex
//turning tokens into data types

class csvReader
{
public:

	csvReader();

	static std::vector <csvObjects> readFile(std::string csvFilename);

	static csvObjects stringsToObjects(std::string price,
		std::string amount,
		std::string timestamp,
		std::string product,
		ObjectType ObjectType);



private:
	
	static csvObjects stringsToObjects(std::vector<std::string> strings);


};