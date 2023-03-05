#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <dirent.h>

#include "string_parser.h"
#include "pattern_matching.h"

#define DIRECTORY_PATH "data/emails"
#define KEYWORDS_FILE_PATH "data/keywords"
#define ADDITIONAL_FILE_PATH "additional_keywords"
#define SPAMMERS_FILE_PATH "data/spammers"
#define STATISTICS_FILE_PATH "statistics.out"
#define PREDICTION_FILE_PATH "prediction.out"

#define MAX_KEYWORD_LENGTH 10000
#define MAX_LENGTH 10000

typedef struct email {
	int len;				/* email length (number of characters) */
	int count;				/* keywords score */
	int caps;				/* number of uppercase letters in the email body */
	int spam;				/* spammers file score */
	double score;			/* email spam score */
} email;

typedef struct size {
	int emails;				/* total number of emails */
	int keywords;			/* number of keywords in the keywords file */
	int additional;			/* number of keywords in the additional_keywords file */
	int total;				/* total number of keywords in all files */
	int spams;				/* total number of spam email addresses */
	double avg_size;		/* average size of email body (no of characters) */
} size;

void **calloc_matrix(int rows, int columns, size_t size);

void free_matrix(void **matrix, int rows, size_t size);

#endif