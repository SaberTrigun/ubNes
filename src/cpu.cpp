#include <stdio.h>
#include "../headers/cpu.h"


namespace ub
{
u_char code[5] = {0xB1, 0x50};
uint8_t ram[0xFFFF] = {0};


    // Мы получаем код операции из PC по нему вызываем нужную функцию с нужным режимом адресом
int cpu()
{
    int result = 0;

    switch(readMemory())
    {
        case 0xA9:
            ++CpuRegister.PC;
            lda(immediate(), 2);
            //++CpuRegister.PC;
            break;
        case 0xA5:
            ++CpuRegister.PC;
            lda(zeropage(), 2);
            break;
        case 0xB5:
            ++CpuRegister.PC;
            lda(zeropageX(), 2);
            break;
        case 0xAD:
            ++CpuRegister.PC;
            lda(absolute(), 2);
            break;
        case 0xBD:
            ++CpuRegister.PC;
            lda(absoluteX(), 3);
            break;
        case 0xB9:
            ++CpuRegister.PC;
            lda(absoluteY(), 3);
            break;
        case 0xA1:
            ++CpuRegister.PC;
            lda(indirectX(), 3);
            //todo from addrMod
            break;
        case 0xB1:
            ++CpuRegister.PC;
            lda(indirectY(), 3);
            //todo from addrMod
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
    ram[0x0050] = 0x0050;
    ram[0x0056] = 37;
    return ram[addr];
}


uint16_t immediate()
{
    return code[CpuRegister.PC];
}


uint16_t absolute()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC]);
    return readRam(*ptrRam);
}


uint16_t zeropage()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC], 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(*ptrRam);

}


uint16_t zeropageX()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC] + CpuRegister.X, 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(*ptrRam);
}


uint16_t absoluteX()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC + CpuRegister.X]);
    return readRam(*ptrRam);
}


uint16_t absoluteY()
{
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&code[CpuRegister.PC + CpuRegister.Y]);
    return readRam(*ptrRam);
}


uint16_t indirectX()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC] + CpuRegister.X, 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(readRam(*ptrRam));
}

uint16_t indirectY()
{
    uint8_t zeroAddr[2] = {code[CpuRegister.PC], 0x00};
    uint16_t* ptrRam = reinterpret_cast<uint16_t*>(&zeroAddr);
    return readRam(readRam(*ptrRam) + CpuRegister.Y);
}


uint8_t lda(uint8_t value, uint8_t cycles)
{
    CpuRegister.A = value;
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
