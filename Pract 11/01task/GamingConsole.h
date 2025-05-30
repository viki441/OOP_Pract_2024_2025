#pragma once
#include "Computer.h"

class GamingConsole : public Computer
{
public:
	GamingConsole();
	GamingConsole(double procesorPower, const char* videoCard, int power, int ram);

	void describeComputer() const override;
	void printComponents() const override;
};
