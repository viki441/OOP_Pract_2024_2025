#include "Laptop.h"

Laptop::Laptop() : Computer() {}

Laptop::Laptop(double procesorPower, const char* videoCard, int power, int ram)
	:Computer(procesorPower, videoCard, power, ram) {}

void Laptop::describeComputer() const
{
	std::cout << "This is a Laptop." << std::endl;
	Computer::describeComputer();
}

void Laptop::printComponents() const
{
	static const char* components[] = { "mouse pad", "keyboard", "monitor"};
	const int count = sizeof(components) / sizeof(components[0]);

	std::cout << "Laptop Peripherals:\n";
	for (int i = 0; i < count; ++i) {
		std::cout << "- " << components[i] << std::endl;
	}
}
