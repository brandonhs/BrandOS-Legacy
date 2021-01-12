#ifndef CLI_H
#define CLI_H

#include "../../cpu/ktypes.h"

void init_cli();

void user_input(char a, u8 event);
void send_command();

#endif