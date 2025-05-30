#include "Computer.h"
#include <cstring>
#pragma warning (disable : 4996)

void Computer::freeDynamic()
{
	_videoCard = nullptr;
	delete[] _videoCard;
}

void Computer::copyDynamic(const Computer& other)
{
	size_t size = std::strlen(other._videoCard);
	_videoCard = new char[size + 1];
	std::strcpy(_videoCard, other._videoCard);

}
Computer::Computer()
	:_processorPower(0), _videoCard(nullptr), _power(0), _ram(0){}


Computer::Computer(double procesorPower, const char* videoCard, int power, int ram)
	: _processorPower(procesorPower), _power(power), _ram(ram)
{
	setVideoCard(videoCard);
}
Computer::Computer(const Computer& other) 
	: _processorPower(other._processorPower), _power(other._power), _ram(other._ram)
{
	copyDynamic(other);
}
Computer& Computer::operator=(const Computer& other)
{
	if (this != &other)
	{
		freeDynamic();
		copyDynamic(other);
	}
	return *this; 
}
Computer::~Computer()
{
	freeDynamic();
}
//setters
void Computer::setVideoCard(const char* videoCard)
{
	size_t size = std::strlen(videoCard);
	_videoCard = new char[size + 1];
	std::strcpy(_videoCard, videoCard);
}

//getters
const double Computer::getProcessorPower() const
{
	return _processorPower;
}
const char* Computer::getVideoCard() const
{
	return _videoCard;
}
const int Computer::getPower() const
{
	return _power;
}
const int Computer::getRam() const
{
	return _ram;
}

//additional
void Computer::describeComputer() const
{
	std::cout << "Processor Power " << getProcessorPower()
		<< std::endl << "Videocard: " << getVideoCard()
		<< std::endl << "Power: " << getPower()
		<< std::endl << "RAM: " << getRam() << std::endl;
}

void Computer::printComponents() const
{
	std::cout << "No components added.\n";
}
