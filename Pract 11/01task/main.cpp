#include "GamingConsole.h"
#include "Laptop.h"
#include "PC.h"
int main() {

    PC pc(3.5, "NVIDIA GTX 1080", 650, 16);
    pc.describeComputer();
    pc.printComponents();

    Laptop l1(3.0, "NVIDIA GTX 1080", 600, 12);
    l1.describeComputer();
    l1.printComponents();

}
