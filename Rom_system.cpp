#include "Rom_system.h"
#include "F_code_library.h"
#include <iostream>
#include <QMessageBox>
using namespace std;

void initial_rom(ROM & rom, string diskname){
    // directory pointer: [0,4] address <= 940
    int dir_pointer = 70;
    num_to_rom(dir_pointer,0, rom);

    // document pointer: [5,9] address <= 20000
    int doc_pointer = 1000;
    num_to_rom(doc_pointer,5, rom);

    /* input hole_pointers including folder hole [20000,20100], document/App hole [20100,20300] */

    //input path to rom [10, 39]
    string path;
    path = diskname + ":\\";

    if (path.length() > 30) {
        // exception flag1
        cout << "Length of name is out of range!";}
    else{
        for(int i = 10; i < int(path.length())+10; i++){
            change_byte_by_char(rom.contents[i], path[i-10]);
        }
    }

    //input type to rom [40, 49]
    string type = "folder";
    for(int i = 40; i < int(type.length())+40; i++){
        change_byte_by_char(rom.contents[i], type[i-40]);
    }

    //input size to rom [50, 54]
    int size = 60+210;
//    change_byte_by_num(rom.contents[41], size);
    num_to_rom(size, 50, rom);

    //input superset address: [55,59]


    //input subset address: [60, 64]; [65, 69]

}

void createFolder(string path, string folderName, ROM & rom){

    // change directory address pointer (70 -> 130)
    int current_address = rom_to_num(0, rom);

    int new_address = current_address + 60;

    num_to_rom(new_address, 0, rom);

    // get the address of path, to deal with its properties: size, sub_address
    int super_address = getAddress(path,rom); //10


    // change size of super_folder
    int super = super_address;
    while(super != 0){
        int orignal_size = rom_to_num(super+40,rom);

        int new_size = orignal_size +60;

        num_to_rom(new_size, super+40, rom);

        super = rom_to_num(super+45, rom);
    }


    // change sub_address of super_folder
    if (rom.contents[super_address+50].used == false){
        num_to_rom(current_address,super_address+50,rom);
    }
    else if (rom.contents[super_address+55].used == false){
        num_to_rom(current_address,super_address+55,rom);
    }
    else{
        // exception flag3: can't create subfiles more than two
        cout << "You can't create more folder or document" << endl;
    }

    // input path to rom
    string folder_path;
    folder_path = path + folderName + "\\";

    if (folder_path.length() > 30) {
        cout << "Length of name is out of range!";}
    else{
        for(int i = current_address; i < int(folder_path.length())+current_address; i++){
            change_byte_by_char(rom.contents[i], folder_path[i-current_address]);
        }
    }

    //input type to rom
    string type = "folder";
    for(int i = 30+current_address; i < int(type.length())+30+current_address; i++){
        change_byte_by_char(rom.contents[i], type[i-30-current_address]);
    }

    //input size to rom
    int size = 60;
    num_to_rom(size,40+current_address,rom);

    //input super_address to rom
    num_to_rom(super_address,current_address+45,rom);
}


int getAddress(string target_path, ROM &rom){

    vector<int> vec;
    getAllAddress(rom, vec);
    int pointer;

    for (int i=0; i<int(vec.size());i++){
        pointer = vec[i];
        string current_path = "";
        for (int i=pointer; i<pointer+30; i++){
            if (rom.contents[i].used==true){
                current_path = current_path + binary_to_char(rom.contents[i].contents);
            }
            else{
                break;
            }
        }
//        cout << "address: " << current_path << endl;

        bool flag = !current_path.compare(target_path);

        if (flag){
            return pointer;
        }
    }

    // exception flag2 (文件找不到)
//    cout << "Don't find corresponding folder or file" << endl;
    return 0;
}

int getAllAddress(ROM & rom, vector<int> & vec, int pointer){

    vec.push_back(pointer);

    int next_pointer1;
    int next_pointer2;
    next_pointer1 = rom_to_num(pointer+50,rom);
    next_pointer2 = rom_to_num(pointer+55,rom);

    if (next_pointer1 == 0 && next_pointer2 == 0){
        return 0;
    }
    else{
        if (next_pointer1!=0){
            getAllAddress(rom, vec, next_pointer1);
        }
        if (next_pointer2!=0){
            getAllAddress(rom, vec, next_pointer2);
        }
    }
    return 0;
}

