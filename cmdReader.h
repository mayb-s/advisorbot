#pragma once
#include "csvObjects.h"
#include "getData.h"

class cmdReader
{
	
public:

		cmdReader()=default;
		void init();

	private:

		//Functions and strings for processing commands
	
		std::string userInput();

		void oneCommand(std::string input);

		void twoCommands(std::string input);

		void MaxorMin(std::string input);

		void avgCommand(std::string input);

		void predictCommand(std::string input);
		
		void inputCheck(std::string input);

		void invalidInput();

		//time
		std::string currentTime;

		//input
		std::string input;

		//tokens
		std::vector<std::string> tokens;

		//NEW COMMAND
		//command that tells me when to buy a certain product by looking at percent increase
		//user> sell ETH/BTC 10
		//bot> Hold, price change is 0%
		void BuyorSell(std::string input);

		//actual data, large data file
		//getData GetData{"RealData.csv"};

		//for testing, small data file
		getData GetData{ "TestData.csv" };


};