// gate_emt_dts_win.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include "tcp_unit.h"


int main()
{
    

    std::list<ConfigSharedMemory> memory;
    std::list<ConfigUnitGate> gaties;

    TypeSignal m = TypeSignal::Analog;

    if (read_config_file("conf.txt", &memory, &gaties) != 0)
    {
        std::cout << "ERROR READ CONFIG FILE" << std::endl;
        getch();
        return -1;
    }
    
    UnitSharedMemory* m1 = new UnitSharedMemory(*memory.begin());

    std::list<UnitSharedMemory> mi;
    for (auto iter2 = memory.begin(); iter2 != memory.end(); iter2++)
    {
        mi.push_back(UnitSharedMemory(*iter2));
    }

    for (auto iter2 = mi.begin(); iter2 != mi.end(); iter2++)
    {
        for (std::list<ConfigUnitGate>::iterator iter = gaties.begin(); iter != gaties.end(); iter++)
        {
            iter2->FillConfigUnitGate(&*iter);
        }
    }
    
 

    float* out = NULL;
    float* in = NULL;
    for (auto iter = mi.begin(); iter != mi.end(); iter++)
    {
        if ((&*iter)->parametrs.type_data == TypeData::OutPut) out = (float*)(&*iter)->buf;
        if ((&*iter)->parametrs.type_data == TypeData::InPut) in = (float*)(&*iter)->buf;
    }

    for (int i = 0; i < 100; i++)
    {
        out[i] = (float)i;
    }

    std::cout << "Hello World!\n";
    std::list<tcp_unit*> units_gate;
    int id = 0;
    for (auto iter = gaties.begin(); iter != gaties.end(); iter++)
    {
        units_gate.push_back(tcp_unit::create_tcp_unit(*iter, id));
        id++;
    }

next:
    /*Sleep(2000);
    for (int i = 0; i < 100; i++)
    {
        out[i]++;
    }

    std::cout << in[0] << std::endl;
    std::cout << in[99] << std::endl;
    */
    goto next;

}