#include "Process_RAM.h"

using namespace std;


/*创建新文件*/
Process_File::Process_File(File file, int inode_id, vector<RAM> &file_info) {


    /***inode初始化***/
    cout << endl << "ip: " << ip << endl;
    ip = &file_info[inode_id];
    cout << "ip: " << ip << endl;
    cout << "&file_info[0]: " << &file_info[inode_id] << endl;
    (*ip).ram_used = 1;


    /*filename*/
    for(int i = 0; i <= int(file.getFilename().length()); i++){
        change_byte_by_char((*ip).contents[i], file.getFilename()[i]);
        (*ip).contents[i].show_contents(cout);
        if (i >= int(file.getFilename().size())-1)
            break;
    }

    /*time*/
    for(int i = 101; i <= 110; i++){
        change_byte_by_char((*ip).contents[i], file.getTime()[i-101]);
        (*ip).contents[i].show_contents(cout);
    }

    /*read permission*/
    change_byte_by_num((*ip).contents[51], file.isReadable());
    (*ip).contents[51].show_contents(cout);

    /*write permission*/
    change_byte_by_num((*ip).contents[52], file.isWritable());
    (*ip).contents[51].show_contents(cout);

    /*read password*/
    for(int i = 61; i <= 70; i++){
        change_byte_by_char((*ip).contents[i], file.getReadPassword()[i-61]);
        (*ip).contents[i].show_contents(cout);
    }

    /*write password*/
    for(int i = 71; i <= 80; i++){
        change_byte_by_char((*ip).contents[i], file.getReadPassword()[i-71]);
        (*ip).contents[i].show_contents(cout);
    }


}


/*文件具体内容录入*/
void Process_File::readin_file(File file, int start_address, vector<RAM> &ana_ram){

    /*Read the file address into inode & content into the block*/
    string s = file.getContent();
    size = s.size();
    int block_num = size/1024 + 1;
    int current = 0;
    cout << block_num << endl;
    for (int t = 201; t < 201+block_num*5; t = t+5){

        /*inode录入*/
        int keep = 1;
        cout << "address: " << start_address << endl;
        change_byte_by_num((*ip).contents[t+4], keep);
        int address_temp = start_address;
        change_byte_by_num((*ip).contents[t], address_temp);


        /*Block录入*/
        ana_ram[start_address].ram_used = 1;
        if (current < block_num-1){
            for(int i = 0; i < 1024; i++){
                change_byte_by_char(ana_ram[start_address].contents[i], s[i+current*1024]);
                ana_ram[start_address].remain -= 1;

            }
        }
        if (current == block_num-1){
            int sz = size-(block_num-1)*1024;
            for(int i = 0; i < sz; i++){
                change_byte_by_char(ana_ram[start_address].contents[i], s[i+current*1024]);
                ana_ram[start_address].remain -= 1;
            }
        }


        /*计数器*/
        start_address += 1;
        current += 1;
    }

    for (int t = 201; t <= 201+block_num*5; t++){
        (*ip).contents[t].show_contents(cout);
    }

}


void Process_File::readout_file(vector<RAM> &ana_ram){


    cout << "Here is the information stored in the RAM " << endl;
    cout << "The filename is: ";
    for(int i = 0; i < 40; ++i){
        cout << binary_to_char((*ip).contents[i].contents);
    }
    cout << endl <<"The creating time of this file is: ";
    for(int i = 101; i <= 125; ++i){
        cout << binary_to_char((*ip).contents[i].contents);
    }
    cout << endl << "The content of this file is: ";

    for (int t = 201; t < 1024; t = t+5){
        int keep = binary_to_num((*ip).contents[t+4].contents);
        if (keep == 0){
            break;
        }
        int address = binary_to_num((*ip).contents[t].contents);
        for(int i = 0; i < 1024; ++i){
            cout << binary_to_char(ana_ram[address].contents[i].contents);
        }
    }

    cout << endl;
}


void Process_File::delete_file(vector<RAM> &ana_ram){

    /*Delete actual content*/
    for (int t = 201; t < 1024; t = t+5){
        int keep = binary_to_num((*ip).contents[t+4].contents);
        if (keep == 0){
            break;
        }
        int address = binary_to_num((*ip).contents[t].contents);
        ana_ram[address].ram_used = 0;
        ana_ram[address].start();
    }

    /*Delete inode*/
    (*ip).ram_used = 0;
    (*ip).start();
    ip = NULL;

}

Process_APP::Process_APP(vector<RAM> &ana_ram){
    address = memory_allocation(2, ana_ram);
    for (int i = 0; i <=1; i++){
        ana_ram[address+i].ram_used = 1;
    }
}

void Process_APP::kill_Process_APP(vector<RAM> &ana_ram){
    for (int i = 0; i <=1; i++){
        ana_ram[address+i].ram_used = 0;
    }
}
