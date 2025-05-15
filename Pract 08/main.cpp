#include <iostream>
#include "StringVector.h"

int main()
{
	StringVector vector;

	vector.push_back("Hello");
	vector.push_back("World");

	std::cout << "Initial vector: \n";
	for (size_t i = 0; i < vector.getSize(); ++i) 
	{
		std::cout << vector.at(i) << std::endl;
	}

	vector.insert(1, "Amazing");
	vector.erase(2);

	std::cout << "\nIs empty? " << (vector.isEmpty() ? "Yes" : "No") << std::endl;
	vector.clear();
	std::cout << "\nAfter clear:\nIs empty? " << (vector.isEmpty() ? "Yes" : "No") << std::endl;
}
