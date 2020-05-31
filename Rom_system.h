#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include "Header.h"

#include "Cl_Byte.h"
#include "Cl_RAM.h"

#include "Cl_ROM.h"
#include "File.h"

void initial_rom(ROM &rom, string diskname);

void createFolder(string path, string folderName, ROM & rom);

int getAddress(string path, ROM &rom);
int getAllAddress(ROM & rom, vector<int> & vec, int pointer=10);

void createFile(string path, File file, ROM & rom);

void createApp(string path, string AppName, ROM & rom);

void DeleteFile(string path, ROM & rom);
void DeleteApp(string path, ROM & rom);
int findHole(ROM & rom);

vector<string> openFolder(string path, ROM & rom);
File openFile(string path, ROM & rom);

File copyFile(string path, ROM & rom);
void pasteFile(string path, File file, ROM & rom);

string RomUsage(ROM & rom);

#endif // FILE_SYSTEM_H
