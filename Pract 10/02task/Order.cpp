#include "Order.h"
#pragma warning (disable : 4996)
#include <utility>
#include <cstring>
#include <stdexcept>

void Order::freeDynamic()
{
	delete[] _list;
	_list = nullptr;
	_count = 0;

}

void Order::copyDynamic(const Order& other)
{
	_count = other._count;
	_list = new String[_count];
	for (int i = 0; i < _count; ++i)
	{
		_list[i] = other._list[i];
	}
}

void Order::moveFrom(Order&& other)
{
	_name = std::move(other._name);
	_list = other._list;
	_count = other._count;

	other._list = nullptr;
	other._count = 0;
}

Order::Order()
	:_name(""), _list(nullptr), _count(0)
{}

Order::Order(const String& name, const String* list, unsigned int count)
	:_name(name), _list(nullptr), _count(count)
{
	setProductsList(list, count);
}

Order::Order(const Order& other)
	:_name(other._name), _list(nullptr), _count(0)
{
	copyDynamic(other);
}

Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{
		freeDynamic();
		_name = other._name;
		copyDynamic(other);
	}
	return *this;
}

Order::Order(Order&& other) noexcept
{
	moveFrom(std::move(other));
}
Order& Order::operator=(Order&& other) noexcept
{
	if (this != &other)
	{
		freeDynamic();
		moveFrom(std::move(other));
	}
	return *this;
}

Order::~Order()
{
	freeDynamic();
}

//setters
void Order::setProductsList(const String* list, unsigned int count)
{
	freeDynamic();
	_count = count;
	_list = new String[count];
	for (unsigned int i = 0; i < _count; ++i)
	{
		_list[i] = list[i];
	}
}

//getters
const String& Order::getName() const
{
	return _name;
}
const String* Order::getProductsList() const
{
	return _list;
}
unsigned int Order::getCountProducts() const
{
	return _count;
}

//additional

int Order::countDeliveryTime() const
{
	int time = _count;
	for (unsigned int i = 0; i < _count; ++i) {
		time += _list[i].length();
	}
	return time;
}

void Order::addProduct(const char* product)
{
	String* newList = new String[_count + 1];
	for (unsigned int i = 0; i < _count; ++i)
	{
		newList[i] = _list[i];
	}
	newList[_count] = String(product);
	delete[] _list;
	_list = newList;
	++_count;
}

