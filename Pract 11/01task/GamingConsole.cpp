#include "GamingConsole.h"

GamingConsole::GamingConsole() : Computer() {}

GamingConsole::GamingConsole(double procesorPower, const char* videoCard, int power, int ram)
	:Computer(procesorPower, videoCard, power, ram) {}

void GamingConsole::describeComputer() const
{
	std::cout << "This is a GamingConsole." << std::endl;
	Computer::describeComputer();
}

void GamingConsole::printComponents() const
{
	static const char* components[] = { "joystick", "monitor" };
	const int count = sizeof(components) / sizeof(components[0]);

	std::cout << "Gaming Console Peripherals:\n";
	for (int i = 0; i < count; ++i) {
		std::cout << "- " << components[i] << std::endl;
	}
}
