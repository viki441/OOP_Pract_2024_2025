#pragma once
#include "Order.h"

namespace Constants
{
	const int NAME_SIZE = 25;
}

class Restaurant
{
private:
	char _name[Constants::NAME_SIZE + 1];
	String* _list;
	unsigned int _count;
	Order* _orders;
	unsigned int _receipts;

	void freeDynamic();
	void copyDynamic(const Restaurant& other);
	void moveFrom(Restaurant&& other);

public:
	Restaurant(); 
	Restaurant(const String& name);
	Restaurant(const char* name, const String* list, unsigned int count, Order* orders, unsigned int receipts);
	Restaurant(const Restaurant& other);
	Restaurant& operator=(const Restaurant& other);

	Restaurant(Restaurant&& other) noexcept;
	Restaurant& operator=(Restaurant&& other) noexcept;

	~Restaurant();

	//setters
	void setName(const char* name);
	void setProductsList(const String* list, unsigned int count);
	void setOrders(const Order* orders, unsigned int receipts);
	
	//getters
	const char* getName() const;
	const String* getList() const;
	const unsigned int getCount() const;
	const Order* getOrders() const;
	const unsigned int getReceipts() const;


	//additional 
	
	void addProduct(const char* product);
	void addReceipt(const Order& orders);
};