void createFile(string path, File file, ROM & rom){

    // change directory address pointer (70 -> 130)
    int current_address = rom_to_num(0, rom);

    int new_address = current_address + 60;

    num_to_rom(new_address, 0, rom);

    // get the address of path, to deal with its properties: size, sub_address
    int super_address = getAddress(path,rom); //10


    // change size of super_folder
    int super = super_address;
    while(super != 0){
        int orignal_size = rom_to_num(super+40,rom);

//        int new_size = orignal_size + 60 + 57 + file.getSize();
        int new_size = orignal_size + 60 + 5000;

        num_to_rom(new_size, super+40, rom);

        super = rom_to_num(super+45, rom);
    }


    // change sub_address of super_folder
    if (rom.contents[super_address+50].used == false){
        num_to_rom(current_address,super_address+50,rom);
    }
    else if (rom.contents[super_address+55].used == false){
        num_to_rom(current_address,super_address+55,rom);
    }
    else{
        // exception flag3: can't create subfiles more than two
        cout << "You can't create more folder or document" << endl;
    }

    /******************** input file information to rom catalog ***************/
    // input path to rom
    string file_path;
    file_path = path + file.getFilename() + ".txt";

    if (file_path.length() > 30) {
        cout << "Length of path is out of range!";}
    else{
        for(int i = current_address; i < int(file_path.length())+current_address; i++){
            change_byte_by_char(rom.contents[i], file_path[i-current_address]);
        }
    }

    //input type to rom
    string type = "file";
    for(int i = 30+current_address; i < int(type.length())+30+current_address; i++){
        change_byte_by_char(rom.contents[i], type[i-30-current_address]);
    }

    //input size to rom
    int size = 60 + 5000;
    num_to_rom(size,40+current_address,rom);

    //input super_address to rom
    num_to_rom(super_address,current_address+45,rom);

    /*****************  to get real file address  *************/

    // to get current file address

    int file_address;
    int hole_address = findHole(rom);
    if (hole_address == -1){
        file_address = rom_to_num(5,rom);
        // change file/APP pointer to new address
        int new_file_address = file_address + 5000;
        num_to_rom(new_file_address, 5, rom);
    }
    else{
        file_address = hole_address;
    }

    // input file_address in folder part
    num_to_rom(file_address,current_address+50,rom);

    /*****************  input file class information to ROM  *************/

    // input filename
    string filename = file.getFilename();
    for(int i = file_address; i < int(filename.size())+file_address; i++){
        change_byte_by_char(rom.contents[i], filename[i-file_address]);
    }

    // input time
    string time = file.getTime();
    for(int i = file_address+10; i < int(time.size())+file_address+10; i++){
        change_byte_by_char(rom.contents[i], time[i-file_address-10]);
    }

    // input size of file
    int filesize = file.getSize();
    num_to_rom(filesize,file_address+30,rom);

    // input read_permission bool
    bool read_permission = file.isReadable();
    if (read_permission == true){
        change_byte_by_num(rom.contents[file_address+35],1);
    }
    else if (read_permission == false){
        change_byte_by_num(rom.contents[file_address+35],0);
    }
    // input write_permission bool
    bool write_permission = file.isWritable();
    if (write_permission == true){
        change_byte_by_num(rom.contents[file_address+36],1);
    }
    else if (write_permission == false){
        change_byte_by_num(rom.contents[file_address+36],0);
    }

    // input read password
    string read_password = file.getReadPassword();
    for(int i = file_address+37; i < int(read_password.size())+file_address+37; i++){
        change_byte_by_char(rom.contents[i], read_password[i-file_address-37]);
    }
    // input write password
    string write_password = file.getWritePassword();
    for(int i = file_address+47; i < int(write_password.size())+file_address+47; i++){
        change_byte_by_char(rom.contents[i], write_password[i-file_address-47]);
    }

    // input file contents
    string file_content = file.getContent();
    for(int i = file_address+57; i < int(file_content.size())+file_address+57; i++){
        change_byte_by_char(rom.contents[i], file_content[i-file_address-57]);
    }

}

