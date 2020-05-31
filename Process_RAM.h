#ifndef File_RAM_H
#define File_RAM_H

#include <stdio.h>
#include "F_code_library.h"
#include "Header.h"
#include "File.h"
#include <ctime>

/*RAM当中的文件进程*/
class Process_File{
public:

    Process_File(File file, int inode_id, vector<RAM> &file_info);
    void readin_file(File file, int start_address, vector<RAM> &ana_ram);
    void readout_file(vector<RAM> &ana_ram);
    void delete_file(vector<RAM> &ana_ram);



public:

    RAM *ip;
    int size;
};


/*RAM当中的APP进程*/
class Process_APP{
public:
    Process_APP(vector<RAM> &ana_ram);
    void kill_Process_APP(vector<RAM> &ana_ram);

public:
    int address;

};

#endif // File_RAM_H
