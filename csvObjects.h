#pragma once
#include <string>

enum class ObjectType { bid, ask, unknown};

class csvObjects
{
	public:
	
	
		static ObjectType stringToObjectType(const std::string& s);

	
		csvObjects(double _price,
			double _amount,
			std::string _timestamp,
			std::string _product,
			ObjectType _type);

		double price;
		double amount;
		std::string timestamp;
		std::string product;
		ObjectType type;

	//sorting functions, times and prices
		static bool compareTimestamp(const csvObjects& e1, const csvObjects& e2)
		{
			return e1.timestamp < e2.timestamp;
		}
		static bool compareByPriceAsc(csvObjects& e1, csvObjects& e2)
		{
			return e1.price < e2.price;
		}
		static bool compareByPriceDesc(csvObjects& e1, csvObjects& e2)
		{
			return e1.price > e2.price;
		}

	private:


};

