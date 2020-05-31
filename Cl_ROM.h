//
//  Cl_ROM.hpp
//  Basic_system
//
//

#ifndef Cl_ROM_hpp
#define Cl_ROM_hpp

#include <stdio.h>
#include "Cl_Byte.h"


class ROM{
public:
    ROM & start_1(const int &rom_index);
    ROM & restart();
    ROM & change_length(int new_length_num);
    ROM & change_layer(int new_layer_num);

public:
    int length_num = 21100;
//    int layer_num = 1024;
    vector<Byte> contents;
    int idx = 0;
    
};


#endif /* Cl_ROM_hpp */
