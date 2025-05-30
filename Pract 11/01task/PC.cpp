#include "PC.h"

PC::PC() : Computer() {}

PC::PC(double procesorPower, const char* videoCard, int power, int ram)
	:Computer(procesorPower, videoCard, power, ram){}

void PC::describeComputer() const
{
	std::cout << "This is a PC." << std::endl;
	Computer::describeComputer();
}

void PC::printComponents() const
{
	static const char* components[] = { "mouse", "keyboard", "microphone", "headphones" };
	const int count = sizeof(components) / sizeof(components[0]);

	std::cout << "PC Peripherals:\n";
	for (int i = 0; i < count; ++i) {
		std::cout << "- " << components[i] << std::endl;
	}
}
