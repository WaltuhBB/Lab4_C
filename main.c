#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Сжать файл
bool compress(FILE* data, FILE* res)
{
    bool check = false;
    
    if (data && res)
    {
        unsigned char buffer[8];
        int bytes_read = 1;

        unsigned char mask;

        while (bytes_read > 0)
        {
            bytes_read = fread(buffer, sizeof(unsigned char), 8, data);

            if (bytes_read == 8)
            {
                for (size_t i = 0; i < 7; i++)
                {
                    mask = (1 << 6) >> i;
                    mask = mask & buffer[7];
                    mask = mask << (i + 1);

                    buffer[i] = buffer[i] | mask;
                }

                fwrite(buffer, sizeof(unsigned char), 7, res);
            }
            else
            {
                fwrite(buffer, sizeof(unsigned char), bytes_read, res);
            }
        }

        check = true;
    }

    return check;
}

int main()
{
    FILE *ptrIn = fopen("test.txt", "r");
    FILE *ptrOut = fopen("res.txt", "w");

    compress(ptrIn, ptrOut);

    fclose(ptrIn);    
    fclose(ptrOut);

    return 0;
}
