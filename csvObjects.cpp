#include "csvObjects.h"

//functions from ObjectBookEntry in merkelrex

//data types for csv file
csvObjects::csvObjects(double _price,
	double _amount,
	std::string _timestamp,
	std::string _product,
	ObjectType _type)

	: price(_price),
	amount(_amount),
	timestamp(_timestamp),
	product(_product),
	type(_type)

{

}
//turns data type strings into Object Type
ObjectType csvObjects::stringToObjectType(const std::string& s)
{
	if (s == "ask")
	{
		return ObjectType::ask;
	}
	if (s == "bid")
	{
		return ObjectType::bid;
	}
	return ObjectType::unknown;
}

