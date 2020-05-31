#include "File.h"

using namespace std;

File::File(){
    filename = "report";
    content = "Hello, Mr.HUANG!";
    time = "2020.5.16";
    size = content.size();
    read_permission = true;
    write_permission = true;
    read_password = "37";
    write_password = "37";

}

File::File(string filename, string content){
    this->filename = filename;
    this->content = content;
    size = content.size();
    read_permission = true;
    write_permission = true;
    read_password = "37";
    write_password = "37";
}

void File::setName(string filename){
    this->filename = filename;
}

void File::setTime(string time){
    this->time = time;
}

//void File::setSize(int size){
//    this->size = size;
//}

void File::setContent(string content){
    this->content = content;
    this->size = content.size();

};

void File::setReadability(bool permission, string password){
    read_permission = permission;
    read_password = password;
}

void File::setWritability(bool permission, string password){
    write_permission = permission;
    write_password = password;
}


string File::getFilename(){
    return filename;
}

string File::getTime(){
    return time;
}

string File::getContent(){
    return content;
}

int File::getSize(){
    return size;
}

string File::getReadPassword(){
    return read_password;
}

string File::getWritePassword(){
    return write_password;
}

bool File::isReadable(){
    return read_permission;
}


bool File::isWritable(){
    return write_permission;
}
