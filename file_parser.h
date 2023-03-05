#ifndef __FILE_PARSER_H__
#define __FILE_PARSER_H__

#include "detection.h"

int count_regular_files(char *directory_path);

void read(char *keywords, FILE *file);

int parse_spam_file(char *file_path, size *count, int **spam_score, char ***spam);

int parse_keywords_file(char *keywords_file, char *additional_file, size *count, char ***keywords);

void read_keywords(char **keywords, size count, FILE *file1, FILE *file2);

void get_keywords_count(size *count, FILE *keywords, FILE *additional);

#endif
