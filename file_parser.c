#include "file_parser.h"

/* Returns the number of regular files in given directory. */
int count_regular_files(char *directory_path)
{
	/* open directory stream */
	DIR *directory = opendir(directory_path);
	if (!directory) return 0;
	
	int count = 0;

    /* get the first directory entry */
	struct dirent *file = readdir(directory);

	while (file) {
		if (file->d_type == DT_REG)
			count++;

        /* get the next directory entry */
		file = readdir(directory);
	}

	/* close directory stream */
	closedir(directory);

	return count;
}

/* Read keywords from input files. */
void read_keywords(char **keywords, size count, FILE *file1, FILE *file2)
{
	for (int i = 0; i < count.keywords; i++)
		read(keywords[i], file1);

	for (int i = 0; i < count.additional; i++)
		read(keywords[count.keywords + i], file2);
}

/* Parse the information from the spammers file. */
int parse_spam_file(char *file_path, size *count, int **spam_score, char ***spam) {
	FILE *spam_file = fopen(file_path, "rt");
	if (!spam_file) return -1;

	fscanf(spam_file, "%d", &count->spams);
	fgetc(spam_file);
	
	*spam_score = calloc(count->spams, sizeof(int));
	if (!(*spam_score)) return -1;

	*spam = (char **) calloc_matrix(count->spams, MAX_LENGTH, sizeof(char));
	if (!(*spam)) return -1;

	get_spam_addresses(*spam, count->spams, spam_file, *spam_score);

	fclose(spam_file);

	return 0;
}

/* Parse the information from the keywords file. */
int parse_keywords_file(char *keywords_file, char *additional_file, size *count, char ***keywords)
{
	FILE *fp_keywords = fopen(keywords_file, "rt");
	if (!fp_keywords) return -1;

	FILE *fp_additional = fopen(additional_file, "rt");
	if (!fp_additional) {
		fclose(fp_keywords); return -1;
	}

	get_keywords_count(count, fp_keywords, fp_additional);

	*keywords = (char **) calloc_matrix(count->total, MAX_KEYWORD_LENGTH, sizeof(char));

	read_keywords(*keywords, *count, fp_keywords, fp_additional);

	fclose(fp_keywords);
	fclose(fp_additional);

	return 0;
}

void get_keywords_count(size *count, FILE *keywords_file, FILE *additional_file)
{
	fscanf(keywords_file, "%d", &count->keywords);
	fscanf(additional_file, "%d", &count->additional);

	fgetc(keywords_file);
	fgetc(additional_file);

	count->total = count->keywords + count->additional;
}

void read(char *keywords, FILE *file)
{
	fgets(keywords, MAX_KEYWORD_LENGTH, file);
	remove_whitespace(keywords);
}
