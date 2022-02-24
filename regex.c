#include "regex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// Function Definitions
RegExp *createRegExp(char *pattern)
{
    RegExp *regex = (RegExp *)malloc(sizeof(RegExp));
    if (!regex)
        return NULL;

    regex->pattern = (char *)malloc(strlen(pattern));
    if (!regex->pattern)
    {
        // Free regex first!
        free(regex);
        return NULL;
    }

    strcpy(regex->pattern, pattern);

    return regex;
}
void deleteRegExp(RegExp *regex)
{
    if (!regex)
        return;

    if (regex->pattern)
        free(regex->pattern);
    free(regex);
}

typedef struct
{
    int i;
    int pointer;
    char ch;
    char opr;
    int length;
} _RegExpOpr;

// . + *
int matchRegExp(RegExp *regex, char *test)
{
    // When match or pattern char is a dot, increment i and pointer and proceed.

    // When pattern char is a plus or star, decrement pointer (if pointer is negative, return 0), create entry on stack, then:
    // 1. if the created entry has a -1 (starting), then increment pointer until a different character is encountered, and note the length. Increment i and proceed.
    // 2. if the created entry has a non-negative value, then decrement the pointer and add the value to the pointer, and proceed.
    // 3. if the length is 0 for a star opr, or -1 (not starting) for star, pop the item from the stack and repeat the rule. If the stack is empty, return 0.

    // When mismatch:
    // 1. If the next pattern char is a star, simply increment i twice and proceed.
    // 2. Else, backtrack to the top of the stack (copy values), and repeat same steps as when the pattern char is a plus or star.
    // 3. If stack is empty, return 0.

    // When null character of the test is encountered and pattern still has characters, treat as mismatch.

    // When null character of the pattern is encountered and test still has characters, return 0.

    // When both pattern char and test char is a null char, return 1.

    Stack *stack = createStack();
    if (!stack)
        return -1;

    int i = 0, pointer = 0;
    int copyStackTop = 0;
    int status = 1;
    while (regex->pattern[i] != '\0' || test[pointer] != '\0')
    {
        if (copyStackTop) // Backtrack/Copy
        {
            int mustContinue = 0;

            if (!stack->length)
            {
                status = 0;
                break;
            }

            _RegExpOpr *data;
            if (!popStack(stack, (void **)&data))
            {
                status = -2;
                break;
            }

            i = data->i;
            pointer = data->pointer;

            if (data->length == -1)
            {
                if (copyStackTop == 1) // Starting
                {
                    int length = 1;
                    pointer++;
                    while (test[pointer] == data->ch || data->ch == '.' && test[pointer] != '\0')
                    {
                        pointer++;
                        length++;
                    }

                    if (length == 1 && test[pointer] == '\0' && data->opr == '+')
                    {
                        status = 1;
                        break;
                    }

                    data->length = length;
                    i++;

                    mustContinue = 1;
                }
                else
                {
                    status = 0;
                    break;
                }
            }
            else
            {
                data->length--;

                if ((data->length == 0 && data->opr == '+') || (data->length == -1 && data->opr == '*'))
                {
                    deleteStackData(data);

                    continue;
                }

                pointer += data->length;

                i++;
            }

            if (pushStack(stack, data, sizeof(_RegExpOpr)) != 0)
            {
                status = -2;
                break;
            }

            copyStackTop = 0;

            if (mustContinue)
                continue;
        }

        if (regex->pattern[i] == '+' || regex->pattern[i] == '*') // Plus or Star
        {
            if (--pointer < 0)
            {
                status = 0;
                break;
            }

            _RegExpOpr entry;
            entry.i = i;
            entry.pointer = pointer;
            if (i - 1 < 0)
            {
                status = 0;
                break;
            }

            entry.ch = regex->pattern[i - 1];
            entry.opr = regex->pattern[i];
            entry.length = -1;

            if (pushStack(stack, &entry, sizeof(_RegExpOpr)) != 0)
            {
                status = -2;
                break;
            }

            copyStackTop = 1;
        }
        else if (regex->pattern[i] == test[pointer] || regex->pattern[i] == '.' && test[pointer] != '\0') // Match
        {
            i++;
            pointer++;
        }
        else if (regex->pattern[i] != test[pointer] || (test[pointer] == '\0' && regex->pattern[i] != '\0')) // Mismatch
        {
            if (regex->pattern[i + 1] == '*')
            {
                i += 2;
                continue;
            }

            copyStackTop = 2;
            continue;
        }
        else if (regex->pattern[i] == '\0' && test[pointer] != '\0') // Pattern end
        {
            status = 0;
            break;
        }
    }

    deleteStack(stack);

    return status;
}