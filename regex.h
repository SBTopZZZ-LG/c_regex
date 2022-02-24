#ifndef REGEX_H
#define REGEX_H

// Structures

typedef struct
{
    char *pattern;
} RegExp;

// Function Declarations

RegExp *createRegExp(char *);
void deleteRegExp(RegExp *);

int matchRegExp(RegExp *, char *);

#endif