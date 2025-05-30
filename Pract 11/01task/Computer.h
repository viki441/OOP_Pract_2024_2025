#pragma once
#include <iostream>

class Computer
{
private:

    double _processorPower;
    char* _videoCard;
    int _power;
    int _ram;

    void freeDynamic();
    void copyDynamic(const Computer& other);

public:
    Computer();
    Computer(double processorPower, const char* videoCard, int power, int ram);
    Computer(const Computer& other);
    Computer& operator=(const Computer& other);
    virtual ~Computer();

    //setters
    void setProcessorPower(double processorPower);
    void setVideoCard(const char* videoCard);
    void setPower(int power);
    void setRam(int ram);
    
    //getters
    const double getProcessorPower() const;
    const char* getVideoCard() const;
    const int getPower() const;
    const int getRam() const;

    //additional
    virtual void describeComputer() const;
    virtual void printComponents() const;
};
