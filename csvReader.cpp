#include "csvReader.h"

//Code from worksheet week 6 about reading file using tokeniser
//functions from CSVReader.cpp in merkelrex
//turning tokens into data types

csvReader::csvReader()
{
	
}

std::vector <csvObjects> csvReader::readFile(std::string csvFilename)
{
	std::vector<csvObjects> entries;

	std::ifstream csvFile{ csvFilename };
	std::string line;
	if (csvFile.is_open())
	{

		std::cout << "Opened file " << csvFilename << std::endl;
		
		std::string line;
		while (getline(csvFile, line))
		{
			
			std::vector<std::string> tokens = tokeniser::tokenise(line, ',');
			
			if (tokens.size() != 5) continue;
			try
			{
				
				csvObjects obe = stringsToObjects(tokeniser::tokenise(line, ','));
				entries.push_back(obe);
			}
			catch (const std::exception& e)
			{
				
				continue;
			}

		}

	}
	else
	{
		std::cout << "Problem opening file " << csvFilename << std::endl;
	}

	return entries;
}

csvObjects csvReader::stringsToObjects(std::vector<std::string> tokens)
{
	
	double price, amount;
	if (tokens.size() != 5) // bad
	{
		throw std::exception{};
	}
	// we have 5 tokens
	try {
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);
	}
	catch (const std::exception& e) {
		std::cout << "Bad float! " << tokens[3] << std::endl;
		std::cout << "Bad float! " << tokens[4] << std::endl;
		throw;
	}
	
	csvObjects obe{ price,
					amount,
					tokens[0],
					tokens[1],
					csvObjects::stringToObjectType(tokens[2]) };

	return obe;
}

csvObjects csvReader::stringsToObjects(std::string priceString,
	std::string amountString,
	std::string timestamp,
	std::string product,
	ObjectType type)
{
	double price, amount;
	try {
		price = std::stod(priceString);
		amount = std::stod(amountString);
	}
	catch (const std::exception& e) {
		std::cout << "csvReader::stringsToObjects Bad float! " << priceString << std::endl;
		std::cout << "csvReader::stringsToObjects Bad float! " << amountString << std::endl;
		throw; // throw up to the calling function
	}
	csvObjects obe{ price,
					amount,
					timestamp,
					product,
					type};

	return obe;
}