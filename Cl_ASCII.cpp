//
//  Cl_ASCII.cpp
//  Basic_system
//
//  Created by Daniel on 2020/2/27.
//  Copyright © 2020 Daniel. All rights reserved.
//

#include "Cl_ASCII.h"

//struct ASCII_item{
//
//    ASCII_item() = default;
//    ASCII_item(const std::string &s, const char &ch, const unsigned &i): code_by2(s), value(ch), idx(i){}
//
//    std::string code_by2 = "00000000";
//    char value = ' ';
//    unsigned idx;
//
//    vector<char> code_vec();
//
//};

//ASCII_item as = {"01110100", 'a', 97};





// Input the ascii_file from the repository by it seems no use now.
void read_ASCII(vector<ASCII_item> & ascii_vec)
{
//    ifstream myfile("/Basic_system/ASCII_table.csv");
    ifstream myfile("/Users/Daniel/Documents/GitHub/basic_system_cpp/basic_system_cpp/ASCII_table.csv");

    string temp;
    if (!myfile.is_open()){
        cout << "未成功打开文件" << endl;
    }
    int num = 0;   // This is the value by 10
    while(getline(myfile, temp)){
        ASCII_item ascii_i(temp.substr(0, 8), temp[9], num++);
        ascii_vec.push_back(ascii_i);
//        cout << temp.substr(0, 8) << endl;
    }
    myfile.close();

//    return ASCII_vec
}



// Show the ascii_item binary code like a vector. Maybe it is convenient to compare with the value of RAM.
inline
vector<char> ASCII_item::code_vec(){
    vector<char> vec_char;
    for (auto c : code_by2){
        vec_char.push_back(c);
    }
    return vec_char;
}



//inline
//const ostream ASCII_item::show(ostream &os) const{
//    os << "by2 is " << code_by2
//    << " value is " << value
//    << " index is " << idx << endl;
////    return os;
//    return os
//}
//
//inline
//void ASCII_item::show() const{
//    cout << "by2 is " << code_by2
//    << " value is " << value
//    << " index is " << idx << endl;
//}






// Changing character into binary system

//string char_to_binary(const char &ch){
//    string by2;
//    switch (ch) {
//        case 'a':
//            by2 = "01100001";
//            break;
//        case 'b':
//            by2 = "01100010";
//            break;
            
//        default:
//            by2 = "00000000";
//            break;
//    }
//    return by2;
//};


// Changing character into binary system by system
// 用系统自带的 char -> int.10 -> int.2
//
//string char_to_binary_sys(const char &ch){
//    int num = (int)ch;
//
//    string by2 = "00000000";
//    for(int i = 8; i >= 0; i--){
//        if(num & (1<<i))
//            by2[7-i] = '1';
//        else
//            by2[7-i] = '0';
//    }
//
//    return by2;
//}
//
//
//
//
//
//// Changing binary system into character
//// Unfinished
//
//char binary_to_char(const string & by2){
//    int i = std::stoi(by2, nullptr, 2);
//    char ch;
//    switch (i) {
//        case 97:
//            ch = 'a';
//            break;
//
//        default:
//            ch = ' ';
//            break;
//    }
//
//    return ch;
//}
//
//// 想一个 int.2 -> int.10 -> char 的方法
