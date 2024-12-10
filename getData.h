#pragma once
#include "csvObjects.h"
#include "csvReader.h"
#include <vector>
class getData
{
public:
	/** construct, reading a csv data file */
	getData(std::string filename);

	/** return vector of all know products in the dataset*/
	std::vector<std::string> getProducts();

	/** return vector of Orders according to the sent filters*/
	std::vector<csvObjects> getOrders(ObjectType type, std::string product,
		std::string timestamp);

	//get current timestamp
	std::string getEarliestTime();

	//get next timestamp
	std::string nextTime(const std::string& timestamp);

	//lowest bid or ask in timeframe
	static double getMinPrice(std::vector<csvObjects>& orders);

	//highest bid or ask in timeframe
	static double getMaxPrice(std::vector<csvObjects>& orders);

	//FOR avg command 
	//average bid/ask in timeframe
	static double getAvgPrice(std::vector<csvObjects>& orders);
	
	//FOR NEW COMMAND
	static double getPriceChange(std::vector<csvObjects>& orders);

private:
	std::vector<csvObjects> orders;
};