#include <cstdio>
#include "../headers/cpu.h"




bool testLda()
{
    bool resultTest = false;

    for(int i = 0; i < 8; ++i)
    {
        ub::cpu();
        ub::cpuInfo();
    }


    return resultTest;
}

int main(){

    testLda();


    return 0;

}
