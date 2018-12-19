#ifndef LABGPIO_H
#define LABGPIO_H

#include <sys/_stdint.h>

class LabGPIO
{

private:

 int Port;
 int Pin;

public:

LabGPIO(uint8_t port,uint8_t pin);

 void setAsInput();

 void setAsOutput();

 void setDirection(bool output);

 void setHigh();

 void setLow();

 void set(bool high);

 bool getLevel();

 //~LabGPIO();
};
#endif
