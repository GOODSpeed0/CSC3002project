//
//  F_code_library.hpp
//  Basic_system
//
//

#ifndef F_code_library_hpp
#define F_code_library_hpp


#include <stdio.h>
#include "Header.h"

#include "Cl_Byte.h"
#include "Cl_Byte.cpp"

#include "Cl_RAM.h"
#include "Cl_RAM.cpp"

#include "Cl_ROM.h"
#include "Cl_ROM.cpp"


//#include "Cl_ASCII.h"
//#include "Cl_ASCII.cpp"


/*
这部分是改变Byte内容的函数
*/


void change_byte_by_char(Byte & bt, char ch);

void change_byte_by_num(Byte & bt, int num);

Byte change_contents_outside(Byte & bt, const short &ix, bool new_item);


/* read the file */
void read_ASCII(vector<ASCII_item> & ascii_vec);


/* char<--->binary */
string char_to_binary(char & ch);

string char_to_binary_sys(char &ch);

char binary_to_char(vector<bool> & by2);


/* number(10)<--->binary */
int binary_to_num(vector<bool> & by2);

string num_to_binary(int & num);

void num_to_rom (int num, int index, ROM &rom);

int rom_to_num(int index, ROM rom);


/*
 * RAM和ROM的生成&报告
 */

void ram_report(const vector<RAM> & RAM_vec);

void rom_report(const vector<ROM> & RAM_vec);

vector<RAM> build_RAM(const int &RAM_num);

vector<ROM> build_ROM(const int &ROM_num);



/*
 * 这里是将一些东西写入到指定ROM中去
 */

double ram_usage(RAM & ram);

double rom_usage(ROM & rom);




/*
 * 系统内存监控
 */
double memory_usage(vector<RAM> ana_ram);

void memory_report(vector<RAM> ana_ram);

void system_report(vector<RAM> ana_ram);


/*
 * 内存分配算法（First-fit)
 */
string show_RAM(vector<RAM> ana_ram);

int memory_allocation(int length, vector<RAM> ana_ram);


#endif /* F_code_library_hpp */

