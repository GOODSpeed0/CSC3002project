#ifndef EXCEPTIONSYSTEM_H
#define EXCEPTIONSYSTEM_H

#include <iostream>
#include <exception>
#include <string>
#include <cstring>
#include "Cl_ROM.h"
#include "Rom_system.h"

using namespace std;

//void TestExceptionSystem();


/**************** input exception: especially for Chinese character ******************/

class inputException:public exception{
public:
    const char * what() const throw(){
        return "ERROR! Invalid input format. Please enter again!\n";
    }
};

// if the input contains Chinese characters, OS will report an error.
void check_input(char *str) throw(inputException){
    char c;
    while(c =*str++)
    {
       if( (c&0x80) && (*str & 0x80) )
       {
           throw inputException();
           break;
       }
    }
}

string getValidInput() throw(inputException){
    while(true){
        try{
            // convert string_input to char_input
            cout << "Please enter: " << endl;
            string input;
            cin >> input;
            int input_size = input.length();
            char c[input_size];
            strcpy(c,input.c_str());

            // check input
            check_input(c);

            // if valid, directly return input
            return input;
            break;
        }
        catch(inputException& e)
        {
            cout << e.what();
        }
    }
}

/********************** File class exception ********************************/

// file name length
class fileNameException:public exception{
public:
    const char * what() const throw(){
        return "Error! Length of file name is out of range. Please enter again!";
    }
};


void checkFileName(string file_name){
    if (file_name.size()>10){
        throw fileNameException();
    }
}

string enterFileName(){
    while(true){
        try{
            // convert string_input to char_input
            cout << "Please enter file name: " << endl;
            string input;
            cin >> input;
            int input_size = input.length();
            char c[input_size];
            strcpy(c,input.c_str());

            // check input format
            check_input(c);

            // check file name length
            checkFileName(input);

            return input;
            break;
        }
        catch(inputException& e)
        {
            cout << e.what();
        }
        catch(fileNameException& f){
            cout << f.what();
        }
    }
}


// file content size
class fileContentException:public exception{
public:
    const char * what() const throw(){
        return "Error! Length of file content is out of range. Please enter again!";
    }
};

void checkFileContent(string content){
    if (content.length()>4943){
        throw fileContentException();
    }
}

string enterFileContent(){
    while(true){
        try{
            // convert string_input to char_input
            cout << "Please enter file content: " << endl;
            string input;
            cin >> input;
            int input_size = input.length();
            char c[input_size];
            strcpy(c,input.c_str());

            // check input format
            check_input(c);

            // check file content length
            checkFileContent(input);

            return input;
            break;
        }
        catch(inputException& e)
        {
            cout << e.what();
        }
        catch(fileContentException& f){
            cout << f.what();
        }
    }

}


// password exception (including write and read password)
class filePasswordException:public exception{
public:
    const char * what() const throw(){
        return "Error! Length of file password is out of range. Please enter again!";
    }
};


void checkFilePassword(string file_password){
    if (file_password.size()>10){
        throw filePasswordException();
    }
}

string enterFilePassword(){
    while(true){
        try{
            // convert string_input to char_input
            cout << "Please enter file password: " << endl;
            string input;
            cin >> input;
            int input_size = input.length();
            char c[input_size];
            strcpy(c,input.c_str());

            // check input format
            check_input(c);

            // check file name length
            checkFilePassword(input);

            return input;
            break;
        }
        catch(inputException& e)
        {
            cout << e.what();
        }
        catch(filePasswordException& f){
            cout << f.what();
        }
    }
}

/********************** Rom system exception ********************************/

//path length exception
class pathLengthException:public exception{
public:
    const char * what() const throw(){
        return "Error! Length of path is out of range. You cannot create more in this folder.";
    }
};


void checkPathException(string path){
    if (path.size()>30){
        throw pathLengthException();
    }
}

// folder capacity
class folderCapacityException:public exception{
public:
    const char * what() const throw(){
        return "Error! One folder can only contain no more than two docements. You cannot create more in this folder.";
    }
};

void checkFolderCapacity(string path, ROM & rom){
    int super_address = getAddress(path,rom);
    if (rom.contents[super_address+55].used == true){
        throw folderCapacityException();
    }
}


// to test create folder/document/App
string enterPathName(string path, ROM & rom){
    try{
        // check folder capacity firstly
        checkFolderCapacity(path,rom);

        // convert string_input to char_input
        cout << "Please enter foldername: " << endl;
        string input;
        cin >> input;
        int input_size = input.length();
        char c[input_size];
        strcpy(c,input.c_str());

        // check input format
        check_input(c);

        // check path length
        string folder_path;
        folder_path = path + input + "\\";

        checkPathException(folder_path);

        return input;

        // if above are all satisfied, user can create folder or file
        // createFolder
        // createFile

    }
    catch(inputException& e)
    {
        cout << e.what();
        return "None";
    }
    catch(pathLengthException& f){
        cout << f.what();
        return "None";

    }
    catch(folderCapacityException& g){
        cout << g.what();
        return "None";
    }
}

// rom size exception

class romSizeWarning:public exception{
public:
    const char * what() const throw(){
        return "Warning! This disk is about to hit its ceiling.\n";
    }
};

class romSizeException:public exception{
public:
    const char * what() const throw(){
        return "Error! This disk memory is up to its limit.\n You cannot create more files in this disk.";
    }
};

//after creating file (size warning in advance)
void checkDiskSize(ROM & rom){
    int current_size = rom_to_num(50,rom);
    if (current_size > 20000 && current_size < 21000){
        throw romSizeWarning();
    }
}

// before create file
void checkDiskSize2(ROM & rom){
    int current_size = rom_to_num(50,rom);
    if (current_size > 20000 && current_size < 21000){
        throw romSizeException();
    }
}

 /********************** Ram system exception ********************************/

class ramFullException:public exception{
public:
    const char * what() const throw(){
        return "Warning! Ram is about to use up.\n";
    }
};

void checkRamSize(int length, vector<RAM> ana_ram){
    int index = memory_allocation(length, ana_ram);
    if (index == -1){
        throw ramFullException();
    }
}



#endif // EXCEPTIONSYSTEM_H
