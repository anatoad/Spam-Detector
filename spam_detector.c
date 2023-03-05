#include "utils.h"
#include "file_parser.h"
#include "detection.h"

int main(void)
{
	int stop = 0, res;
	int *spam_score = NULL;
	char **spam = NULL, **keywords = NULL;
	size count;

	/* get the number of emails in the directory */
	count.emails = count_regular_files(DIRECTORY_PATH);

	/* parse the information from the spammers file */
	res = parse_spam_file(SPAMMERS_FILE_PATH, &count, &spam_score, &spam);
	if (res < 0) return -1;
	
	/* parse the information from the keywords file */
	res = parse_keywords_file(KEYWORDS_FILE_PATH, ADDITIONAL_FILE_PATH, &count, &keywords);
	if (res < 0) return -1;

	int *ap = calloc(count.keywords, sizeof(int));
	int **v = (int **) calloc_matrix(count.emails, count.total, sizeof(int));
	email *mail = calloc(count.emails, sizeof(email));

	stop = get_info(count, mail, v, spam, spam_score, keywords);

	if (!stop) {  /* if errors have not occured */
		count.avg_size = get_avg_size(mail, count.emails);

		get_keyword_aparitions(ap, count, v);

		for (int i = 0; i < count.emails; i++)
			mail[i].score = get_score(count, mail, v, i);

		compute_statistics(v, keywords, count.keywords, count.emails, ap, STATISTICS_FILE_PATH);

		compute_predictions(mail, count, PREDICTION_FILE_PATH);
	}

	/* free memory */
	free(spam_score);
	free(ap);
	free(mail);
	free_matrix((void **) v, count.emails, sizeof(int));
	free_matrix((void **) keywords, count.total, sizeof(char));
	free_matrix((void **) spam, count.spams, sizeof(char));

	return 0;
}
