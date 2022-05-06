#include <stdio.h>
#include<cs50.h>
#include<string.h>

int main(void)
{
    string text = get_string("Text: ");

    int words = 0;
    int sentences = 0;
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++;
        }

        if ((text[i] == ' ' || text[i] == '.' || text[i] == '!' || text[i] == '?') && text[i + 1] != ' ')
        {
            words++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }

    }
    printf("Letters: %i. words: %i. sentencees: %i", letters, words, sentences);
    double L = letters * 100 / words;      //Letters per 100 words
    double S = sentences * 100 / words;    //Sentences per 100 words
    printf("L: %f, S: %f", L, S);
    double grade = 0.0588 * L - 0.296 * S - 15.85;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0lf\n", grade);
    }
}