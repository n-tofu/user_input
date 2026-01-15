#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#include "user_input.h"


// InputStatus in "util.h" and *error_menu[] must stay in sync
const char *error_menu[] = 
{
    "Success",                                          // 0
    "Error: Could not read input.",                     // 1
    "Error: Input exceeds buffer limit.",               // 2
    "Error: Value out of integer range.",               // 3
    "Error: No valid numeric input found.",             // 4
    "Error: Invalid characters detected.",              // 5
    "Error: Value outside of requested range.",         // 6
    "Error: Value must be a finite number.",            // 7
    "Error: Invaild parameters passed.",                // 8    
    "Error: String is empty.",                          // 9
    "Error: Error while trying to allocate memory."     // 10
};


/******************************************************************************
 * get_int_input() -> IntStatus
 *****************************************************************************/
InputStatus get_int_input(const char *prompt, int min, int max, int *rtn_val)
{
    if(prompt == NULL || rtn_val == NULL) 
        return ERR_INVALID_PARAM;

    char buffer[NUM_BUFFER] = {0};
    char *endptr = NULL;
    long value = 0;
    *rtn_val = 0;

    printf("%s: ", prompt);
    fflush(stdout);

    if(!fgets(buffer, sizeof(buffer), stdin))
        return ERR_READ;

    if(!strchr(buffer, '\n') && !feof(stdin))
        return ERR_TOO_LONG;

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if(errno == ERANGE || value < INT_MIN || value > INT_MAX)
        return ERR_RANGE;

    if(endptr == buffer)
        return ERR_NOT_NUM;

    while(isspace((unsigned char)*endptr))
        endptr++;

    if(*endptr != '\0' && *endptr != '\n')
        return ERR_GARBAGE;

    if(value < min || value > max)
        return ERR_LIMITS;

    *rtn_val = (int)value;

    return SUCCESS;
}


/******************************************************************************
 * get_float_input() -> float
 *****************************************************************************/
InputStatus get_float_input(const char *prompt, float min, float max, float *rtn_val)
{
    if(prompt == NULL || rtn_val == NULL) 
        return ERR_INVALID_PARAM;

    char buffer[NUM_BUFFER] = {0};
    char *endptr = NULL;
    float value = 0.0f;

    printf("%s: ", prompt);
    fflush(stdout);

    if(!fgets(buffer, sizeof(buffer), stdin))
        return ERR_READ;

    if(!strchr(buffer, '\n') && !feof(stdin))
        return ERR_TOO_LONG;

    errno = 0;
    value = strtof(buffer, &endptr);

    if(errno == ERANGE)
        return ERR_RANGE;

    if(endptr == buffer)
        return ERR_NOT_NUM;

    while(isspace((unsigned char)*endptr))
        endptr++;

    if(*endptr != '\0' && *endptr != '\n')
        return ERR_GARBAGE;

    if(!isfinite(value))
        return ERR_INFINITY;

    if(value < min || value > max)
        return ERR_LIMITS;

    *rtn_val = value;

    return SUCCESS;
}


/******************************************************************************
 * get_double_input() -> double
 *****************************************************************************/
InputStatus get_double_input(const char *prompt, double min, double max, double *rtn_val)
{
    if(prompt == NULL || rtn_val == NULL) 
        return ERR_INVALID_PARAM;

    char buffer[NUM_BUFFER] = {0};
    char *endptr = NULL;
    double value = 0.0;


    printf("%s: ", prompt);
    fflush(stdout);

    if(!fgets(buffer, sizeof(buffer), stdin))
        return ERR_READ;

    if(!strchr(buffer, '\n') && !feof(stdin))
        return ERR_TOO_LONG;

    errno = 0;
    value = strtod(buffer, &endptr);

    if(errno == ERANGE)
        return ERR_RANGE;

    if(endptr == buffer)
        return ERR_NOT_NUM;

    while(isspace((unsigned char)*endptr))
        endptr++;

    if(*endptr != '\0' && *endptr != '\n')
        return ERR_GARBAGE;

    if(!isfinite(value))
        return ERR_INFINITY;

    if(value < min || value > max)
        return ERR_LIMITS;

    *rtn_val = value;
    
    return SUCCESS;
}


/******************************************************************************
 * get_string_input() -> char*
 *****************************************************************************/
InputStatus get_string_input(const char *prompt, char **rtn_val)
{
    if(prompt == NULL || rtn_val == NULL) 
        return ERR_INVALID_PARAM;

    char buffer[STR_BUFFER] = {0};

    printf("%s: ", prompt);
    fflush(stdout);

    if(!fgets(buffer, sizeof(buffer), stdin))
        return ERR_READ;

    char *newline = strchr(buffer, '\n');
    if (newline)
        *newline = '\0';
    else 
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (ch != EOF)
            return ERR_TOO_LONG;
    }

    char *start = buffer;
    while(isspace((unsigned char)*start))
        start++;

    size_t len = strlen(start);
    if(len == 0)
        return ERR_STR_EMPTY;
    
    char *end = start + len - 1;
    while(end > start && isspace((unsigned char)*end))
        *end-- = '\0';

    len = strlen(start);

    *rtn_val = malloc(len + 1);
    if(*rtn_val == NULL)
        return ERR_MEMORY;

    memcpy(*rtn_val, start, len + 1);

    return SUCCESS;
}
