#pragma once

#include "MorseDecoder.h"

struct morse_char
{
	char morse_strn[MAX_MORSE_LEN];
	morse_char* next_dah;
	morse_char* next_dih;

};