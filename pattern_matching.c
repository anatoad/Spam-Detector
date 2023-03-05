#include "pattern_matching.h"

/* Preprocessing: computes the largest prefix that is also a suffix in given string. */
int *compute_prefix(char *str)
{
    int j = 0, i = 1;
    int n = strlen(str) - 1;

    int *p = calloc(n, sizeof(int));
    if (!p) return NULL;

    while (i < n) {
        if (compare_char(str[i], str[j])) {
            p[i] = j+1;
            i++; j++;
        } else {
            if (j == 0) {
                p[i] = 0;
                i++;
            } else {
                j = p[j-1];
            }
        }
    }

    return p;
}

/* Returns the number of apparitions of pattern as a substring in text, using the
   Knuth-Morris-Pratt (KMP) pattern matching algorithm */
int kmp(char *text, char *pattern) {
    int m = strlen(text);
    int n = strlen(pattern);

    int i = 0, j = 0;
    int count = 0;

    int *p = compute_prefix(pattern);

    while(i < m) {
        if (compare_char(text[i], pattern[j])) {
            if (j == n-1) {
                count++;

                j = p[j-1];
            } else {
                i++; j++;
            }
        } else {
            while (j > 0 && !compare_char(text[i], pattern[j]))
                j = p[j-1];
            
            if (compare_char(text[i], pattern[j]))
                j++;
            i++;
        }
    }
    
    free(p);

    return count;
}

/* Case insensitive character comparison. */
int compare_char(char a, char b)
{
	if (is_letter(a) && is_letter(b)) {
		a = to_lowercase(a);
		b = to_lowercase(b);
	}

	return (a == b);
}
