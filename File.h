#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include "F_code_library.h"

class File{
public:
    File();
    File(string filename, string content);
    void setTime(string time);
    void setName(string filename);
    void setContent(string content);
//    void setSize(int size);
    void setReadability(bool permission, string password="37");
    void setWritability(bool permission, string password="37");

    string getFilename();
    string getTime();
    string getContent();
    int getSize();
    string getReadPassword();
    string getWritePassword();
    bool isReadable();
    bool isWritable();

private:

    string filename; // <= 10 bytes!!!
    string time; // <= 20 bytes!!!
    string content; // <= 4943 bytes!!!
    int size;
    bool read_permission;
    bool write_permission;
    string read_password; // <= 10 bytes!!!
    string write_password; // <= 10 bytes!!!
};


#endif // FILESYSTEM_H
