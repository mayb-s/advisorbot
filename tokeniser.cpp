#include "tokeniser.h"


//parsing string
//Worksheet on tokenise Week 5
std::vector<std::string> tokeniser::tokenise(std::string command, char separator)
{
	

	std::vector<std::string> tokens;
	signed int start, end;
	std::string token;
	start = command.find_first_not_of(separator, 0);
	do {
		end = command.find_first_of(separator, start);

		//added condition for user commands
		//processes all tokens even eith double spacing

		if (separator == ' ')
		{
			if (end < command.size()|| end==start)
			{
				start = command.find_first_not_of(separator, start);
				end = start;
				end = command.find_first_of(separator, start);
			}

		}

		if (start == command.length() || start == end) break;
		if (end >= 0) token = command.substr(start, end - start);
		else token = command.substr(start, command.length() - start);
		tokens.push_back(token);
		start = end + 1;
	} while (end > 0);

	return tokens;
	
}