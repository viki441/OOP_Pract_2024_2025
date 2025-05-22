#pragma warning (disable : 4996)
#include "Restaurant.h"
#include <cstring>
#include <stdexcept>
#include <utility>

void Restaurant::freeDynamic() 
{
	_name[0] = '\0';
	delete[] _list;
	_list = nullptr;
	_count = 0;
	_receipts = 0;
}

void Restaurant::copyDynamic(const Restaurant& other)
{
	_list = nullptr;
	_orders = nullptr;
	delete[] _list;
	delete[] _orders;

	std::strcpy(_name, other._name);
	_name[Constants::NAME_SIZE] = '\0';

	_count = other._count;
	_receipts = other._receipts;

	_list = new String[_count];
	_orders = new Order[_receipts];
	for (unsigned int i = 0; i < _count; ++i)
	{
		_list[i] = other._list[i];
	}
	for (unsigned int i = 0; i < _receipts; ++i)
	{
		_orders[i] = other._orders[i];
	}
}

void Restaurant::moveFrom(Restaurant&& other)
{
	_list = other._list;
	_orders = other._orders;
	std::strcpy(_name, other._name);
	_count = other._count;
	_receipts = other._receipts;

	other._count = 0;
	other._receipts = 0;
	other._list = nullptr;
	other._orders = nullptr;
	// Zero out all bytes
	std::memset(other._name, 0, sizeof(other._name)); 


}
Restaurant::Restaurant()
	:_name("none"), _list(nullptr), _count(0), _orders(nullptr), _receipts(0)
{}

Restaurant::Restaurant(const char* name, const String* list, unsigned int count, Order* orders, unsigned int receipts)
	:_count(_count), _receipts(receipts), _orders(nullptr), _list(nullptr)
{
	setName(name);
	setProductsList(list, count);
	setOrders(orders, receipts);
}
Restaurant::Restaurant(const Restaurant& other)
{
	_count = other._count;
	_receipts = other._receipts;
	copyDynamic(other);
}
Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		_count = other._count;
		_receipts = other._receipts;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}
Restaurant::Restaurant(Restaurant&& other) noexcept
{
	moveFrom(std::move(other));
}

Restaurant& Restaurant::operator=(Restaurant&& other) noexcept
{
	if (this != &other)
	{
		freeDynamic();
		moveFrom(std::move(other));
	}
	return *this;

}
Restaurant::~Restaurant()
{
	freeDynamic();
}

//setters
void Restaurant::setName(const char* name)
{
	if (!name)
	{
		throw std::invalid_argument("Null name\n");
	}

	if (std::strlen(name) > Constants::NAME_SIZE)
	{
		throw std::invalid_argument("Name is too long.\n");
	}

	std::strcpy(_name, name);
	_name[Constants::NAME_SIZE - 1] = '\n';
}

void Restaurant::setProductsList(const String* list, unsigned int count)
{
	if (!list || count == 0)
	{
		std::cout << "Invalid product list. skipping \n";
		return;
	}
	delete[] _list;
	_list = new String[count];
	for (int i = 0; i < count; ++i)
	{
		_list[i] = list[i];
	}
}

void Restaurant::setOrders(const Order* orders, unsigned int receipts)
{
	
	if (!orders || receipts == 0)
	{
		std::cout << "Invalid receipt list. skipping \n";
		return;
	}
	delete[] _orders;
	_orders = new Order[receipts];
	for (int i = 0; i < receipts; ++i)
	{
		_orders[i] = orders[i];
	}
}

//getters
const char* Restaurant::getName() const
{
	return _name;
}
const String* Restaurant::getList() const
{
	return _list;
}
const unsigned int Restaurant::getCount() const
{
	return _count;
}
const Order* Restaurant::getOrders() const
{
	return _orders;
}
const unsigned int Restaurant::getReceipts() const
{
	return _receipts;
}

//additional
void Restaurant::addProduct(const char* product) 
{
	String* newList = new String[_count + 1];
	for (unsigned int i = 0; i < _count; ++i)
	{
		newList[i] = _list[i];
	}
	newList[_count] = product;

	delete[] _list;
	_list = newList;
	++_count;
} 


void Restaurant::addReceipt(const Order& order)
{
	Order* newList = new Order[_receipts + 1];
	for (unsigned int i = 0; i < _receipts; ++i)
	{
		newList[i] = _orders[i];
	}
	newList[_receipts] = order;
	delete[] _orders;
	_orders = newList;
	++_receipts;
}