void createApp(string path, string AppName, ROM & rom){

    // change directory address pointer (70 -> 130)
    int current_address = rom_to_num(0, rom);

    int new_address = current_address + 60;

    num_to_rom(new_address, 0, rom);

    // get the address of path, to deal with its properties: size, sub_address
    int super_address = getAddress(path,rom); //10


    // change size of super_folder
    int super = super_address;
    while(super != 0){
        int orignal_size = rom_to_num(super+40,rom);

        int new_size = orignal_size +60+5000;

        num_to_rom(new_size, super+40, rom);

        super = rom_to_num(super+45, rom);
    }


    // change sub_address of super_folder
    if (rom.contents[super_address+50].used == false){
        num_to_rom(current_address,super_address+50,rom);
    }
    else if (rom.contents[super_address+55].used == false){
        num_to_rom(current_address,super_address+55,rom);
    }
    else{
        // exception flag3: can't create subfiles more than two
        cout << "You can't create more folder or document" << endl;
    }

    // input path to rom
    string App_path;
    App_path = path + AppName + ".exe";

    if (App_path.length() > 30) {
        cout << "Length of name is out of range!";}
    else{
        for(int i = current_address; i < int(App_path.length())+current_address; i++){
            change_byte_by_char(rom.contents[i], App_path[i-current_address]);
        }
    }

    //input type to rom
    string type = "APP";
    for(int i = 30+current_address; i < int(type.length())+30+current_address; i++){
        change_byte_by_char(rom.contents[i], type[i-30-current_address]);
    }

    //input size to rom
    int size = 60 + 5000;
    num_to_rom(size,40+current_address,rom);

    //input super_address to rom
    num_to_rom(super_address,current_address+45,rom);


    /*****************  to get real APP address and change App hole pointer *************/

    // to get current App address

    int app_address;
    int hole_address = findHole(rom);
    if (hole_address == -1){
        app_address = rom_to_num(5,rom);
        // change file/APP pointer to new address
        int new_app_address = app_address + 5000;
        num_to_rom(new_app_address, 5, rom);
    }
    else{
        app_address = hole_address;
    }

    // input app_address in catalog part
    num_to_rom(app_address,current_address+50,rom);

}

void DeleteFile(string path, ROM & rom){
    // change size of super_folder
    int current_address = getAddress(path,rom);
    int current_size = rom_to_num(current_address+40,rom);
    int super_address = rom_to_num(current_address+45,rom);
    int super = super_address;
    while(super != 0){
        int orignal_size = rom_to_num(super+40,rom);

        int new_size = orignal_size-current_size;

        num_to_rom(new_size, super+40, rom);

        super = rom_to_num(super+45, rom);
    }

    // change sub_address of super_folder
    if (rom_to_num(super_address+50,rom) == current_address){

        // move sub_address2 to sub_address1
        int sub_address2 = rom_to_num(super_address+55,rom);
        num_to_rom(sub_address2,super_address+50,rom);

        // then release sbu_address2
        rom.contents[super_address+55].set_closed();
        rom.contents[super_address+56].set_closed();
        rom.contents[super_address+57].set_closed();
        rom.contents[super_address+58].set_closed();
        rom.contents[super_address+59].set_closed();
    }
    else if(rom_to_num(super_address+55,rom) == current_address){
        rom.contents[super_address+55].set_closed();
        rom.contents[super_address+56].set_closed();
        rom.contents[super_address+57].set_closed();
        rom.contents[super_address+58].set_closed();
        rom.contents[super_address+59].set_closed();
    }

    // add folder hole address to hole_pointer
    int hole_pointer;
    int hole_index = 21000;

        // to find empty hole_pointer address
    for (int i=21000; i<21100;i=i+5){
        hole_pointer = rom_to_num(i,rom);
        if (hole_pointer==0){
            hole_index = i;
            break;
        }
    }

    /**************delete all contents in terms of file************/

    // firstly delete file contents
    int current_file_address = rom_to_num(current_address+50,rom);
    for (int i=current_file_address; i<current_file_address+5000;i++){
        rom.contents[i].set_closed();
    }

    int hole_address = current_file_address;
    num_to_rom(hole_address,hole_index,rom);


    // then delete file info in catalog
    for (int i= current_address; i<current_address+60; i++){
        rom.contents[i].set_closed();
    }

}

void DeleteApp(string path, ROM & rom){
    // change size of super_folder
    int current_address = getAddress(path,rom);
    int current_size = rom_to_num(current_address+40,rom);
    int super_address = rom_to_num(current_address+45,rom);
    int super = super_address;
    while(super != 0){
        int orignal_size = rom_to_num(super+40,rom);

        int new_size = orignal_size-current_size;

        num_to_rom(new_size, super+40, rom);

        super = rom_to_num(super+45, rom);
    }

    // change sub_address of super_folder
    if (rom_to_num(super_address+50,rom) == current_address){

        // move sub_address2 to sub_address1
        int sub_address2 = rom_to_num(super_address+55,rom);
        num_to_rom(sub_address2,super_address+50,rom);

        // then release sbu_address2
        rom.contents[super_address+55].set_closed();
        rom.contents[super_address+56].set_closed();
        rom.contents[super_address+57].set_closed();
        rom.contents[super_address+58].set_closed();
        rom.contents[super_address+59].set_closed();
    }
    else if(rom_to_num(super_address+55,rom) == current_address){
        rom.contents[super_address+55].set_closed();
        rom.contents[super_address+56].set_closed();
        rom.contents[super_address+57].set_closed();
        rom.contents[super_address+58].set_closed();
        rom.contents[super_address+59].set_closed();
    }

    // add folder hole address to hole_pointer
    int hole_pointer;
    int hole_index = 21000;

        // to find empty hole_pointer address
    for (int i=21000; i<21100;i=i+5){
        hole_pointer = rom_to_num(i,rom);
        if (hole_pointer==0){
            hole_index = i;
            break;
        }
    }

    /**************delete all contents in terms of App************/

    // firstly delete file contents
    int current_file_address = rom_to_num(current_address+50,rom);
    for (int i=current_file_address; i<current_file_address+5000;i++){
        rom.contents[i].set_closed();
    }

    int hole_address = current_file_address;
    num_to_rom(hole_address,hole_index,rom);


    // then delete file info in catalog
    for (int i= current_address; i<current_address+60; i++){
        rom.contents[i].set_closed();
    }

}

