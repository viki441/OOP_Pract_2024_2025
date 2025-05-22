#include "Foodpanda.h"

void Foodpanda::freeDynamic()
{
	delete[] _restaurants;
	_restaurants = nullptr;
	_count = 0;
}

void Foodpanda::copyDynamic(const Foodpanda& other)
{
	delete[] _restaurants;
	_count = other._count;

	_restaurants = new Restaurant[_count];
	for (unsigned int i = 0; i < _count; ++i)
	{
		_restaurants[i] = other._restaurants[i];
	}
}

void Foodpanda::moveFrom(Foodpanda&& other)
{
	_restaurants = std::move(other._restaurants);
	_count = other._count;

	other._restaurants = nullptr;
	other._count = 0;
}

Foodpanda::Foodpanda(Restaurant* restaurants, unsigned int count)
	:_count(count)
{
	setRestaurants(restaurants, count);
}
Foodpanda::Foodpanda(const Foodpanda& other)
{
	_count = other._count;
	copyDynamic(other);
}

Foodpanda& Foodpanda::operator=(const Foodpanda& other)
{
	if (this != &other)
	{
		_count = other._count;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Foodpanda::Foodpanda(Foodpanda&& other) noexcept
{
	moveFrom(std::move(other));
}
Foodpanda& Foodpanda::operator=(Foodpanda&& other) noexcept
{
	if (this != &other)
	{
		freeDynamic();
		moveFrom(std::move(other));
	}
	return *this;
}

Foodpanda::~Foodpanda()
{
	freeDynamic();
}

//setters
void Foodpanda::setRestaurants(Restaurant* restaurants, const unsigned int count)
{
	delete[] _restaurants;
	_restaurants = new Restaurant[count];
	for (unsigned int i = 0; i < count; ++i)
	{
		_restaurants[i] = restaurants[i];
	}
	_count = count;
}

//getters
const Restaurant* Foodpanda::getRestaurants() const
{
	return _restaurants;
}

//additional

Restaurant* Foodpanda::findRestaurant(const char* restName)
{
	for (unsigned int i = 0; i < _count; ++i)
	{
		if (String(restName) == _restaurants[i].getName())
		{
			return &_restaurants[i];
		}
	}
	return nullptr;
}
void Foodpanda::addNewProductInRestaurant(const char* restName, const char* product)
{
	Restaurant* rest = findRestaurant(restName);

	if (!rest)
	{
		std::cout << "No such restaurant. Skipping.\n";
		return;
	}
	rest->addProduct(product);
}

void Foodpanda::addNewRestaurant(const Restaurant& rest)
{
	Restaurant* newRestaurants = new Restaurant[_count + 1];
	for (unsigned int i = 0; i < _count; ++i)
	{
		newRestaurants[i] = _restaurants[i];
	}
	newRestaurants[_count] = rest;
	delete[] _restaurants;
	_restaurants = newRestaurants;
	++_count;
}

void Foodpanda::addOrderToRestaurant(const char* restName, const Order& order)
{
	Restaurant* rest = findRestaurant(restName);

	if (!rest)
	{
		std::cout << "No such restaurant to put order in. Skipping.\n";
		return;
	}
	rest->addReceipt(order);
}
