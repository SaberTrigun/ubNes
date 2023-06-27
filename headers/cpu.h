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
} CpuRegister = {.PC = 0, .A = 0, .S = 0, .X = 0x05, .Y = 0x06};


void cpuInfo();


u_char readMemory();
void writeToRam();

uint8_t readRam(uint16_t addr);

int cpu();


uint16_t immediate();

uint16_t absolute();

uint16_t zeropage();

void accumulator();

uint16_t absoluteX();

uint16_t absoluteY();

uint16_t zeropageX();

uint16_t zeropageY();

void indirect();

uint16_t preIndexedIndirectZpX();

uint16_t postIndexedIndirectZpY();

void relative();


uint8_t adc(uint8_t value, uint8_t cycles);

uint8_t lda(uint8_t value, uint8_t cycles);

uint8_t ldx(uint8_t value, uint8_t cycles);

uint8_t ldy(uint8_t value, uint8_t cycles);

uint8_t sta(uint8_t value, uint8_t cycles);

uint8_t stx(uint8_t value, uint8_t cycles);

uint8_t sty(uint8_t value, uint8_t cycles);

uint8_t tax(uint8_t value, uint8_t cycles);

uint8_t tay(uint8_t value, uint8_t cycles);

uint8_t tsx(uint8_t value, uint8_t cycles);

uint8_t txa(uint8_t value, uint8_t cycles);

uint8_t txs(uint8_t value, uint8_t cycles);

uint8_t tya(uint8_t value, uint8_t cycles);



}
#endif //__UB_CPU_H__
