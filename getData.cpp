#include "getData.h"
#include <map>


getData::getData(std::string filename)
{
	orders = csvReader::readFile(filename);

}

//from OrderBook in merkelrex
std::vector<std::string> getData::getProducts()
{
	std::vector<std::string> products;

	std::map<std::string, bool> prodMap;
	for (const csvObjects& e : orders)
	{
		prodMap[e.product] = true;
	}

	for (const auto& e : prodMap)
	{
		products.push_back(e.first);
	}

	return products ;
}
//from OrderBook in merkelrex
std::vector<csvObjects> getData::getOrders(ObjectType type,std::string product,
	std::string timestamp)
{
	std::vector<csvObjects> orders_sub;
	
	for (csvObjects& e : orders)
	{
		if (e.type == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}

	return orders_sub;

}


//new code to compare timestamps to find earliest
std::string getData::getEarliestTime()
{
	//initializer
	std::string earliest = orders[0].timestamp;
	//iterating over orders 
	for (csvObjects& e : orders)
	{
		//comparing times
		if (e.timestamp < earliest)earliest = e.timestamp;
	}
	//prints out time
	std::cout << earliest << std::endl;
	return earliest;
}


//from OrderBook in merkelrex
std::string getData::nextTime(const std::string& timestamp)
{
	//initializer
	std::string next_time = timestamp;
	
	for (csvObjects& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_time = e.timestamp;
			break;
		}else { continue; }
				
	}
	return next_time;
}

//from OrderBook in merkelrex
double getData::getMinPrice(std::vector<csvObjects>& orders)
{
	//initializer
	double min = orders[0].price;

	for (csvObjects& e : orders)
	{
		if (e.price < min)min = e.price;
	}

	return min;

}
//from OrderBook in merkelrex
double getData::getMaxPrice(std::vector<csvObjects>& orders)
{
	//initializer
	double max = orders[0].price;

	for (csvObjects& e : orders)
	{
		if (e.price > max)max = e.price;
	}

	return max;
}

//for avg command
//compares first price to the next, then divides by orders size
double getData::getAvgPrice(std::vector<csvObjects>& orders)
{
	//initializer
	double total = orders[0].price;

	for (csvObjects& e : orders)
	{

		total = total + e.price;

	}
	double avg = total / orders.size();

	return avg;

}


//FOR NEW COMMAND
//finds price change percent
double getData::getPriceChange(std::vector<csvObjects>& orders)
{
	//initializer
	double original_price = orders[0].price;
	double change = 0;

	for (csvObjects& e : orders)
	{
		//change over timesteps
		change = ((e.price-original_price)/original_price)*100;
		
		//std::cout << change << std::endl;

	}
	
	return change;

}
