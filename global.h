/*
 * @FrankFAN@
 */

#ifndef GLOBAL_H
#define GLOBAL_H
#include "F_code_library.h"
#include "Process_RAM.h"
#include "Rom_system.h"
#include "Cl_ROM.h"
//define ram as a global variable, so that every widget can change it.
extern vector<RAM> ana_ram;
//define rom as a global variable
extern vector<ROM> ana_rom;

extern Process_APP snakeProcess;
extern Process_APP editorProcess;


#endif // GLOBAL_H
