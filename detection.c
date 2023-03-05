#include "detection.h"

/* Parses the spammers file, saves information about the email addresses and
the score associated with each into the char **spam parameter. */
void get_spam_addresses(char **spam, int count, FILE *file, int *spam_score)
{
	char *pos = NULL;

	for (int i = 0; i < count; i++) {
		fgets(spam[i], MAX_LENGTH, file);

		pos = strchr(spam[i], ' ');
		if (pos)  {
			*pos = '\0';
			spam_score[i] = get_number(pos + 1);
		}
	}
}

/* Compute the standard deviation for each keyword. */
void compute_statistics(int **v, char **k, int count_k, int emails, int *ap, char *file_path)
{
	FILE *fp = fopen(file_path, "wt");
	if (!fp) return;

	int i = 0, j = 0;
	double ma = 0, stdev = 0;
	for (i = 0; i < count_k; i++) {
		ma = 0, stdev = 0;
		for (j = 0; j < emails; j++)
			ma += v[j][i];
		ma /= emails;

		for (j = 0; j < emails; j++)
			stdev += (v[j][i] - ma) * (v[j][i] - ma);

		stdev = sqrt(stdev / emails);

		fprintf(fp, "%s %d %f\n", k[i], ap[i], stdev);
	}

	fclose(fp);
}

/* Count the number of apparitions of every keyword. */
void get_keyword_aparitions(int *ap, size count, int **v)
{
	for (int i = 0; i < count.keywords; i++)
		for (int j = 0; j < count.emails; j++)
			ap[i] += v[j][i];
}

/* Returns 1 if file is a regular file, 0 otherwise. */
int is_regular_file(struct dirent *file)
{
	return (file->d_type == DT_REG && strncmp(file->d_name, ".", 1));
}

/* Parse the archive and get information about every email */
int get_info(size count, email *mail, int **v, char **sp, int *sc, char **keywords)
{
	DIR *directory = opendir(DIRECTORY_PATH);
	struct dirent *file = NULL;
	FILE *current_emailp = NULL;
	int caps = 0, nr;

	if (!directory) {
		printf("Could not open directory %s.\n", DIRECTORY_PATH);
		return 1;
	}

	for (int i = 0; i < count.emails; i++) {
		file = readdir(directory);
		if (!is_regular_file(file)) {
			i--;
			continue;
		}

		/* get the email index and file path */
		nr = get_number(file->d_name);
		char file_path[MAX_LENGTH] = "data/emails/", line[MAX_LENGTH];
		strncat(file_path, file->d_name, strlen(file->d_name));

		current_emailp = fopen(file_path, "rt");
		if (!current_emailp) {
			printf("Error trying to open file.");
			closedir(directory); return 1;
		}

		/* get the email address of the sender */
		while (fgets(line, MAX_LENGTH, current_emailp) && strncmp(line, "From:", 5));

		line[strlen(line) - 1] = '\0';

		char *address = strtok(line, " <\">");
		while (address && !strchr(address, '@'))
			address = strtok(NULL, " <\">");

		/* check if email address is known as a spammer */
		for (int j = 0; j < count.spams; j++)
			if (strncmp(address, sp[j], strlen(address)) == 0) {
				mail[nr].spam = sc[j];
				break;
			}

		/* parse the body of the email */
		while (fgets(line, MAX_LENGTH, current_emailp) && strncmp(line, "Body:", 5));

		strncpy(line, "     ", 5);

		caps = 0;

		/* count the apparitions of each keyword in the email body */
		do {
			line[strlen(line) - 1] = '\0';

			mail[nr].len += count_characters(line);
			caps += count_uppercase(line);

			for (int j = 0; j < count.total; j++)
				v[nr][j] += kmp(line, keywords[j]);

		} while (fgets(line, MAX_LENGTH, current_emailp));

		mail[nr].caps = caps;
		fclose(current_emailp);
	}

	closedir(directory);
	return 0;
}

/* Compute the average size of email bodies. */
double get_avg_size(email *mail, int count_emails)
{
	double avg_size = 0;

	for (int i = 0; i < count_emails; i++)
		avg_size += mail[i].len;

	avg_size /= count_emails;

	return avg_size;
}

double get_score(size count, email *mail, int **v, int e)
{
	double score = 0;

	for (int i = 0; i < count.total; i++)
		score += v[e][i];

	mail[e].count = score;
	score = score * count.avg_size / mail[e].len;

	return score;
}

void compute_predictions(email *mail, size count, char *file_path)
{
	FILE *fp = fopen(file_path, "wt");
	if (!fp) return;

	int caps, res;
	double score;

	for (int i = 0; i < count.emails; i++) {
		res = 0;
		caps = (mail[i].caps > mail[i].len / 2 || mail[i].caps > 1000);

		score = 10 * mail[i].score + 30.0 * caps + mail[i].spam;
		if (count.avg_size / mail[i].len > 3.5 && mail[i].len < 200)
			score = mail[i].count + 30.0 * caps + mail[i].spam;

		res = (score > 35);

		fprintf(fp, "%d\n", res);
	}

	fclose(fp);
}