#pragma once
/****************************************
Oct 11th, 2022
Patrick Wain

MorseDecoder.h
Header file containing common files and definitions
****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MORSE_LEN 32
#define NUL '\0'
#define UNDEFINED '~'

typedef struct morse_char MORSE;

extern MORSE* decode_char(MORSE* root, char morse_str[]);

extern MORSE* build_compare_tree();
extern MORSE* new_node(char morse_coded[], char decoded);
extern void get_morse_str(char morse[], int len, int index);
extern void my_add_node(MORSE* root, char morse_coded[], char decoded);

struct morse_char
{
	char morse_strn[MAX_MORSE_LEN];
	char morse_char;
	MORSE* next_dit;
	MORSE* next_dah;
};