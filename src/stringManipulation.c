

#include "../headers/stringManipulation.h"

/* CUSTOM STRING OPERATIONS */
void copyStr(char *str, char *data)
{
    assert(str != NULL && data != NULL);

    int counter = 0;

    while (*(data + counter) != '\0')
    {
        *(str + counter) = *(data + counter);
        counter++;
    }

    *(str + counter) = '\0';
}

void concat(char *dest, char *first_str, char *second_str)
{
    assert(dest != NULL);
    assert(first_str != NULL);
    assert(second_str != NULL);

    copyStr(dest, first_str);

    char *walker = dest;

    while (*(walker) != '\0')
    {
        // this is coded this way to be more explicit, we could do +=1;
        walker = &(*(walker + 1));
    }

    copyStr(walker, second_str);
}
