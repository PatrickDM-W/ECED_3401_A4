/****************************************
Oct 11th, 2022
Patrick Wain

tree_support.c
support functions for tree
****************************************/

#include "MorseDecoder.h"
#define ONE_MORSE "ET"
#define TWO_MORSE "IANM"
#define THREE_MORSE "SURWDKGO"
#define FOUR_MORSE "HVF#L#PJBXCYZQ##"
#define FIVE_MORSE "54#3###2&#+####16=/###(#7###8#90"
#define SIX_MORSE "############?########.####@###'##-#########!#)#####,####:#######"

MORSE* build_compare_tree()
{
	/* basic node declarations */
	MORSE* root;
	MORSE* curr;
	char morse[MAX_MORSE_LEN];		//string to get morse encoded value

	/* 
	- build root node 
	- root node is not used, it acts as a "sentinal node"
	*/
	root = new_node("ROOT", UNDEFINED);
	
	/* add One Lengths to the tree */
	for (int i = 0; i < strlen(ONE_MORSE); i++)
	{
		get_morse_str(morse, strlen(ONE_MORSE), i);			//modify morse with current code
		curr = new_node(morse, ONE_MORSE[i]);				//build new node with code and char

		if (morse[0] == '.')
			root->next_dit = curr;		//E added as first dit
		else if (morse[0] == '-')
			root->next_dah = curr;		//T added as first dah
	}

	/* add subsequents */
	for (int i = 0; i < strlen(TWO_MORSE); i++)				//runs down defined TWO_MORSE string
	{
		get_morse_str(morse, strlen(TWO_MORSE), i);			//modify morse

		/* add new node with morse as encoded string, index of X_MORSE as decoded char */
		my_add_node(root, morse, TWO_MORSE[i]);
	}

	for (int i = 0; i < strlen(THREE_MORSE); i++)
	{
		get_morse_str(morse, strlen(THREE_MORSE), i);

		my_add_node(root, morse, THREE_MORSE[i]);
	}

	for (int i = 0; i < strlen(FOUR_MORSE); i++)
	{
		get_morse_str(morse, strlen(FOUR_MORSE), i);

		my_add_node(root, morse, FOUR_MORSE[i]);
	}

	for (int i = 0; i < strlen(FIVE_MORSE); i++)
	{
		get_morse_str(morse, strlen(FIVE_MORSE), i);

		my_add_node(root, morse, FIVE_MORSE[i]);
	}

	for (int i = 0; i < strlen(SIX_MORSE); i++)
	{
		get_morse_str(morse, strlen(SIX_MORSE), i);

		/* 
		- " is hardcoded because I do not
		- know how to include " in a string
		- definition
		*/
		if (strcmp(morse, ".-..-.") == 0)
			my_add_node(root, morse, '"');
		else
			my_add_node(root, morse, SIX_MORSE[i]);
	}

	return root;
}

MORSE* new_node(char morse_coded[], char decoded)
{
	/* 
	- create a new node for the tree
	- return NULL if malloc() fails
	- return node otherwise
	- code provided by Dr. Hughes
	*/

	MORSE* new;

	if ((new = malloc(sizeof(MORSE))) == NULL)
		return NULL;

	/* Update data and links */
	strcpy_s(new->morse_strn, MAX_MORSE_LEN, morse_coded);
	new->morse_char = decoded;
	new->next_dit = NULL;
	new->next_dah = NULL;
	return new;
}

void get_morse_str(char morse_str[], int len, int index)
{
	int morse_len = log2(len);
	int val = index;

	for (int i = morse_len; i > 0; i--)
	{
		if (val % 2)
			morse_str[i-1] = '-';
		else
			morse_str[i-1] = '.';

		val /= 2;
	}

	morse_str[morse_len] = NUL;

	return;
}

void my_add_node(MORSE* root, char morse_coded[], char decoded)
{
	/* for node traversal */
	MORSE* curr = root;
	MORSE* prev = root;
	int i = 0;

	while (curr != NULL)
	{
		prev = curr;
		if (morse_coded[i] == '.')
			/*
			- current pulse of passed string is .
			- go to next dit
			*/
			curr = curr->next_dit;
		else if (morse_coded[i] == '-')
			/*
			- current pulse of passed string is -
			- go to next dah
			*/
			curr = curr->next_dah;

		i++;
	}
	/* curr == NULL */
	if (morse_coded[i - 1] == '.')		//add to dit location
		prev->next_dit = new_node(morse_coded, decoded);
	else if (morse_coded[i - 1] == '-')	//add to dah location
		prev->next_dah = new_node(morse_coded, decoded);

	return;
}

MORSE* decode_char(MORSE* root, char morse_str[])
{
	MORSE* curr = root;

	for (int i = 0; i < strlen(morse_str) + 1; i++)
	{
		if (curr == NULL)				//match was never found
			return root;
		if (strcmp(curr->morse_strn, morse_str) == 0)
			return curr;

		if (morse_str[i] == '.')
		{
			curr = curr->next_dit;
		}
		else if (morse_str[i] == '-')
		{
			curr = curr->next_dah;
		}
	}
}