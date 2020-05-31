//
//  Cl_Byte.hpp
//  Basic_system
//

#ifndef Cl_Byte_h
#define Cl_Byte_h


#include <stdio.h>
#include "Header.h"
#include "Cl_ASCII.h"


class Byte{
public:
    // set the byte used, open
    inline void set_open() {
        used = true;
    }
    
    // set the byte unused closed
    inline void set_closed() {
        contents = {0, 0, 0, 0, 0, 0, 0, 0};
        used = false;
    }
    
    // show the contents of the byte
    const ostream &show_contents(ostream &os) const;
    Byte & change_contents(const short &ix, bool new_item);
    inline Byte & operator++();
    
    
// some private properties, they needed to change into private.
    
public:
    vector<bool> contents = {0, 0, 0, 0, 0, 0, 0, 0};
    const short sz = 8;
    bool used = false;
    int address = 0;   // 暂时没有使用
    vector<int> index = {0, 0, 0};  // 用index来表示byte在ROM和RAM中的位置
    
};


//void change_byte_by_char(Byte & bt, const char & ch);


#endif /* Cl_Byte_hpp */
