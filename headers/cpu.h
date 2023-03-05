#include <stdint.h>

#ifndef __UB_CPU_H__
#define __UB_CPU_H__

using u_char = unsigned char;
using u_int = unsigned int;

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
        } flags = {.C = 0, .Z = 0, .I = 0, .D = 0, .B = 1, .unused = 1, .V = 0, .N = 0};
    } P;            // register status
} CpuRegister = {.PC = 0, .A = 0, .S = 0, .X = 0, .Y = 0};


void cpuInfo();


u_char readMemory();
void writeToRam();

u_char readRam(uint16_t addr);

int cpu();


uint16_t immediate();

uint16_t absolute();

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

uint8_t lda(uint8_t value, uint8_t cycles);


}
#endif //__UB_CPU_H__
