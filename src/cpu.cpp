#include <stdio.h>
#include "../headers/cpu.h"


namespace ub
{
unsigned int code[18] = {0xB1, 0x00};
//u_char code[5] = {0xB1, 0x50};
uint8_t ram[0x02] = {};


    // Мы получаем код операции из PC по нему вызываем нужную функцию с нужным режимом адресом
int cpu()
{
    int result = 0;

    switch(readMemory())
    {
        case 0xA9:
            ++CpuRegister.PC;
            lda(immediate(), 2);
            ++CpuRegister.PC;
            break;
        case 0xA5:
            ++CpuRegister.PC;
            lda(zeropage(), 2);
            ++CpuRegister.PC;
            break;
        case 0xB5:
            ++CpuRegister.PC;
            lda(zeropageX(), 2);
            ++CpuRegister.PC;
            break;
        case 0xAD:
            ++CpuRegister.PC;
            lda(absolute(), 2);
            ++CpuRegister.PC;
            break;
        case 0xBD:
            ++CpuRegister.PC;
            lda(absoluteX(), 3);
            ++CpuRegister.PC;
            break;
        case 0xB9:
            ++CpuRegister.PC;
            lda(absoluteY(), 3);
            ++CpuRegister.PC;
            break;
        case 0xA1:
            ++CpuRegister.PC;
            lda(preIndexedIndirectZpX(), 3);
            ++CpuRegister.PC;
            break;
        case 0xB1:
            ++CpuRegister.PC;
            lda(postIndexedIndirectZpY(), 3);
            ++CpuRegister.PC;
            break;
        case 0xA2:
            ++CpuRegister.PC;
            ldx(immediate(), 2);
            ++CpuRegister.PC;
        case 0xA6:
            ++CpuRegister.PC;
            ldx(zeropage(), 2);
            ++CpuRegister.PC;
        case 0xB6:
            ++CpuRegister.PC;
            ldx(postIndexedIndirectZpY(), 2);
            ++CpuRegister.PC;
        case 0xAE:
            ++CpuRegister.PC;
            ldx(absolute(), 3);
            ++CpuRegister.PC;
        case 0xBE:
            ++CpuRegister.PC;
            ldx(absoluteY(), 3);
            ++CpuRegister.PC;
        case 0xA0:
            ++CpuRegister.PC;
            ldy(immediate(), 2);
            ++CpuRegister.PC;
        case 0xA4:
            ++CpuRegister.PC;
            ldy(zeropage(), 2);
            ++CpuRegister.PC;
        case 0xB4:
            ++CpuRegister.PC;
            ldy(preIndexedIndirectZpX(), 2);
            ++CpuRegister.PC;
        case 0xAC:
            ++CpuRegister.PC;
            ldy(absolute(), 3);
            ++CpuRegister.PC;
        case 0xBC:
            ++CpuRegister.PC;
            ldy(absoluteX(), 3);
            ++CpuRegister.PC;
        case 0x85:
            ++CpuRegister.PC;
            sta(zeropage(), 2);
            ++CpuRegister.PC;
            break;
        case 0x95:
            ++CpuRegister.PC;
            sta(zeropageX(), 2);
            ++CpuRegister.PC;
            break;
        case 0x8D:
            ++CpuRegister.PC;
            sta(absolute(), 3);
            ++CpuRegister.PC;
            break;
        case 0x9D:
            ++CpuRegister.PC;
            sta(absoluteX(), 3);
            ++CpuRegister.PC;
            break;
        case 0x99:
            ++CpuRegister.PC;
            sta(absoluteY(), 3);
            ++CpuRegister.PC;
            break;
        case 0x81:
            ++CpuRegister.PC;
            sta(preIndexedIndirectZpX(), 2);
            ++CpuRegister.PC;
            break;
        case 0x91:
            ++CpuRegister.PC;
            sta(postIndexedIndirectZpY(), 2);
            ++CpuRegister.PC;
            break;
    }

    return result;
}


u_char readMemory()
{
    return code[CpuRegister.PC];
}


uint8_t readRam(uint16_t addr)
{
    for(int i = 0; i < 0xFF; ++i)
        ram[i] = i; // Заполняем рам значениями для теста
    return ram[addr];
}


uint16_t immediate()
{
    return code[CpuRegister.PC];
}


uint16_t absolute()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC]);
    return *ptrRam;
}


uint16_t zeropage()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC], 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return *ptrRam;

}


uint16_t zeropageX()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC] + CpuRegister.X, 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return *ptrRam;
}


uint16_t zeropageY()
{

}


uint16_t absoluteX()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC + CpuRegister.X]);
    return *ptrRam;
}


uint16_t absoluteY()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC + CpuRegister.Y]);
    return *ptrRam;
}


uint16_t preIndexedIndirectZpX()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC] + CpuRegister.X, 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(readRam(*ptrRam));
}

uint16_t postIndexedIndirectZpY()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC], 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(*ptrRam + CpuRegister.Y);
}


uint8_t lda(uint8_t value, uint8_t cycles)
{
    CpuRegister.A = readRam(value);
    return cycles;
}


uint8_t ldx(uint8_t value, uint8_t cycles)
{
    CpuRegister.X = readRam(value);
    return cycles;
}


uint8_t ldy(uint8_t value, uint8_t cycles)
{
    CpuRegister.Y = readRam(value);
    return cycles;
}


uint8_t sta(uint8_t value, uint8_t cycles)
{
    ram[value] = CpuRegister.A;
    return cycles;
}











void cpuInfo()
{
    printf("CpuRegister: \n");
    printf("PC-> %i \n", CpuRegister.PC);
    printf("A-> %i \n", CpuRegister.A);
    printf("S-> %i \n", CpuRegister.S);
    printf("X-> %i \n", CpuRegister.X);
    printf("Y-> %i \n", CpuRegister.Y);
    printf("P: \n");
    printf("C Z I D B - V N \n");
    printf("%i %i %i %i %i %i %i %i \n", CpuRegister.P.flags.C,
            CpuRegister.P.flags.Z,
            CpuRegister.P.flags.I,
            CpuRegister.P.flags.D,
            CpuRegister.P.flags.B,
            CpuRegister.P.flags.unused,
            CpuRegister.P.flags.V,
            CpuRegister.P.flags.N);
}
























}