int findHole(ROM & rom){
    int hole_pointer;

    for (int i=21000; i<21100;i=i+5){
        hole_pointer = rom_to_num(i,rom);
        if (hole_pointer!=0){
            return hole_pointer;
        }
    }
    return -1;
}


vector<string> openFolder(string path, ROM & rom){

    vector<string> vec_name;
    int current_address = getAddress(path, rom);

    int sub1_address = rom_to_num(current_address+50,rom);
    int sub2_address = rom_to_num(current_address+55,rom);

    if (sub1_address != 0){
        string sub_name1 = "";
        for (int i=sub1_address; i<sub1_address+30; i++){
            if (rom.contents[i].used==true){
                sub_name1 = sub_name1 + binary_to_char(rom.contents[i].contents);
            }
            else{
                break;
            }
        }
        vec_name.push_back(sub_name1);
    }
    if (sub2_address != 0){
        string sub_name2 = "";
        for (int i=sub2_address; i<sub2_address+30; i++){
            if (rom.contents[i].used==true){
                sub_name2 = sub_name2 + binary_to_char(rom.contents[i].contents);
            }
            else{
                break;
            }
        }
        vec_name.push_back(sub_name2);
    }
    return vec_name;
}

File openFile(string path, ROM & rom){

    File file;
    // get the address of path in folder part
    int current_address = getAddress(path,rom);
//    cout << "file address in folder part: " << current_address << endl;

    // get corresponding file address
    int file_address = rom_to_num(current_address+50,rom);
//    cout << "file address: " << file_address << endl;

    /*****************  read file in ROM into File class  *************/

    // read filename
    string filename="";
    for(int i = file_address; i < file_address+10; i++){
        if (rom.contents[i].used == false){
            break;
        }
        filename = filename + binary_to_char(rom.contents[i].contents);
    }
    file.setName(filename);

    // read time
    string time = "";
    for(int i = file_address+10; i < file_address+30; i++){
        if (rom.contents[i].used == false){
            break;
        }
        time = time + binary_to_char(rom.contents[i].contents);
    }
    file.setTime(time);

    // read size of file
    int filesize;
    filesize = rom_to_num(file_address+30,rom);
//    file.setSize(filesize);

    // read read_permission bool
    bool read_permission;
    read_permission = binary_to_num(rom.contents[file_address+35].contents);

    // read write_permission bool
    bool write_permission;
    write_permission = binary_to_num(rom.contents[file_address+36].contents);

    // read read_password
    string read_password="";
    for(int i = file_address+37; i < file_address+47; i++){
        if (rom.contents[i].used == false){
            break;
        }
        read_password = read_password + binary_to_char(rom.contents[i].contents);
    }

    // read write_password
    string write_password="";
    for(int i = file_address+47; i < file_address+57; i++){
        if (rom.contents[i].used == false){
            break;
        }
        write_password = write_password + binary_to_char(rom.contents[i].contents);
    }

    file.setReadability(read_permission,read_password);
    file.setWritability(write_permission,write_password);

    // read file contents
    string file_content ="";
    for(int i = file_address+57; i < file_address+5000; i++){
        if (rom.contents[i].used == false){
            break;
        }
        file_content = file_content + binary_to_char(rom.contents[i].contents);
    }
    file.setContent(file_content);

    return file;
};


File copyFile(string path, ROM & rom){
    File file;
    file = openFile(path, rom);
    return file;
}

void pasteFile(string path, File file, ROM & rom){
    createFile(path, file, rom);
}

string RomUsage(ROM & rom){
    string usage;
    int current_size = rom_to_num(50,rom);
    double percent = double(current_size)/21000 *100;
    int percent_int = int(percent);
    usage = to_string(percent_int) + "%";
    return usage;
}
