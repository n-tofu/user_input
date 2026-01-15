#include <stdio.h>
#include <stdlib.h>

#include "user_input.h"


int main(int argc, char *argv[])
{
    int int_value = 0;
    InputStatus is = get_int_input("Enter int", 1, 100, &int_value);
    if(is != SUCCESS)
    {
        fprintf(stderr, "%s\n", error_menu[is]);
        return EXIT_FAILURE;
    }

    printf("You entered the int value of: %d\n", int_value);

    return EXIT_SUCCESS;
}
