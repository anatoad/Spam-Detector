#ifndef __STRING_PARSER_H__
#define __STRING_PARSER_H__

#include <string.h>
#include <stdio.h>

#define WORD_SEPARATORS " ,./!?\'\"*-:;"

int is_letter(char c);

int is_digit(char c);

char to_lowercase(char c);

int is_uppercase(char c);

int count_uppercase(char *string);

int is_whitespace(char c);

int count_characters(char *string);

int word_count(char *string);

int get_number(char *s);

void remove_whitespace(char *string);

#endif
