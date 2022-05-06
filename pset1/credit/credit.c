#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long n = get_long("Number: \n");

    long last = n % 10;
    long twolast = (n % 100) / 10;
    long threelast = (n % 1000) / 100;
    long fourlast = (n % 10000) / 1000;
    long fivelast = (n % 100000) / 10000;
    long sixlast = (n % 1000000) / 100000;
    long sevenlast = (n % 10000000) / 1000000;
    long eightlast = (n % 100000000) / 10000000;
    long ninelast = (n % 1000000000) / 100000000;
    long tenlast = (n % 10000000000) / 1000000000;
    long elevenlast = (n % 100000000000) / 10000000000;
    long twelvelast = (n % 1000000000000) / 100000000000;
    long thirteenlast = (n % 10000000000000) / 1000000000000;
    long fourteenlast = (n % 100000000000000) / 10000000000000;
    long fifteenlast = (n % 1000000000000000) / 100000000000000;
    long sixteenlast = n / 1000000000000000;

    int evensum = last + threelast + fivelast + sevenlast + ninelast + elevenlast + thirteenlast + fifteenlast;

    int doublesixteenlast = sixteenlast * 2;
    int sumdoublesixteenlast = doublesixteenlast % 10 + doublesixteenlast / 10;

    int doublefourteenlast = fourteenlast * 2;
    int sumdoublefourteenlast = doublefourteenlast % 10 + doublefourteenlast / 10;

    int doubletwelvelast = twelvelast * 2;
    int sumdoubletwelvelast = doubletwelvelast % 10 + doubletwelvelast / 10;

    int doubletenlast = tenlast * 2;
    int sumdoubletenlast = doubletenlast % 10 + doubletenlast / 10;

    int doubleeightlast = eightlast * 2;
    int sumdoubleeightlast = doubleeightlast % 10 + doubleeightlast / 10;

    int doublesixlast = sixlast * 2;
    int sumdoublesixlast = doublesixlast % 10 + doublesixlast / 10;

    int doublefourlast = fourlast * 2;
    int sumdoublefourlast = doublefourlast % 10 + doublefourlast / 10;

    int doubletwolast = twolast * 2;
    int sumdoubletwolast = doubletwolast % 10 + doubletwolast / 10;

    int oddsum = sumdoublesixteenlast + sumdoublefourteenlast + sumdoubletwelvelast + sumdoubletenlast + sumdoubleeightlast +
                 sumdoublesixlast + sumdoublefourlast + sumdoubletwolast;

    int sumsum = evensum + oddsum;
    printf("%i = %i + %i", sumsum, evensum, oddsum);

    if (sumsum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (sixteenlast == 5 && fifteenlast == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (sixteenlast == 5 && fifteenlast == 2)
    {
        printf("MASTERCARD\n");
    }
    else if (sixteenlast == 5 && fifteenlast == 3)
    {
        printf("MASTERCARD\n");
    }
    else if (sixteenlast == 5 && fifteenlast == 4)
    {
        printf("MASTERCARD\n");
    }
    else if (sixteenlast == 5 && fifteenlast == 5)
    {
        printf("MASTERCARD\n");
    }
    else if (sixteenlast == 4)
    {
        printf("VISA\n");
    }
    else if (thirteenlast == 4 && sixteenlast == 0)
    {
        printf("VISA\n");
    }
    else if (fifteenlast == 3 && fourteenlast == 4)
    {
        printf("AMEX\n");
    }
    else if (fifteenlast == 3 && fourteenlast == 7)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}



