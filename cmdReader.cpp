#include "cmdReader.h"
#include "getData.h"

void cmdReader::init()
{
	//greeting
	std::cout << "Time: ";
	currentTime = GetData.getEarliestTime();
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~$~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Welcome to Advisorbot" << std::endl;
	std::cout << "Advisorbot is a command line program that can" << std::endl;
	std::cout << "carry out various tasks to help a cryptocurrency" << std::endl;
	std::cout << "investor analyse the data available on an exchange."<<std::endl;
	std::cout << "To start type, help " << std::endl;

	while (true)
	{
		//spacer and command line
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~$~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "user> ";
		
		//calls user input and input check
		input=userInput();
		inputCheck(input);
		

	}
	
}

std::string cmdReader::userInput()
{
	std::getline(std::cin, input);
	return input;
}

//checks input to send to command functions
void cmdReader::inputCheck(std::string input)
{
	//tokenise with spaces in between 
	tokens = tokeniser::tokenise(input, ' ');

	//std::cout << "tokens size is " << tokens.size() << std::endl;

	//if user enters empty command or just spaces
	//then invalid input is called 
	if (tokens.size() != 0)
	{
		
		if (tokens.size() == 1)
		{
			//help, time, step, prod
			oneCommand(input);
		}

		if (tokens.size() == 2)
		{
			//help<cmd>, 
			twoCommands(input);
		}
		//checks size and first token
		if (tokens.size() == 3 && (tokens[0]=="max"|| tokens[0] == "min") )
		{
			MaxorMin(input);
		}

		if (tokens[0] == "avg" && tokens.size() == 4)
		{
			avgCommand(input);
		}

		if (tokens[0] == "predict" && tokens.size() == 4)
		{
			predictCommand(input);
		}

		if ((tokens[0] == "buy" || tokens[0] == "sell") && tokens.size() == 3)
		{
			BuyorSell(input);
		}
		//no commands have a size greater than 4
		//so any input larger than 4 is invalid
		if (tokens.size() > 4)
		{
			invalidInput();
		}


	}
	else
	{ invalidInput(); }


}

//sends message to user in case of error
void cmdReader::invalidInput()
{
	std::cout << "advisorbot> ";
	std::cout << "Invalid input! " << std::endl;
	std::cout << "Please enter a complete command or type, help" << std::endl;
	
}


void cmdReader::oneCommand(std::string input)
{
	

	if (tokens[0] == "help" || tokens[0] == "prod" || tokens[0] == "time" || tokens[0] == "step")
	{
		
		std::cout << "advisorbot> ";

		if (tokens[0] == "help")
		{
			//help message
			std::cout << "The available commands are help, help <cmd>,"<<std::endl;
			std::cout << "avg, time, prod, min, max, predict, step" << std::endl;
			std::cout << "To learn how to use each command type, help <command>" << std::endl;
			std::cout << "For example, user> help prod" << std::endl;

		}
		if (tokens[0] == "prod")
		{
			//iterates over all products and prints them out
			//calls getProducts 
			for (const std::string& p : GetData.getProducts())
			{
				std::cout << p << std::endl;
				
			}
			
		}

		if (tokens[0] == "time")
		{
			//calls earliest time and prints out
			std::cout << currentTime << std::endl;;

		}

		if (tokens[0] == "step")
		{
			//call nextTime for next time step
			std::cout << "now at "<< GetData.nextTime(currentTime) <<std::endl;
			
		}
	}
	else { invalidInput(); 
		
	}

}

    
void cmdReader::twoCommands(std::string input)
{
	//help<cmd> command for user reference
	//all outputs are strings that don't change

	if (tokens[0]=="help" && (tokens[1] == "avg" || tokens[1] == "prod" || tokens[1] == "min" ||
		tokens[1] == "max" || tokens[1] == "predict" || tokens[1] == "time" || 
		tokens[1] == "step"|| tokens[1] == "buy"|| tokens[1] == "sell"))
	{
		std::cout << "advisorbot> ";

		if (tokens[1] == "avg")
		{
			std::cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid" << std::endl;;
			std::cout << "over last 10 time steps" << std::endl;
		}
		if (tokens[1] == "prod")
		{
			std::cout << " prod ->  product is ETH/BTC and DOGE/BTC" << std::endl;
		}
		if (tokens[1] == "min")
		{
			std::cout << "min ETH/BTC ask -> the minimum ask for ETH/BTC" << std::endl;
		}
		if (tokens[1] == "max")
		{
			std::cout << "max ETH/BTC ask -> the maximum ask for ETH/BTC" << std::endl;
		}
		if (tokens[1] == "predict")
		{
			std::cout << "predict max ETH/BTC bid -> The average ETH/BTC ask price" << std::endl;
		}
		if (tokens[1] == "time")
		{
			std::cout << "time -> current timeframe, e.g., 2020/03/17 17:01:24" << std::endl;
		}
		if (tokens[1] == "step")
		{
			std::cout << "step -> the next timeframe, e.g., 2020/03/17 17:01:30" << std::endl;
		}
		if (tokens[1] == "sell")
		{
			std::cout << "sell ETH/BTC 10 -> Sell! ETH/BTC price change is 7%" << std::endl;
			std::cout << "over the last 10 timesteps" << std::endl;
		}
		if (tokens[1] == "buy")
		{
			std::cout << "buy ETH/BTC 10 -> Buy! ETH/BTC price change is 7%" << std::endl;
			std::cout << "over the last 10 timesteps" << std::endl;
		}
	}else {invalidInput(); }

}


