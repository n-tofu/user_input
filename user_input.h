#ifndef UTIL_H
#define UTIL_H

// InputStatus and *error_menu[] in "util.c" must stay in sync
typedef enum
{
    SUCCESS = 0,            // 0
    ERR_READ,               // 1
    ERR_TOO_LONG,           // 2
    ERR_RANGE,              // 3
    ERR_NOT_NUM,            // 4
    ERR_GARBAGE,            // 5
    ERR_LIMITS,             // 6
    ERR_INFINITY,           // 7
    ERR_INVALID_PARAM,      // 8
    ERR_STR_EMPTY,          // 9
    ERR_MEMORY              // 10
} InputStatus;


extern const char *error_menu[];


enum 
{ 
    NUM_BUFFER  = 256,
    STR_BUFFER  = 1024 
};


InputStatus get_int_input(const char *prompt, int min, int max, int *rtn_val);
InputStatus get_float_input(const char *prompt, float min, float max, float *rtn_val);
InputStatus get_double_input(const char *prompt, double min, double max, double *rtn_val);
InputStatus get_string_input(const char *prompt, char **rtn_val); // caller must free()


#endif
