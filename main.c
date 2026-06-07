#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Сжать файл
bool compress(char* file_in, char* file_out)
{
    bool check = false;

    if (file_in && file_out)
    {
        FILE *ptr_in = fopen(file_in, "r");
        FILE *ptr_out = fopen(file_out, "w");

        
    }

    return check;
}

int main()
{
    

    return 0;
}
