#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Сжать файл
int compress(char* file_in, char* file_out)
{
    int res = -1;

    if (file_in && file_out)
    {
        FILE *ptr_in = fopen(file_in, "rb");
        FILE *ptr_out = fopen(file_out, "wb");

        if (!ptr_in || !ptr_out)
        {
            res = 1;
        }
        else
        {
            unsigned char buffer[8] = {0};
            
            size_t bytes_read = 0;
            size_t bytes_total = 0;

            int check_scanf = 1;

            res = 0;

            while (check_scanf == 1 && res == 0)
            {
                bytes_read = 0;

                //считываем по 8 байт
                for (size_t i = 0; i < 8; i++)
                {
                    check_scanf = fscanf(ptr_in, "%c", &buffer[i]);
                    
                    if (check_scanf == 1)
                    {
                        if (buffer[i] & (1 << 7))
                        {
                            res = 2;
                            i = 8;
                        }
                        else
                        {
                            bytes_read++;
                            bytes_total++;
                        }
                    }
                    else
                    {
                        i = 8;
                    }
                }

                if (res == 0 && bytes_read == 8)
                {
                    unsigned char mask = 1 << 6;
                    
                    //записываем по 7 байт
                    for (size_t i = 0; i < 7; i++)
                    {
                        if (mask & buffer[7])
                        {
                            buffer[i] = buffer[i] | (1 << 7);
                        }
                        
                        fprintf(ptr_out, "%c", buffer[i]);
                        
                        mask = mask >> 1;
                    }
                }
            }

            //записываем хвост
            if (res == 0 && bytes_read > 0 && bytes_read < 8)
            {
                for (size_t i = 0; i < bytes_read; i++)
                {
                    fprintf(ptr_out, "%c", buffer[i]);
                }    
            }

            fclose(ptr_in);
            fclose(ptr_out);
        }
    }

    return res;
}

int main()
{
    char file_in[20] = "test.txt";
    char file_out[20] = "res.txt";

    compress(file_in, file_out);

    return 0;
}
