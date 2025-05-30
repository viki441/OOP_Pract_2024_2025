#pragma once
#include "Computer.h"

class PC : public Computer
{
public:
	PC();
	PC(double procesorPower, const char* videoCard, int power, int ram);

	void describeComputer() const override;
	void printComponents() const override;
};
