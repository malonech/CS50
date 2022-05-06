#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include<ctype.h>

int main(int argc, string key[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int n = strlen(key[1]);

        if (n != 26)                                    //All key's past this stage are 26 characters in length
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if ((key[1][i] >= 'A' && key[1][i] <= 'Z') || (key[1][i] >= 'a' && key[1][i] <= 'z'))
                {
                    for (int g = 0; g < n; g++)
                    {
                        if (i == g)
                        {
                            continue;
                        }
                        else if (key[1][i] == key[1][g])
                        {
                            printf("Usage: ./substitution key\n");
                            return 1;
                        }
                        else
                        {
                            continue;
                        }
                        continue;                                                    //All keys past here are 26 characters and only valid letters
                    }
                }
                else
                {
                    printf("Usage: ./substitution key\n");
                    return 1;
                }
            }
        }

    }

    int c = strlen(key[1]);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int convert[26];

    for (int i = 0; i < c; i++)
    {
        key[1][i] = toupper(key[1][i]);
        convert[i] = (int) alphabet[i] - (int) key[1][i];
        //printf("%i - %i = %i\n", alphabet[i], key[1][i], convert[i]);
    }
    //printf("%s\n", key[1]);

    string plaintext = get_string("plaintext: ");
    int m = strlen(plaintext);
    int ciphertext[m];

    for (int j = 0; j < m; j++)
    {
        if (plaintext[j] == 'A' || plaintext[j] == 'a')
        {
            ciphertext[j] = plaintext[j] - convert[0];
        }

        else if (plaintext[j] == 'B' || plaintext[j] == 'b')
        {
            ciphertext[j] = plaintext[j] - convert[1];
        }

        else if (plaintext[j] == 'C' || plaintext[j] == 'c')
        {
            ciphertext[j] = plaintext[j] - convert[2];
        }

        else if (plaintext[j] == 'D' || plaintext[j] == 'd')
        {
            ciphertext[j] = plaintext[j] - convert[3];
        }

        else if (plaintext[j] == 'E' || plaintext[j] == 'e')
        {
            ciphertext[j] = plaintext[j] - convert[4];
        }

        else if (plaintext[j] == 'F' || plaintext[j] == 'f')
        {
            ciphertext[j] = plaintext[j] - convert[5];
        }

        else if (plaintext[j] == 'G' || plaintext[j] == 'g')
        {
            ciphertext[j] = plaintext[j] - convert[6];
        }

        else if (plaintext[j] == 'H' || plaintext[j] == 'h')
        {
            ciphertext[j] = plaintext[j] - convert[7];
        }

        else if (plaintext[j] == 'I' || plaintext[j] == 'i')
        {
            ciphertext[j] = plaintext[j] - convert[8];
        }

        else if (plaintext[j] == 'J' || plaintext[j] == 'j')
        {
            ciphertext[j] = plaintext[j] - convert[9];
        }

        else if (plaintext[j] == 'K' || plaintext[j] == 'k')
        {
            ciphertext[j] = plaintext[j] - convert[10];
        }

        else if (plaintext[j] == 'L' || plaintext[j] == 'l')
        {
            ciphertext[j] = plaintext[j] - convert[11];
        }

        else if (plaintext[j] == 'M' || plaintext[j] == 'm')
        {
            ciphertext[j] = plaintext[j] - convert[12];
        }

        else if (plaintext[j] == 'N' || plaintext[j] == 'n')
        {
            ciphertext[j] = plaintext[j] - convert[13];
        }

        else if (plaintext[j] == 'O' || plaintext[j] == 'o')
        {
            ciphertext[j] = plaintext[j] - convert[14];
        }

        else if (plaintext[j] == 'P' || plaintext[j] == 'p')
        {
            ciphertext[j] = plaintext[j] - convert[15];
        }

        else if (plaintext[j] == 'Q' || plaintext[j] == 'q')
        {
            ciphertext[j] = plaintext[j] - convert[16];
        }

        else if (plaintext[j] == 'R' || plaintext[j] == 'r')
        {
            ciphertext[j] = plaintext[j] - convert[17];
        }

        else if (plaintext[j] == 'S' || plaintext[j] == 's')
        {
            ciphertext[j] = plaintext[j] - convert[18];
        }

        else if (plaintext[j] == 'T' || plaintext[j] == 't')
        {
            ciphertext[j] = plaintext[j] - convert[19];
        }

        else if (plaintext[j] == 'U' || plaintext[j] == 'u')
        {
            ciphertext[j] = plaintext[j] - convert[20];
        }

        else if (plaintext[j] == 'V' || plaintext[j] == 'v')
        {
            ciphertext[j] = plaintext[j] - convert[21];
        }

        else if (plaintext[j] == 'W' || plaintext[j] == 'w')
        {
            ciphertext[j] = plaintext[j] - convert[22];
        }

        else if (plaintext[j] == 'X' || plaintext[j] == 'x')
        {
            ciphertext[j] = plaintext[j] - convert[23];
        }

        else if (plaintext[j] == 'Y' || plaintext[j] == 'y')
        {
            ciphertext[j] = plaintext[j] - convert[24];
        }

        else if (plaintext[j] == 'Z' || plaintext[j] == 'z')
        {
            ciphertext[j] = plaintext[j] - convert[25];
        }

        else
        {
            ciphertext[j] = plaintext[j];
        }
    }
    printf("ciphertext: ");

    for (int z = 0; z < m; z++)
    {
        printf("%c", ciphertext[z]);
    }

    printf("\n");

}