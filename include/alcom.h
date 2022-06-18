#ifndef ALCOM_HEADER_CLOWZED
#define ALCOM_HEADER_CLOWZED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//? Here are colors for stdout
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define RESET   "\x1B[0m"

//? Simple defines for colored output
#define info    printf(BLUE    "what? : " RESET);
#define warning printf(YELLOW  "hm... : " RESET);
#define done    printf(GREEN   "woho! : " RESET);
#define error   printf(RED     "nooo! : " RESET);

//? Functions prototypes for -Weverything flag

ssize_t comment_splitter_position(const char * line);
size_t find_longest_line_without_comment(const char * filename);

bool line_has_comment(const char * line);
bool line_is_empty(const char * line);

void align_asm_file(char * filename);

#endif
