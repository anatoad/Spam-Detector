#ifndef __PATTERN_MATCHING_H__
#define __PATTERN_MATCHING_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string_parser.h"

int *compute_prefix(char *str);

int kmp(char *text, char *pattern);

int compare_char(char a, char b);

#endif
