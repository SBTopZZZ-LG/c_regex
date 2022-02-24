#include <stdio.h>
#include "regex.h"

int main()
{
    RegExp *regex1 = createRegExp("a.*bc*.*z");
    if (matchRegExp(regex1, "absadasdzz") == 1)
        printf("1: Match!\n");
    else
        printf("1: Matchn't!\n");

    RegExp *regex2 = createRegExp("a.+bc");
    if (matchRegExp(regex2, "azybc") == 1)
        printf("2: Match!\n");
    else
        printf("2: Matchn't!\n");

    RegExp *regex3 = createRegExp("a*.+c");
    if (matchRegExp(regex3, "aaaazbc") == 1)
        printf("3: Match!\n");
    else
        printf("3: Matchn't!\n");

    RegExp *regex4 = createRegExp("a+aa+ss");
    if (matchRegExp(regex4, "aaaass") == 1)
        printf("4: Match!\n");
    else
        printf("4: Matchn't!\n");

    RegExp *regex5 = createRegExp(".+@.+");
    if (matchRegExp(regex5, "sbtopzzz@") == 1)
        printf("5: Match!\n");
    else
        printf("5: Matchn't!\n");

    deleteRegExp(regex1);
    deleteRegExp(regex2);
    deleteRegExp(regex3);
    deleteRegExp(regex4);
    deleteRegExp(regex5);
    return 0;
}