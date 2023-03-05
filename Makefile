CC = gcc
FLAGS = -Wall -Wextra -g

.PHONY: build

build: spam_detector

spam_detector: spam_detector.c utils.o string_parser.o file_parser.o pattern_matching.o detection.o
	$(CC) $(FLAGS) $^ -o $@ -lm

utils.o: utils.c utils.h string_parser.h pattern_matching.h
	$(CC) $(FLAGS) -c $< -o $@ -lm

string_parser.o: string_parser.c string_parser.h
	$(CC) $(FLAGS) -c $< -o $@

file_parser.o: file_parser.c file_parser.h
	$(CC) $(FLAGS) -c $< -o $@

pattern_matching.o: pattern_matching.c pattern_matching.h
	$(CC) $(FLAGS) -c $< -o $@

detection.o: detection.c detection.h
	$(CC) $(FLAGS) -c $< -o $@

run:
	./spam_detector

.PHONY: clean
clean:
	rm -rf *.o spam_detector