void cmdReader::MaxorMin(std::string input)
{
		//calls getProducts and iterates over all
		for (const std::string& p : GetData.getProducts())
		{
			//checks if token is product
			if (tokens[1] == p)
			{
				//calls getOrders and puts into new vector for later use
				std::vector<csvObjects> entries_bid = GetData.getOrders(ObjectType::bid, tokens[1], currentTime);
				std::vector<csvObjects> entries_ask = GetData.getOrders(ObjectType::ask, tokens[1], currentTime);

				if (tokens[0] == "max" && (tokens[2] == "bid" || tokens[2] == "ask"))
				{
					std::cout << "advisorbot> ";

					//bid or ask outputs
					//inputs new entries vector to get max price

					if (tokens[2] == "bid")
					{
						std::cout << "The max bid for " << tokens[1] << " is ";
						std::cout << getData::getMaxPrice(entries_bid) << std::endl;

					}
					else if (tokens[2] == "ask")
					{
						std::cout << "The max ask for " << tokens[1] << " is ";
						std::cout << getData::getMaxPrice(entries_ask) << std::endl;
					}

					break;

				}

				if (tokens[0] == "min" && (tokens[2] == "bid" || tokens[2] == "ask"))
				{
					std::cout << "advisorbot> ";

					if (tokens[2] == "bid")
					{
						std::cout << "The min bid for " << tokens[1] << " is ";
						std::cout << getData::getMaxPrice(entries_bid) << std::endl;

					}
					else if (tokens[2] == "ask")
					{
						std::cout << "The min ask for " << tokens[1] << " is ";
						std::cout << getData::getMaxPrice(entries_ask) << std::endl;
					}

				}
				else { invalidInput(); }
				break;
			}
			else { continue; }
		}
	
}

void cmdReader::avgCommand(std::string input)
{

	for (const std::string& p : GetData.getProducts())
	{
		if (tokens[1] == p)
		{
			
			std::vector<csvObjects> entries_bid = GetData.getOrders(ObjectType::bid,
				tokens[1], currentTime);
			std::vector<csvObjects> entries_ask = GetData.getOrders(ObjectType::ask,
				tokens[1], currentTime);
			std::vector <csvObjects> AllBidOrders;
			std::vector <csvObjects> AllAskOrders;

			//starts counter to find how many integer characters there are in the token
			int counter = 0;
			for (int i = 0; i < tokens[3].length(); i++)
			{
				//2nd for loop, to figure out if token is integer 
				for (int i = 0; i < tokens[3].length(); i++)
				{
					if (isdigit(tokens[3][i]) != 0)
					{	//is digit
						//tokens[3][i]= 1,2,...;
						counter = i + 1;

					}
					else { break; }
				}
				
				//0 = isdigit means it's not an integer

				if (counter == tokens[3].length() && isdigit(tokens[3][i]) != 0)
				{
					//Comment

					int steps = stoi(tokens[3]);
					for (int i = 0; i < steps; i++)
					{
						//pushes all timestamps into new vector for later
						currentTime = GetData.nextTime(currentTime);
						AllBidOrders.push_back(entries_bid[i]);
						AllAskOrders.push_back(entries_ask[i]);

					}

					if (steps < 51)
					{

						if (tokens[0] == "avg" && (tokens[2] == "bid" || tokens[2] == "ask"))
						{
							//outputs

						
								std::cout << "advisorbot> ";


								if (tokens[2] == "bid")
								{
									std::cout << "The average " << tokens[1];
									std::cout << " bid price over the last " << steps;
									std::cout << " timesteps was ";
									std::cout << getData::getAvgPrice(AllBidOrders) << std::endl;

								}
								else if (tokens[2] == "ask")
								{
									std::cout << "The average " << tokens[1];
									std::cout << " ask price over the last " << steps;
									std::cout << " timesteps was ";
									std::cout << getData::getAvgPrice(AllAskOrders) << std::endl;

								}
						
						


						}
						else { invalidInput(); }

						break;

					}
					else { invalidInput(); std::cout << "Use timestamps 50 and below" << std::endl; break; }

				}
				else { invalidInput(); break; }

			}
			
			break;
		
		}
		else { continue;}

	}


}

