#ifndef __DETECTION_H__
#define __DETECTION_H__

#include "utils.h"

void get_keyword_aparitions(int *ap, size count, int **v);

void compute_statistics(int **v, char **k, int count_k, int emails, int *ap, char *file_path);

double get_avg_size(email *mail, int count_emails);

double get_score(size count, email *mail, int **v, int e);

void get_spam_addresses(char **spam, int count, FILE *file, int *spam_score);

void compute_predictions(email *mail, size count, char *file_path);

int get_info(size count, email *mail, int **v, char **sp, int *sc, char **k);

#endif