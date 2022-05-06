#include "helpers.h"
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = 0;
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempblue = 0;
            int tempgreen = 0;
            int tempred = 0;

            if (j - 1== width - j)
            {
                break;
            }
            else if (j == width - j)
            {
                break;
            }
            else
            {
                tempblue = image[i][j].rgbtBlue;
                tempgreen = image[i][j].rgbtGreen;
                tempred = image[i][j].rgbtRed;

                image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

                image[i][width - 1 - j].rgbtBlue = tempblue;
                image[i][width - 1 - j].rgbtGreen = tempgreen;
                image[i][width - 1 - j].rgbtRed = tempred;
            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagetemp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bool topleft = false;
            bool topright = false;
            bool botleft = false;
            bool botright = false;
            bool topedge = false;
            bool leftedge = false;
            bool rightedge = false;
            bool botedge = false;

            if (i == 0 && j == 0)
                topleft = true;
            else if (i == 0 && j == width - 1)
                topright = true;
            else if (i == height - 1 && j == 0)
                botleft = true;
            else if (i == height - 1 && j == width - 1)
                botright = true;
            else if (i == 0)
                topedge = true;
            else if (j == 0)
                leftedge = true;
            else if (j == width - 1)
                rightedge = true;
            else if (i == height - 1)
                botedge = true;

            if (topleft == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0);
                imagetemp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
            }
            else if (topright == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                imagetemp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
            }
            else if (botleft == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                imagetemp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
            }
            else if (botright == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                imagetemp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
            }
            else if (topedge == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                imagetemp[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            }
            else if (leftedge == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                imagetemp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                imagetemp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
            }
            else if (rightedge == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                imagetemp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                imagetemp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
            }
            else if (botedge == true)
            {
                imagetemp[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                imagetemp[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                imagetemp[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
            }
            else
            {
                imagetemp[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
                imagetemp[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                imagetemp[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
            }
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;
        }

    }

    return;
}

// Detect edges


void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imagetemp[height][width]; //creates an array for the filtered image

    float Gx[3][3];
    float Gy[3][3];

    Gx[0][0] = -1.0; //creating the Gx array
    Gx[0][1] = 0.0;
    Gx[0][2] = 1.0;
    Gx[1][0] = -2.0;
    Gx[1][1] = 0.0;
    Gx[1][2] = 2.0;
    Gx[2][0] = -1.0;
    Gx[2][1] = 0.0;
    Gx[2][2] = 1.0;

    Gy[0][0] = -1.0;  //creating the Gy array
    Gy[0][1] = -2.0;
    Gy[0][2] = -1.0;
    Gy[1][0] = 0.0;
    Gy[1][1] = 0.0;
    Gy[1][2] = 0.0;
    Gy[2][0] = 1.0;
    Gy[2][1] = 2.0;
    Gy[2][2] = 1.0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxBlue;
            float GxGreen;
            float GxRed;
            float GyBlue;
            float GyGreen;
            float GyRed;

            bool topleft = false;
            bool topright = false;
            bool botleft = false;
            bool botright = false;
            bool topedge = false;
            bool leftedge = false;
            bool rightedge = false;
            bool botedge = false;

            if (i == 0 && j == 0)                           //Checking for corner/edge condition
                topleft = true;
            else if (i == 0 && j == width - 1)
                topright = true;
            else if (i == height - 1 && j == 0)
                botleft = true;
            else if (i == height - 1 && j == width - 1)
                botright = true;
            else if (i == 0)
                topedge = true;
            else if (j == 0)
                leftedge = true;
            else if (j == width - 1)
                rightedge = true;
            else if (i == height - 1)
                botedge = true;

            if (topleft == true)
            {
                GxBlue = image[i][j].rgbtBlue * Gx[1][1] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];
                GyBlue = image[i][j].rgbtBlue * Gy[1][1] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
                GxGreen = image[i][j].rgbtGreen * Gx[1][1] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];
                GyGreen = image[i][j].rgbtGreen * Gy[1][1] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
                GxRed = image[i][j].rgbtRed * Gx[1][1] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i + 1][j + 1].rgbtRed * Gx[2][2];
                GyRed = image[i][j].rgbtRed * Gy[1][1] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i + 1][j + 1].rgbtRed * Gy[2][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (topright == true)
            {
                GxBlue = image[i][j].rgbtBlue * Gx[1][1] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i][j - 1].rgbtBlue * Gx[1][0] + image[i + 1][j - 1].rgbtBlue * Gx[2][0];
                GyBlue = image[i][j].rgbtBlue * Gy[1][1] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i][j - 1].rgbtBlue * Gy[1][0] + image[i + 1][j - 1].rgbtBlue * Gy[2][0];
                GxGreen = image[i][j].rgbtGreen * Gx[1][1] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i][j - 1].rgbtGreen * Gx[1][0] + image[i + 1][j - 1].rgbtGreen * Gx[2][0];
                GyGreen = image[i][j].rgbtGreen * Gy[1][1] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i][j - 1].rgbtGreen * Gy[1][0] + image[i + 1][j - 1].rgbtGreen * Gy[2][0];
                GxRed = image[i][j].rgbtRed * Gx[1][1] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i][j - 1].rgbtRed * Gx[1][0] + image[i + 1][j - 1].rgbtRed * Gx[2][0];
                GyRed = image[i][j].rgbtRed * Gy[1][1] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i][j - 1].rgbtRed * Gy[1][0] + image[i + 1][j - 1].rgbtRed * Gy[2][0];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));
                
                printf("B: %i, G: %i, R: %i", B, G, R);
                
                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (botleft == true)
            {
                GxBlue = image[i][j].rgbtBlue * Gx[1][1] + image[i - 1][j].rgbtBlue * Gx[0][1] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i - 1][j + 1].rgbtBlue * Gx[0][2];
                GyBlue = image[i][j].rgbtBlue * Gy[1][1] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i - 1][j + 1].rgbtBlue * Gy[0][2];
                GxGreen = image[i][j].rgbtGreen * Gx[1][1] + image[i - 1][j].rgbtGreen * Gx[0][1] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i - 1][j + 1].rgbtGreen * Gx[0][2];
                GyGreen = image[i][j].rgbtGreen * Gy[1][1] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i - 1][j + 1].rgbtGreen * Gy[0][2];
                GxRed = image[i][j].rgbtRed * Gx[1][1] + image[i - 1][j].rgbtRed * Gx[0][1] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i - 1][j + 1].rgbtRed * Gx[0][2];
                GyRed = image[i][j].rgbtRed * Gy[1][1] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i - 1][j + 1].rgbtRed * Gy[0][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (botright == true)
            {
                GxBlue = image[i][j].rgbtBlue * Gx[1][1] + image[i - 1][j].rgbtBlue * Gx[0][1] + image[i][j - 1].rgbtBlue * Gx[1][0] + image[i - 1][j - 1].rgbtBlue * Gx[0][0];
                GyBlue = image[i][j].rgbtBlue * Gy[1][1] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i][j - 1].rgbtBlue * Gy[1][0] + image[i - 1][j - 1].rgbtBlue * Gy[0][0];
                GxGreen = image[i][j].rgbtGreen * Gx[1][1] + image[i - 1][j].rgbtGreen * Gx[0][1] + image[i][j - 1].rgbtGreen * Gx[1][0] + image[i - 1][j - 1].rgbtGreen * Gx[0][0];
                GyGreen = image[i][j].rgbtGreen * Gy[1][1] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i][j - 1].rgbtGreen * Gy[1][0] + image[i - 1][j - 1].rgbtGreen * Gy[0][0];
                GxRed = image[i][j].rgbtRed * Gx[1][1] + image[i - 1][j].rgbtRed * Gx[0][1] + image[i][j - 1].rgbtRed * Gx[1][0] + image[i - 1][j - 1].rgbtRed * Gx[0][0];
                GyRed = image[i][j].rgbtRed * Gy[1][1] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i][j - 1].rgbtRed * Gy[1][0] + image[i - 1][j - 1].rgbtRed * Gy[0][0];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (topedge == true)
            {
                GxBlue = image[i][j - 1].rgbtBlue * Gx[1][0] + image[i][j].rgbtBlue * Gx[1][1] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i + 1][j - 1].rgbtBlue * Gx[2][0] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];
                GyBlue = image[i][j - 1].rgbtBlue * Gy[1][0] + image[i][j].rgbtBlue * Gy[1][1] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
                GxGreen = image[i][j - 1].rgbtGreen * Gx[1][0] + image[i][j].rgbtGreen * Gx[1][1] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i + 1][j - 1].rgbtGreen * Gx[2][0] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];
                GyGreen = image[i][j - 1].rgbtGreen * Gy[1][0] + image[i][j].rgbtGreen * Gy[1][1] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i + 1][j - 1].rgbtGreen * Gy[2][0] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
                GxRed = image[i][j - 1].rgbtRed * Gx[1][0] + image[i][j].rgbtRed * Gx[1][1] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i + 1][j - 1].rgbtRed * Gx[2][0] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i + 1][j + 1].rgbtRed * Gx[2][2];
                GyRed = image[i][j - 1].rgbtRed * Gy[1][0] + image[i][j].rgbtRed * Gy[1][1] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i + 1][j - 1].rgbtRed * Gy[2][0] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (leftedge == true)
            {
                GxBlue = image[i - 1][j].rgbtBlue * Gx[0][1] + image[i][j].rgbtBlue * Gx[1][1] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i - 1][j + 1].rgbtBlue * Gx[0][2] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];
                GyBlue = image[i - 1][j].rgbtBlue * Gy[0][1] + image[i][j].rgbtBlue * Gy[1][1] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
                GxGreen = image[i - 1][j].rgbtGreen * Gx[0][1] + image[i][j].rgbtGreen * Gx[1][1] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i - 1][j + 1].rgbtGreen * Gx[0][2] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];
                GyGreen = image[i - 1][j].rgbtGreen * Gy[0][1] + image[i][j].rgbtGreen * Gy[1][1] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
                GxRed = image[i - 1][j].rgbtRed * Gx[0][1] + image[i][j].rgbtRed * Gx[1][1] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i - 1][j + 1].rgbtRed * Gx[0][2] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i + 1][j + 1].rgbtRed * Gx[2][2];
                GyRed = image[i - 1][j].rgbtRed * Gy[0][1] + image[i][j].rgbtRed * Gy[1][1] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i + 1][j + 1].rgbtRed * Gy[2][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (rightedge == true)
            {
                GxBlue = image[i - 1][j].rgbtBlue * Gx[0][1] + image[i][j].rgbtBlue * Gx[1][1] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i - 1][j - 1].rgbtBlue * Gx[0][0] + image[i][j - 1].rgbtBlue * Gx[1][0] + image[i + 1][j - 1].rgbtBlue * Gx[2][0];
                GyBlue = image[i - 1][j].rgbtBlue * Gy[0][1] + image[i][j].rgbtBlue * Gy[1][1] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i][j - 1].rgbtBlue * Gy[1][0] + image[i + 1][j - 1].rgbtBlue * Gy[2][0];
                GxGreen = image[i - 1][j].rgbtGreen * Gx[0][1] + image[i][j].rgbtGreen * Gx[1][1] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i - 1][j - 1].rgbtGreen * Gx[0][0] + image[i][j - 1].rgbtGreen * Gx[1][0] + image[i + 1][j - 1].rgbtGreen * Gx[2][0];
                GyGreen = image[i - 1][j].rgbtGreen * Gy[0][1] + image[i][j].rgbtGreen * Gy[1][1] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i][j - 1].rgbtGreen * Gy[1][0] + image[i + 1][j - 1].rgbtGreen * Gy[2][0];
                GxRed = image[i - 1][j].rgbtRed * Gx[0][1] + image[i][j].rgbtRed * Gx[1][1] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i - 1][j - 1].rgbtRed * Gx[0][0] + image[i][j - 1].rgbtRed * Gx[1][0] + image[i + 1][j - 1].rgbtRed * Gx[2][0];
                GyRed = image[i - 1][j].rgbtRed * Gy[0][1] + image[i][j].rgbtRed * Gy[1][1] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i][j - 1].rgbtRed * Gy[1][0] + image[i + 1][j - 1].rgbtRed * Gy[2][0];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else if (botedge == true)
            {
                GxBlue = image[i][j - 1].rgbtBlue * Gx[1][0] + image[i][j].rgbtBlue * Gx[1][1] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i - 1][j - 1].rgbtBlue * Gx[0][0] + image[i - 1][j].rgbtBlue * Gx[0][1] + image[i - 1][j + 1].rgbtBlue * Gx[0][2];
                GyBlue = image[i][j - 1].rgbtBlue * Gy[1][0] + image[i][j].rgbtBlue * Gy[1][1] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2];
                GxGreen = image[i][j - 1].rgbtGreen * Gx[1][0] + image[i][j].rgbtGreen * Gx[1][1] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i - 1][j - 1].rgbtGreen * Gx[0][0] + image[i - 1][j].rgbtGreen * Gx[0][1] + image[i - 1][j + 1].rgbtGreen * Gx[0][2];
                GyGreen = image[i][j - 1].rgbtGreen * Gy[1][0] + image[i][j].rgbtGreen * Gy[1][1] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2];
                GxRed = image[i][j - 1].rgbtRed * Gx[1][0] + image[i][j].rgbtRed * Gx[1][1] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i - 1][j - 1].rgbtRed * Gx[0][0] + image[i - 1][j].rgbtRed * Gx[0][1] + image[i - 1][j + 1].rgbtRed * Gx[0][2];
                GyRed = image[i][j - 1].rgbtRed * Gy[1][0] + image[i][j].rgbtRed * Gy[1][1] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
            else
            {
                GxBlue = image[i - 1][j - 1].rgbtBlue * Gx[0][0] + image[i - 1][j].rgbtBlue * Gx[0][1] + image[i - 1][j + 1].rgbtBlue * Gx[0][2] + image[i][j - 1].rgbtBlue * Gx[1][0] + image[i][j].rgbtBlue * Gx[1][1] + image[i][j + 1].rgbtBlue * Gx[1][2] + image[i + 1][j - 1].rgbtBlue * Gx[2][0] + image[i + 1][j].rgbtBlue * Gx[2][1] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];
                GyBlue = image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2] + image[i][j - 1].rgbtBlue * Gy[1][0] + image[i][j].rgbtBlue * Gy[1][1] + image[i][j + 1].rgbtBlue * Gy[1][2] + image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
                GxGreen = image[i - 1][j - 1].rgbtGreen * Gx[0][0] + image[i - 1][j].rgbtGreen * Gx[0][1] + image[i - 1][j + 1].rgbtGreen * Gx[0][2] + image[i][j - 1].rgbtGreen * Gx[1][0] + image[i][j].rgbtGreen * Gx[1][1] + image[i][j + 1].rgbtGreen * Gx[1][2] + image[i + 1][j - 1].rgbtGreen * Gx[2][0] + image[i + 1][j].rgbtGreen * Gx[2][1] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];
                GyGreen = image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2] + image[i][j - 1].rgbtGreen * Gy[1][0] + image[i][j].rgbtGreen * Gy[1][1] + image[i][j + 1].rgbtGreen * Gy[1][2] + image[i + 1][j - 1].rgbtGreen * Gy[2][0] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
                GxRed = image[i - 1][j - 1].rgbtRed * Gx[0][0] + image[i - 1][j].rgbtRed * Gx[0][1] + image[i - 1][j + 1].rgbtRed * Gx[0][2] + image[i][j - 1].rgbtRed * Gx[1][0] + image[i][j].rgbtRed * Gx[1][1] + image[i][j + 1].rgbtRed * Gx[1][2] + image[i + 1][j - 1].rgbtRed * Gx[2][0] + image[i + 1][j].rgbtRed * Gx[2][1] + image[i + 1][j + 1].rgbtRed * Gx[2][2];
                GyRed = image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2] + image[i][j - 1].rgbtRed * Gy[1][0] + image[i][j].rgbtRed * Gy[1][1] + image[i][j + 1].rgbtRed * Gy[1][2] + image[i + 1][j - 1].rgbtRed * Gy[2][0] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];

                int B = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
                int G = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
                int R = round(sqrt(GxRed * GxRed + GyRed * GyRed));

                if (B > 255)
                    B = 255;
                if (G > 255)
                    G = 255;
                if (R > 255)
                    R = 255;

                imagetemp[i][j].rgbtBlue = B;
                imagetemp[i][j].rgbtGreen = G;
                imagetemp[i][j].rgbtRed = R;
            }
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)         //Copying the filtered image into the original image array
        {
            image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;
        }

    }
    return;
}

