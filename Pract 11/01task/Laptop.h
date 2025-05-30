#pragma once
#include "Computer.h"

class Laptop : public Computer
{
public:
	Laptop();
	Laptop(double procesorPower, const char* videoCard, int power, int ram);

	void describeComputer() const override;
	void printComponents() const override;
};
