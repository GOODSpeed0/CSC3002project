//
//  Cl_ROM.cpp
//  Basic_system
//

#include "Cl_ROM.h"

inline
ROM & ROM::start_1(const int &rom_index){
    int count = 0;
    for(int i = 0; i != length_num; ++i){
        Byte bt;
        bt.address = count;
        contents.push_back(bt);
        ++ count;
    }
    idx = rom_index;
    return *this;
}


// change the length of the ROM
inline
ROM & ROM::change_length(int new_length_num){
    length_num = new_length_num;
    return *this;
}

// change the layer of the ROM
//inline
//ROM & ROM::change_layer(int new_layer_num){
//    layer_num = new_layer_num;
//    return *this;
//}

