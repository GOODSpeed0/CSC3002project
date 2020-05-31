/*
 * This file initialize the global variables,
 * so that different widgets can change the same variable.
 * @FrankFAN@
 */


#include "global.h"
#include "F_code_library.h"

vector<RAM> ana_ram = build_RAM(20);
Process_APP snakeProcess = Process_APP(ana_ram);
Process_APP editorProcess = Process_APP(ana_ram);

vector<ROM> ana_rom = build_ROM(20);

