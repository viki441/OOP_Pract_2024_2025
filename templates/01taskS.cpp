#include <iostream>
#include <stdexcept>

template <typename T, size_t Size>
class Array
{
private:

	T myArray[Size];
	size_t currSize = 0;

public:

	//Constructor to initialize all elements with a value
	Array(const T& initValue, size_t Size)
	{
		for (size_t i = 0; i < initValue; ++i)
		{
			myArray[i] = initValue;
		}
	}

	//default ctor
	Array() 
		: currSize(0) {
	for (size_t i = 0; i < Size; ++i)
		{	 
			myArray[i] = T();
		}
	}

	//we predefine the operator[] for the array we use, to act like one since it's T type
	T& operator[] (size_t index)
	{
		return myArray[index];
	}

	const T& operator[](size_t index) const // for shit like const Array<int, 5> arr
	{
		return myArray[index];
	}

	//additional
	size_t getMaxSize()
	{
		return Size;
	}

	size_t getSize()
	{
		return currSize + 1;
	}

	bool isEmpty()
	{
		return currSize == 0 ? true : false;
	}

	T& at(size_t index)
	{
		if (index >= currSize)
		{
			throw std::out_of_range("Index is to big\n");
		}
		return myArray[index];
	}


	const T& at(size_t index) const
	{
		if (index >= currSize)
		{
			throw std::out_of_range("Index is to big\n");
		}
		return myArray[index];
	}

	T& front()
	{
		return myArray[0];
	}

	const T& front() const
	{
		return myArray[0];
	}

	T& back()
	{
		return myArray[--currSize];
	}

	const T& back() const
	{
		return myArray[currSize];
	}

	void swap(Array& other) noexcept
	{
		using std::swap;
		swap(currSize, other.currSize);
		for (size_t i = 0; i < Size; ++i) 
		{
			swap(myArray[i], other.myArray[i]);
		}
	}

	void pushBack(const T& value)
	{
		if (currSize >= Size)
		{
			throw std::out_of_range("Array is full\n");
		}
		myArray[currSize++] = value;

	}

	void popBack()
	{
		if (currSize <= 0)
		{
			throw std::out_of_range("Array is empty\n");
		}
		--currSize;
	}
};


template <size_t Size>
class Array<char, Size> 
{
private:
	char myArray[Size + 1];
	size_t currSize;

public:
	//default ctor
	Array()
		:currSize(0)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			myArray[i] = '\0';
		}
	}

	//ctor 
	Array(char initValue)
		:currSize(Size)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			myArray[i] = initValue;
		}
		myArray[Size] = '\0';
	}

	//operator[] 
	char& operator[](size_t index) 
	{
		return myArray[index];
	}

	const char& operator[](size_t index) const 
	{
		return myArray[index];
	}

	void pushBack(char value) 
	{
		if (currSize >= Size)
		{
			throw std::out_of_range("Array is full");
		}
		myArray[currSize++] = value;
		myArray[currSize] = '\0';
	}

	void popBack() 
	{
		if (currSize == 0)
		{
			throw std::out_of_range("Array is empty");
		}
		myArray[--currSize] = '\0';
	}

	char& at(size_t index) 
	{
		if (index >= currSize)
		{
			throw std::out_of_range("Invalid index");
		}
		return myArray[index];
	}

	size_t getSize() const 
	{
		return currSize + 1;
	}

	bool isEmpty() const 
	{
		return currSize == 0;
	}

	void display() const {
		for (size_t i = 0; i < currSize; ++i)
		{
			std::cout << myArray[i];
		}
		std::cout << '\n';
	}
};

int main()
{
	Array<int, 10> arr;

	arr.pushBack(5);
	arr.pushBack(10);
	arr.pushBack(15);

	std::cout << "Array contents:\n";
	for (size_t i = 0; i < arr.getSize(); ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";

	std::cout << "Front: " << arr.front() << "\n";
	std::cout << "Back: " << arr.back() << "\n";

	arr.popBack();
	std::cout << "After popBack(), size = " << arr.getSize() << "\n";


}
