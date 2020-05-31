#include "global.h"
#include "F_code_library.h"

vector<RAM> ana_ram = build_RAM(20);
vector<ROM> ana_rom = build_ROM(20);
Process_APP snakeProcess = Process_APP(ana_ram);
Process_APP clockProcess=Process_APP(ana_ram);
Process_APP mineSweeperProcess=Process_APP(ana_ram);
Process_APP textEditorProcess=Process_APP(ana_ram);
bool endSnack=false;
bool endClock=false;
bool endMine=false;
bool endText=false;
bool hasClock=false;
int process_id_Snack;
int process_id_Clock;
int process_id_Mine;
int process_id_Text;
