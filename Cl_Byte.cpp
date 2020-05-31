//
//  Cl_Byte.cpp
//  Basic_system
//
//  Created by Daniel on 2020/2/27.
//  Copyright © 2020 Daniel. All rights reserved.
//



#include "Cl_Byte.h"
#include "Header.h"


// this function is to show the contents of the byte
inline
const ostream &Byte::show_contents(ostream &os) const {
    os << contents[0] << " "
       << contents[1] << " "
       << contents[2] << " "
       << contents[3] << " "
       << contents[4] << " "
       << contents[5] << " "
       << contents[6] << " "
       << contents[7] << " "
       << "\t"
       << address << "\t"
       << (used ? "used" : "unused") << endl;
    return os;
}



// This function is to change the specific contents of one byte.

inline
Byte & Byte::change_contents(const short &ix, bool new_item){
    if (ix < 8 && ix >= 0)
        contents[ix] = new_item;
        if (used == false)
            set_open();
    return *this;
}


inline Byte & Byte::operator++(){
    //自加1规则
    if (contents[7]==false) {
        contents[7]=true;
        return *this;
        //最后一位0变1
    }
    else {
        //最后一位是1要发生进位
        contents[7]=false; //先给最右一位加1，然后往前每一位都是看加后操作
        //e.g 如果他的右边一位是0，说明右边原本是1，加完才变成0，需要进位，再看自己这一位0/1判断
        for (int i=6;i>=0;i--){
            if (contents[i+1]==true) return *this;//如果右边一位是1，说明已经加法完毕。
            else {
                if (contents[i]==false) contents[i]=true;
                else contents[i]=false;
            }
        }
        return *this;
    }
}