void cmdReader::predictCommand(std::string input)
{

	if (tokens[1] == "max" || tokens[1] == "min")
	{
		

		for (const std::string& p : GetData.getProducts())
		{
			if (tokens[2] == p)
			{

				if (tokens[3] == "bid" || tokens[3] == "ask")
				{
					std::cout << "advisorbot> ";

					
					currentTime = GetData.nextTime(currentTime);
					std::vector<csvObjects> entries_bid = GetData.getOrders(ObjectType::bid,
						tokens[2], currentTime);
					std::vector<csvObjects> entries_ask = GetData.getOrders(ObjectType::ask,
						tokens[2], currentTime);


					if (tokens[3] == "bid" && tokens[1] == "max")
					{
						std::cout << "The max " << tokens[2];
						std::cout << " bid price over the next ";
						std::cout << " timestep is ";
						std::cout << getData::getMaxPrice(entries_bid) << std::endl;
						//break;
					}
					if (tokens[3] == "ask" && tokens[1] == "max")
					{
						std::cout << "The max " << tokens[2];
						std::cout << " ask price over the next ";
						std::cout << " timestep is ";
						std::cout << getData::getMaxPrice(entries_ask) << std::endl;
					}
					if (tokens[3] == "bid" && tokens[1] == "min")
					{
						std::cout << "The min" << tokens[2];
						std::cout << " bid price over the next ";
						std::cout << " timestep is ";
						std::cout << getData::getMinPrice(entries_bid) << std::endl;
					}
					if (tokens[3] == "ask" && tokens[1] == "min")
					{
						std::cout << "The min " << tokens[2];
						std::cout << " ask price over the next ";
						std::cout << " timestep is ";
						std::cout << getData::getMinPrice(entries_ask) << std::endl;
					}
					break;
				}
				else { invalidInput(); }
				
			}
			else { continue; }

		}

	}
	else { invalidInput(); }

}

void cmdReader::BuyorSell(std::string input)
{

		//user> buy ETH/BTC 10
		//bot> buy, price change -7% over last 10 timesteps      
		//assuming the user already owns the product with starting price
	//std::cout << "called" << std::endl;
	for (const std::string& p : GetData.getProducts())
	{
		if (tokens[1] == p)
		{
			std::vector<csvObjects> entries_bid = GetData.getOrders(ObjectType::bid, 
																	tokens[1], currentTime);
			std::vector<csvObjects> entries_ask = GetData.getOrders(ObjectType::ask, 
																	tokens[1], currentTime);
			std::vector <csvObjects> AllBidOrders;
			std::vector <csvObjects> AllAskOrders;

			

			int counter = 0;
			for (int i = 0; i < tokens[2].length(); i++)
			{
				//Comment

				for (int i = 0; i < tokens[2].length(); i++)
				{
					if (isdigit(tokens[2][i]) != 0)
					{
						//is digit
						counter = i + 1;

					}
					else { invalidInput(); break; }
				}

				if (counter == tokens[2].length() && isdigit(tokens[2][i]) != 0)
				{
					int steps = stoi(tokens[2]);
					for (int i = 0; i < steps; i++)
					{
						currentTime = GetData.nextTime(currentTime);
						AllBidOrders.push_back(entries_bid[i]);
						AllAskOrders.push_back(entries_ask[i]);

					}

					if (steps < 51)
					{
						std::cout << "advisorbot> ";

						if (tokens[0] == "buy")
						{
							//Comment
							if (getData::getPriceChange(AllBidOrders) < -6)
							{
								std::cout << "Buy! price change is ";
								std::cout << getData::getPriceChange(AllBidOrders) << "% ";
								std::cout <<"over the last " << steps <<" timesteps "<<std::endl;

							}
							else
							{
								std::cout << "Hold! price change is ";
								std::cout << getData::getPriceChange(AllBidOrders) << "% ";
								std::cout << "over the last " << steps << " timesteps " << std::endl;
							}
							break;
								
						}

						if (tokens[0] == "sell")
						{

							if (getData::getPriceChange(AllAskOrders) > 6)
							{
								std::cout << "Sell! price change is +";
								std::cout << getData::getPriceChange(AllAskOrders) << "% ";
								std::cout << "over the last " << steps << " timesteps " << std::endl;

							}
							else
							{
								std::cout << "Hold! price change is ";
								std::cout << getData::getPriceChange(AllAskOrders) << "% ";
								std::cout << "over the last " << steps << " timesteps " << std::endl;
							}
							break;


						}break;
						
					}
					else
					{
						invalidInput();
						std::cout << "Use timesteps 50 and lower" << std::endl;
						break;
						
					}
					
				}
				else { invalidInput(); break; }
				
			}
			
		}
		else { continue; }
		
	}
	

}