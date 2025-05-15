#include "StringVector.h"
void StringVector::freeDynamic()
{

	delete[] _data;
	_data = nullptr;
	_size = 0;
	_capacity = 0;
}

void StringVector::copyDynamic(const StringVector& other)
{
	//is my copyDynamic okay?
	_size = other._size;
	_capacity = other._capacity;
	_data = new String[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = other._data[i];
	}

}
StringVector::StringVector()
	:_data(new String[4]), _size(0), _capacity(4)
{}

StringVector::StringVector(String* data, size_t size, size_t capacity)
	:_size(size), _capacity(capacity)
{
	setString(data);

}

StringVector::StringVector(const StringVector& other)
	:_size(other._size), _capacity(other._capacity)
{
	copyDynamic(other);
}
StringVector& StringVector::operator=(const StringVector& other)
{
	if (this != &other)
	{
		freeDynamic();
		copyDynamic(other);

	}
	return *this;
}
StringVector::StringVector(StringVector&& other) noexcept
	:_size(other._size), _capacity(other._capacity)
{
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}

StringVector& StringVector::operator=(StringVector&& other) noexcept
{
	if (this != &other)
	{
		freeDynamic();
		_data = other._data;
		_size = other._size;
		_capacity = other._capacity;

		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;

	}
	return *this;
}

StringVector::~StringVector()
{
	freeDynamic();
}

void StringVector::setString(String* data)
{
	_data = new String[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = data[i];
	}
}

void StringVector::resize() 
{
	_capacity *= 2;
	//we also need to resize the data now
	String* newData = new String[_capacity];
	for (size_t i = 0; i < _capacity; ++i)
	{
		newData[i] = _data[i];
	}
	//delete the old data
	delete[] _data;
	_data = newData;
}
void StringVector::push_back(const String& str)
{
	//if not enough space
	if (_size >= _capacity)
	{
		resize();
	}
	_data[_size++] = str;
}
void StringVector::pop_back()
{
	if (_size == 0)
	{
		throw std::out_of_range("Cannot pop from empty vector.");
	}
	--_size;
}
void StringVector::insert(int index,const String& str)
{
	if (index < 0)
	{
		throw std::out_of_range("Index is invalid for inserting.\n");
	}
	if (index >= static_cast<int>(_size))
	{
		index = _size;
	}
	if (_size >= _capacity)
	{
		resize();
	}
	for (size_t i = _size; i > static_cast<int>(index); --i)
	{
		_data[i] = _data[i - 1];
	}

	_data[index] = str;
	++_size;
}
void StringVector::erase(int index)
{
	if (index < 0 || index >= static_cast<int>(_size))
	{
		throw std::out_of_range("Index is invalid for erasing.\n");
	}
	for (size_t i = static_cast<int>(index); i < _size; ++i)
	{
		_data[i] = _data[i + 1];
	}
	--_size;
}

void StringVector::clear()
{
	_size = 0;
}

String& StringVector::at(const int index)
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _data[index];
}

const String& StringVector::at(const int index) const
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _data[index];
}

bool StringVector::isEmpty() const
{
	return _size == 0;
}

size_t StringVector::getSize() const
{
	return _size;
}
