#include "string_parser.h"

int is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int is_whitespace(char c)
{
    return !(c >= 33 && c <= 125);
}

char to_lowercase(char c)
{
    return (c >= 'a' && c <= 'z') ? c : c + 'a' - 'A';
}

int is_uppercase(char c)
{
    return (is_letter(c) && c != to_lowercase(c));
}

int count_uppercase(char *string)
{
	int count = 0, size = (int)strlen(string);

	for (int i = 0; i < size; i++)
		if (is_uppercase(string[i]))
			count++;

	return count;
}

int count_characters(char *string)
{
	int i = 0, size = strlen(string), count = 0;

	for (i = 0 ; i < size; i++)
		if (!is_whitespace(string[i]))
			count++;
        
	return count;
}

int word_count(char *string)
{
	int count = 0, size, i;
	char *p = strtok(string, WORD_SEPARATORS);

	while (p) {
		count++;
        size = strlen(p);
		for (i = 0; i < size; i++)
			if (!is_letter(string[i])) {
				count--;
				break;
			}

		p = strtok(NULL, WORD_SEPARATORS);
	}

	return count;
}

int get_number(char *s)
{
	int i = 0, nr = 0;

	while (is_digit(s[i]))
		nr = nr * 10 + s[i++] - '0';

	return nr;
}

void remove_whitespace(char *string)
{
	int size = strlen(string);

	while (size > 0 && (string[size - 1] == '\n' || string[size - 1] == ' '))
		size--;

	string[size] = '\0';
}
