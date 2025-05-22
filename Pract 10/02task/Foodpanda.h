#pragma once
#include "Restaurant.h"

class Foodpanda 
{
private:
	Restaurant* _restaurants;
	unsigned int _count;

	void freeDynamic();
	void copyDynamic(const Foodpanda& other);
	void moveFrom(Foodpanda&& other);

public:
	Foodpanda(Restaurant* restaurants, unsigned int count);
	Foodpanda(const Foodpanda& other);
	Foodpanda& operator=(const Foodpanda& other);
	Foodpanda(Foodpanda&& other) noexcept;
	Foodpanda& operator=(Foodpanda&& other) noexcept;
	~Foodpanda();

	//setters
	void setRestaurants(Restaurant* restaurants,const unsigned int count);

	//getters
	const Restaurant* getRestaurants() const;

	//additional
	void addNewProductInRestaurant(const char* restName, const char* product);
	Restaurant* findRestaurant(const char* restName);


	void addNewRestaurant(const Restaurant& rest);

	//here search for restaurant's name and then call the func in rest
	void addOrderToRestaurant(const char* restName, const Order& order);
};

