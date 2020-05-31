//
//  F_code_library.cpp
//  Basic_system
//
//  Created by Daniel on 2020/2/29.
//  Copyright © 2020 Daniel. All rights reserved.
//

#include "F_code_library.h"
#include "Header.h"
#include <ctime>


using namespace std;

void change_byte_by_char(Byte & bt, char ch){

    string by2 = char_to_binary_sys(ch);

    for (int count = 0; count < 8; count++){
        bool bool_value = ((by2[count] == '0') ? false : true);
        bt.change_contents(count, bool_value);
    }
    bt.used = 1;
}

void change_byte_by_num(Byte & bt, int num){
    string by2 = num_to_binary(num);

    for (int count = 0; count < 8; count++){
        bool bool_value = ((by2[count] == '0') ? false : true);
        bt.change_contents(count, bool_value);
    }
    bt.used = 1;
}

Byte change_contents_outside(Byte & bt, const short &ix, bool new_item){
    bt.change_contents(ix, new_item);
    return bt;
}


/*
 这部分是ASCII转化的函数
 */
string char_to_binary(char &ch){
    int num = (int)ch;
    string by2;
    string result;
    int i = 0;
    int j = 1;
    while(i < 8){
        result = result + to_string(num % 2);
        num = num / 2;
        j = j * 10;
        i++;
    }
    for (int i = 0; i < 8; i++){
        by2 += result[7-i];
    }

    return by2;

}

string char_to_binary_sys(char &ch){
    int num = (int)ch;
    string by2;
    string result;
    int i = 0;
    int j = 1;
    while(i < 8){
        result = result + to_string(num % 2);
        num = num / 2;
        j = j * 10;
        i++;
    }
    for (int i = 0; i < 8; i++){
        by2 += result[7-i];
    }

    return by2;
}


char binary_to_char(vector<bool> & by2){
    int result = 0;
    int temp = 1;
    for (int i = 7; i >= 0;i--){
        if (by2[i] == 1){
            result += temp;
        }
        temp *= 2;
    }
    char ch = result;
    return ch;
}

int binary_to_num(vector<bool> & by2){
    int result = 0;
    int temp = 1;
    for (int i = 7; i >= 0;i--){
        if (by2[i] == 1){
            result += temp;
        }
        temp *= 2;
    }
    return(result);
}

string num_to_binary(int & num) {
    string by2;
    string result;
    int i = 0;
    int j = 1;
    while(i < 8){
        result = result + to_string(num % 2);
        num = num / 2;
        j = j * 10;
        i++;
    }
    for (int i = 0; i < 8; i++){
        by2 += result[7-i];
    }

    return by2;
}
vector<RAM> build_RAM(const int &RAM_num = 10){
    vector<RAM> RAM_vec;
    for (int i = 0; i != RAM_num; ++i){
        RAM ram;
        ram.start_1(i);
        RAM_vec.push_back(ram);
    }
    return RAM_vec;
}

vector<ROM> build_ROM(const int &ROM_num = 1024){
    vector<ROM> ROM_vec;
    for (int i = 0; i != ROM_num; ++i){
        ROM rom;
        rom.start_1(i);
        ROM_vec.push_back(rom);
    }
    return ROM_vec;
}



void ram_report(const vector<RAM> & RAM_vec){
    for(auto ram : RAM_vec){
        cout << "This is No " << ram.idx
        << " ram and the length is " << ram.layer_num << "."
        << endl;
    }
}

/* num <--> ROM */
void num_to_rom (int num, int index, ROM &rom){
    if (num > 99999) {
        cout << "The length of the number is out of range";
    }
    string str = to_string(num);
    for (int i = 0; i < 5; i++){
        change_byte_by_char(rom.contents[index+i], str[i]);
//        rom.contents[index+i].show_contents(cout);
    }
}

int rom_to_num(int index, ROM rom){
    string str;
    for (int i = 0; i < 5; i++){
        str += binary_to_char(rom.contents[index+i].contents);
    }
    int num = atoi(str.c_str());
    return(num);
}

double ram_usage(RAM & ram){
    //cout << "The index of this ram is " << ram.idx << endl;
    //cout << "The size of this ram is " << ram.length_num << endl;
    double usage = (1024 - ram.remain)/double(1024)*100;
    return(usage);
}


/*
 * 系统内存监控
 *
 */

/*内存使用率*/
double memory_usage(vector<RAM> ana_ram){

    int n  = ana_ram.size();
    int count = 0;
    for (int i = 0; i < n; i++){
        count += ana_ram[i].ram_used;
    }
    double result = double(count)/n;

    return(result*100);
}

/*单个*/
void memory_report(vector<RAM> ana_ram){
    int n  = ana_ram.size();
    cout << "The total memory space is: " << n << "KB" << "   "
         << "Usage: " << memory_usage(ana_ram) << "%" << endl;
}


/*监测系统全部内存使用情况*/
void system_report(vector<RAM> ana_ram){

    cout << "----------------System Report---------------" << endl;
    cout << "ana_ram: " << endl;
    memory_report(ana_ram);
    cout << "--------------------------------------------" << endl;

}


/*
 * 内存分配算法（First-fit)
 */
string show_RAM(vector<RAM> ana_ram){
    string s;
    for (int i = 0; i < int(ana_ram.size()); i++){
        s += to_string(ana_ram[i].ram_used);
    }
    return s;
}

int memory_allocation(int length, vector<RAM> ana_ram){
    string s1;
    string s2 = show_RAM(ana_ram);
    for (int i = 0; i < length; i++){
        s1 += "0";
    }
    if (s2.find(s1, 0) == string::npos){
        return -1;
    }
    return s2.find(s1, 0);
}
