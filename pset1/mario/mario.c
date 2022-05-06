#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int D;
    do
    {
        D = get_int("Height: \n");
    }
    while (D < 1 || D > 8);
  
    for (int i = 0; i < D; i++)
    {
        for (int j = 1; j < D - i; j++)
        {
            printf(" ");
        }
         
        for (int k = D - i; k <= D; k++)
        {
            printf("#");
        }
         
        printf("  ");
         
        for (int m = 0; m <= i; m++)
        {
            printf("#");
        }
         
        printf("\n");
         
    }
      
}

