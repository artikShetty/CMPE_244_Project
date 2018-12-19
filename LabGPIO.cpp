#include <stdio.h>
#include "tasks.hpp"
#include "lpc_sys.h"
#include "utilities.h"
#include "LabGPIO.hpp"

LabGPIO::LabGPIO(uint8_t port,uint8_t pin)
{
    Port = port;
    Pin = pin;
}
void LabGPIO::setAsInput()
{
    switch (Port)
    {
        case 0: LPC_GPIO0->FIODIR &= ~(1 << Pin);
        break;
        case 1: LPC_GPIO1->FIODIR &= ~(1 << Pin);
        break;
        case 2: LPC_GPIO2->FIODIR &= ~(1 << Pin);
        break;
    }
}
void LabGPIO::setAsOutput()
{
    switch (Port)
    {
        case 0: LPC_GPIO0->FIODIR |= (1 << Pin);
        break;
        case 1: LPC_GPIO1->FIODIR |= (1 << Pin);
        break;
        case 2: LPC_GPIO2->FIODIR |= (1 << Pin);
        break;
    }
}
void LabGPIO::setHigh()
{
    switch (Port)
    {
        case 0: LPC_GPIO0->FIOPIN |= (1 << Pin);
        break;
        case 1: LPC_GPIO1->FIOPIN |= (1 << Pin);
        break;
        case 2: LPC_GPIO2->FIOPIN |= (1 << Pin);
        break;
    }
}
void LabGPIO::setLow()
{
    switch (Port)
    {
        case 0: LPC_GPIO0->FIOPIN &= ~(1 << Pin);
        break;
        case 1: LPC_GPIO1->FIOPIN &= ~(1 << Pin);
        break;
        case 2: LPC_GPIO2->FIOPIN &= ~(1 << Pin);
        break;
    }
}
void LabGPIO::set(bool high)
{
    if (high == true)
    {
        switch (Port)
        {
            case 0: LPC_GPIO0->FIOPIN |= (1 << Pin);
            break;
            case 1: LPC_GPIO1->FIOPIN |= (1 << Pin);
            break;
            case 2: LPC_GPIO2->FIOPIN |= (1 << Pin);
            break;
        }
    }
    else
    {
        switch (Port)
        {
            case 0: LPC_GPIO0->FIOPIN &= ~(1 << Pin);
            break;
            case 1: LPC_GPIO1->FIOPIN &= ~(1 << Pin);
            break;
            case 2: LPC_GPIO2->FIOPIN &= ~(1 << Pin);
            break;
        }
    }
}
bool LabGPIO::getLevel()
{
    switch (Port)
    {
        case 0:
        {
            if(LPC_GPIO0->FIOPIN & (1 << Pin))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
        case 1:
        {
            if(LPC_GPIO1->FIOPIN & (1 << Pin))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
        case 2:
        {
            if(LPC_GPIO2->FIOPIN & (1 << Pin))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    }
    return false;
}
