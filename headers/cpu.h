#ifndef __UB_CPU_H__
#define __UB_CPU_H__

namespace ub
{

struct
{
    uint16_t PC;    // command counter
    int8_t  A;      // accumulate
    uint8_t S;      // pointer stack
    uint8_t X;      // index register
    uint8_t Y;      // index register
    union
    {
        struct
        {
            uint8_t C:1;
            uint8_t Z:1;
            uint8_t I:1;
            uint8_t D:1;
            uint8_t B:1;
            uint8_t unused:1;
            uint8_t V:1;
            uint8_t N:1;
        } flags;
    } P;            // register status
} CpuRegister;



uint8_t readFromRam();
void writeToRam();


int cpu();


void immediate();

void absolute();

void zeropage();

void accumulator();

void absoluteX();

void absoluteY();

void zeropageX();

void zeropageY();

void indirect();

void indirectX();

void indirectY();

void relative();


uint8_t adc(uint8_t value, uint8_t cycles);



}
#endif //__UB_CPU_H__
