#pragma once
#include "String.h"

class Order
{
private:

	String _name;
	String* _list;
	unsigned int _count;
	
	void freeDynamic();
	void copyDynamic(const Order& other);
	void moveFrom(Order&& other);

public:
	Order();
	Order(const String& name,const String* list, unsigned int count);
	Order(const Order& other);
	Order& operator=(const Order& other);
	Order(Order&& other) noexcept;
	Order& operator=(Order&& other) noexcept;
	~Order();

	//getters
	const String& getName() const;
	const String* getProductsList() const;
	unsigned int getCountProducts() const;

	//setters
	void setName(const String& name); //wont really use..validation is elsewhere anyway
	void setProductsList(const String* list, unsigned int count);

	//additional
	void setList(const String* list, unsigned int count);
	void addProduct(const char* product);
	int countDeliveryTime() const;

};
