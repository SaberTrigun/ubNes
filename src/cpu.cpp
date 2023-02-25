#include "../headers/cpu.h"


namespace ub
{

    // Мы получаем код операции из PC по нему вызываем нужную функцию с нужным режимом адресом
int cpu()
{
    int result = 0;

    switch(readFromRam())
    {
        case 0x69:
            ++CpuRegister.PC;
            result = adc(immediate(2));
            break;
        case 0x65:
            //todo from addrMod
            break;
        case 0x75:
            //todo from addrMod
            break;
        case 0x6D:
            //todo from addrMod
            break;
        case 0x7D:
            //todo from addrMod
            break;
        case 0x79:
            //todo from addrMod
            break;
        case 0x61:
            //todo from addrMod
            break;
        case 0x71:
            //todo from addrMod
            break;
    }

    return result;
}


uint8_t readFromRam()
{
    return CpuRegister.PC
}

uint8_t immediate()
{
    return
}

uint8_t adc(uint8_t value, uint8_t cycles)
{
    CpuRegister.A += value;
    return cycles;
}



























}
