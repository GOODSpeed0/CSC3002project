//
//  Cl_RAM.hpp
//  Basic_system
//
//  Created by Daniel on 2020/2/27.
//  Copyright © 2020 Daniel. All rights reserved.
//

#ifndef CL_RAM_h
#define CL_RAM_h

#include <stdio.h>
#include "Header.h"
#include "Cl_Byte.h"


class RAM{

public:
    RAM & start();     // Start the RAM
    RAM & restart();   // restart the RAM
    RAM & change_length(int new_length_num);
    RAM & change_layer(int new_layer_num);
    RAM & start_1(const int &ram_index);
    RAM & content(int index);
    
public:
    int length_num = 1024;   // 1K
    int layer_num = 1024;
    int remain = 1024;
    int ram_used = 0;
    vector<Byte> contents;
    int idx = 0;
};


#endif
