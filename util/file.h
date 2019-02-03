#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str{
    char string[255];
}str;


str *read_file(FILE *, str[], int);

#endif