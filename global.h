#ifndef GLOBAL_H
#define GLOBAL_H
#include "F_code_library.h"
#include "Process_RAM.h"
#include "Rom_system.h"
#include "Cl_ROM.h"
//define ram as a global variable, so that every widget can change it.
extern vector<RAM> ana_ram;
extern vector<ROM> ana_rom;
extern Process_APP snakeProcess;
extern Process_APP clockProcess;
extern Process_APP mineSweeperProcess;
extern Process_APP textEditorProcess;
extern bool endSnack;
extern bool endClock;
extern bool endMine;
extern bool endText;
extern bool hasClock;
extern int process_id_Snack;
extern int process_id_Clock;
extern int process_id_Mine;
extern int process_id_Text;
#endif // GLOBAL_H
